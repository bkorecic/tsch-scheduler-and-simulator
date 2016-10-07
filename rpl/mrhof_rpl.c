#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "rpl.h"
#include "../util/defs.h"
#include "../util/debug.h"
#include "../util/files.h"
#include "../mcc/time_schedule.h"
#include "../schedule/fhss.h"

uint16_t rplMrhofGetRank(RPL_Neighbor_t *neighbor);

bool mrhofUpdateDAGRanks(Node_t *node)
{
    uint16_t min_dagRank = MAXDAGRANK;
    RPL_Neighbor_t *preferedParent = NULL;
    RPL_Neighbor_t *oldPreferedParent = NULL;

    /* Set the synced flag */
    node->synced = false;

    /* Go over all neighbors and check which should be our prefered parent */
    for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        uint16_t neighborRank = rplMrhofGetRank(neighbor);
        if (neighbor->stable && neighborRank < min_dagRank)
        {
            /* This neighbor has a lower Rank */
            min_dagRank = neighborRank;
            preferedParent = neighbor;
        }

        if (neighbor->prefered_parent)
        {
            oldPreferedParent = neighbor;
        }

        /* Clean the preferedparent field */
        neighbor->prefered_parent = false;
    }

    if (min_dagRank < MAXDAGRANK)
    {
        /* Set the new Rank for the node */
        node->dagRank = min_dagRank;

        /* Set the synced flag */
        node->synced = true;

        /* Set the new prefered parent */
        preferedParent->prefered_parent = true;
    }

    if (oldPreferedParent != preferedParent)
    {
        /* Changed the prefered parent */
        return (true);
    }
    else
    {
        return (false);
    }
}

uint16_t rplMrhofGetRank(RPL_Neighbor_t *neighbor)
{
    uint16_t rank_increase = 0;

    if (neighbor->rx_success == 0)
    {
        rank_increase = DEFAULTLINKCOST * 2 * MINHOPRANKINCREASE;
    }
    else
    {
        rank_increase = neighbor->estimated_etx * 2.0 * (float)MINHOPRANKINCREASE;
    }

    return (neighbor->dagRank + rank_increase);
}
