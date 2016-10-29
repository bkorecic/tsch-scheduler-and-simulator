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

uint16_t rplTamuGetRank(RPL_Neighbor_t *neighbor);

bool tamuUpdateParents(List *nodesList, uint8_t rpl_algo)
{
    bool ret = false;

    /* Update the information for all nodes */
    for(ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        if (node->type != SINK && node->synced)
        {
            if (tamuSampleNodeMultiHopRank(node, nodesList))
            {
                ret = true;
            }
        }
    }

    return (ret);
}

bool tamuSampleNodeMultiHopRank(Node_t *node, List *nodesList)
{
    float min_rank_beta_sample = MAXDAGRANK;
    RPL_Neighbor_t *min_rank_beta_neighbor = NULL;
    RPL_Neighbor_t *oldPreferedParent = NULL;
    float oldPreferedDagrank;

    node->synced = false;

    /* Clean the prefered parent field of all neighbors */
    for(ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;
        if (neighbor->prefered_parent)
        {
            oldPreferedParent = neighbor;
            oldPreferedDagrank = rplTamuGetRank(neighbor);
        }
        neighbor->prefered_parent = false;
    }

    /* Lets sample all neighbors */
    for(ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        /* Generate the corresponding Beta(1+S_t, 1 + F_t) */
        neighbor->beta_sample = gen_beta(1 + neighbor->rx_success,1 + neighbor->rx_failed);

        if (neighbor->stable && neighbor->n_sampled == 0 && !rplDetectLoop(node, neighbor, nodesList))
        {
            /* This is the new parent */
            tamuSetPreferedParent(node, neighbor);

            return (true);
        }
    }

    /* Lets find what is the stable neighbor with minimum Rank + Beta */
    for(ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor->stable && rplTamuGetRank(neighbor) < min_rank_beta_sample && !rplDetectLoop(node, neighbor, nodesList))
        {
            min_rank_beta_sample = rplTamuGetRank(neighbor);
            min_rank_beta_neighbor = neighbor;
        }
    }

    /* Set the new prefered parent */
    if (min_rank_beta_neighbor != NULL)
    {
        /* Hysteresis */
        if (min_rank_beta_sample < HYSTERESIS_PERCENTUAL*oldPreferedDagrank)
        {
            tamuSetPreferedParent(node, min_rank_beta_neighbor);
            return (true);
        }
        else
        {
            tamuSetPreferedParent(node, oldPreferedParent);
        }
    }

    return (false);
}

void tamuSetPreferedParent(Node_t *node, RPL_Neighbor_t *neighbor)
{
    neighbor->n_sampled++;
    neighbor->prefered_parent = true;

    node->synced = true;
    node->hop_count = neighbor->hop_count + 1;
    node->dagRank = rplTamuGetRank(neighbor);
}

bool tamuRxDio(Node_t *node, List *nodesList)
{
    /* We check if the DIO received was the first one, in this case we have to sample the new neighbor */
    if (!node->synced)
    {
        for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

            if (neighbor->stable)
            {
                neighbor->beta_sample = gen_beta(1 + neighbor->rx_success,1 + neighbor->rx_failed);
                tamuSetPreferedParent(node, neighbor);
                return (true);
            }
        }
    }

    return (false);
}

uint16_t rplTamuGetRank(RPL_Neighbor_t *neighbor)
{
    uint16_t rank_increase = 0;

    if (neighbor->beta_sample == 0)
    {
        rank_increase = DEFAULTLINKCOST * 2 * MINHOPRANKINCREASE;
    }
    else
    {
        rank_increase = 1.0/neighbor->beta_sample * 2.0 * (float)MINHOPRANKINCREASE;
    }

    return (neighbor->dagRank + rank_increase);
}
