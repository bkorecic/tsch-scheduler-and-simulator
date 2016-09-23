#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <float.h>
#include "tamu_rpl.h"
#include "rpl.h"
#include "../util/defs.h"
#include "../util/gen_beta.h"

bool tamuUpdateParents(List *nodesList)
{
    bool ret = false;

    /* Update the information for all nodes */
    for(ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        if (node->type != SINK && node->synced)
        {
            if (tamuSampleNode(node))
            {
                ret = true;
            }
        }
    }

    return (ret);
}

bool tamuSampleNode(Node_t *node)
{
    uint8_t min_hop_count = 255;
    double max_beta_sample = 0;
    RPL_Neighbor_t *max_beta_neighbor = NULL;
    RPL_Neighbor_t *oldPreferedParent = NULL;

    node->synced = false;

    /* Create a list with stable neighbors closer to the sink */
    List neighborsSmallHopCount;
    memset(&neighborsSmallHopCount, 0, sizeof(List)); ListInit(&neighborsSmallHopCount);

    /* Calculate the minimum hop count */
    for(ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor->stable && neighbor->hop_count < min_hop_count)
        {
            min_hop_count = neighbor->hop_count;
        }

        if (neighbor->prefered_parent)
        {
            oldPreferedParent = neighbor;
        }

        /* Reset the parent preference to all neighbors */
        neighbor->prefered_parent = false;
    }

    /* Update the list with all neighbors with minimum hop count */
    for(ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor->stable && neighbor->hop_count == min_hop_count)
        {
            ListAppend(&neighborsSmallHopCount, (void *)neighbor);
        }
    }

    /* Lets check if any of these neighbors were not sampled yet */
    for(ListElem *elem = ListFirst(&neighborsSmallHopCount); elem != NULL; elem = ListNext(&neighborsSmallHopCount, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor->n_sampled == 0)
        {
            /* This is the new parent */
            tamuSetPreferedParent(node, neighbor);

            return (true);
        }

        /* Generate the corresponding Beta(1+S_t, 1 + F_t) */
        neighbor->beta_sample = gen_beta(1 + neighbor->rx_success,1 + neighbor->rx_failed);

        if (neighbor->beta_sample > max_beta_sample)
        {
            max_beta_sample = neighbor->beta_sample;
            max_beta_neighbor = neighbor;
        }
    }

    /* Set the new prefered parent */
    if (max_beta_neighbor != NULL)
    {
        tamuSetPreferedParent(node, max_beta_neighbor);
    }

    if (oldPreferedParent != max_beta_neighbor)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void tamuSetPreferedParent(Node_t *node, RPL_Neighbor_t *neighbor)
{
    node->synced = true;
    node->hop_count = neighbor->hop_count + 1;

    neighbor->n_sampled++;
    neighbor->prefered_parent = true;
}

bool tamuRxDio(Node_t *node)
{
    /* We check if the DIO received was the first one, in this case we have to sample the new neighbor */
    if (!node->synced)
    {
        for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

            if (neighbor->stable)
            {
                tamuSetPreferedParent(node, neighbor);
                return (true);
            }
        }
    }

    return (false);
}
