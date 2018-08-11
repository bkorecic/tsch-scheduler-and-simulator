#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "mrhof_rpl.h"
#include "rpl.h"
#include "../util/defs.h"
#include "../util/debug.h"
#include "../util/files.h"
#include "../mcc/time_schedule.h"
#include "../schedule/fhss.h"

uint16_t mrhofGetRank(RPL_Neighbor_t *neighbor);
void mrhofSetPreferedParent(Node_t *node, RPL_Neighbor_t *neighbor);

bool mrhofUpdateParents(List *nodesList, uint8_t rpl_algo)
{
    bool ret = false;

    /* Update the information for all nodes */
    for(ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        if (node->type != SINK && node->synced)
        {
            if (mrhofUpdateDAGRanks(node, nodesList))
            {
                ret = true;
            }
        }
    }

    return (ret);
}

bool mrhofRxDio(Node_t *node, List *nodesList)
{
    /* We check if the DIO received was the first one, in this case we have to set new neighbor as prefered parent */
    if (!node->synced)
    {
        for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

            if (neighbor->stable)
            {
                mrhofSetPreferedParent(node, neighbor);
                return (true);
            }
        }
    }

    return (false);
}

bool mrhofUpdateDAGRanks(Node_t *node, List *nodesList)
{
    float min_dagRank = MAXDAGRANK;
    RPL_Neighbor_t *preferedParent = NULL;
    RPL_Neighbor_t *oldPreferedParent = NULL;
    float oldPreferedDagrank;

    /* Set the synced flag */
    node->synced = false;

    /* Clean up the createLoop flag of all neighbors */
    for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;
        neighbor->createLoop = false;
    }

    while (rplDetectLoop(node, preferedParent, nodesList) || preferedParent == NULL)
    {
        /* Go over all neighbors and check which should be our prefered parent */
        bool foundOneNewNeighbor = false;
        for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

            uint16_t neighborRank = mrhofGetRank(neighbor);
            if (neighbor->stable && neighborRank < min_dagRank && !neighbor->createLoop)
            {
                /* This neighbor has a lower Rank */
                min_dagRank = neighborRank;
                preferedParent = neighbor;

                foundOneNewNeighbor = true;
            }

            if (neighbor->prefered_parent)
            {
                oldPreferedParent = neighbor;
                oldPreferedDagrank = neighborRank;
            }

            /* Clean the preferedparent field */
            neighbor->prefered_parent = false;
        }

        if (rplDetectLoop(node, preferedParent, nodesList) && preferedParent != NULL)
        {
            preferedParent->createLoop = true;
            min_dagRank = MAXDAGRANK;
            node->loops_detected++;
        }

        if (!foundOneNewNeighbor)
        {
            min_dagRank = oldPreferedDagrank;
            preferedParent = oldPreferedParent;
            break;
        }
    }

    if (preferedParent != NULL)
    {
        /* Hysteresis */
        if (min_dagRank < HYSTERESIS_PERCENTUAL*oldPreferedDagrank)
        {
            mrhofSetPreferedParent(node, preferedParent);

            /* Changed the prefered parent */
            return (true);
        }
        else
        {
            mrhofSetPreferedParent(node, oldPreferedParent);
        }
    }

    return (false);
}

uint16_t mrhofGetRank(RPL_Neighbor_t *neighbor)
{
    uint16_t rank_increase = 0;

    if (neighbor->rx_success == 0)
    {
        rank_increase = rplGetDefaultLinkCost() * 2 * MINHOPRANKINCREASE;
    }
    else
    {
        rank_increase = neighbor->estimated_etx * 2.0 * (float)MINHOPRANKINCREASE;
    }

    return (neighbor->dagRank + rank_increase);
}

void mrhofSetPreferedParent(Node_t *node, RPL_Neighbor_t *neighbor)
{
    neighbor->prefered_parent = true;
    node->synced = true;
    node->hop_count = neighbor->hop_count + 1;
    node->dagRank = mrhofGetRank(neighbor);
}
