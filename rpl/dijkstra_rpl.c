#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "dijkstra_rpl.h"
#include "rpl.h"
#include "../util/defs.h"
#include "../util/debug.h"
#include "../util/files.h"
#include "../mcc/time_schedule.h"
#include "../schedule/fhss.h"

void dijkstraCalculateTree(List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS])
{
    Node_t *v, *u;

    /* This queue keeps all nodes that do not have a dagrank yet */
    List nodesQueue;
    List neighborsList;
    memset(&(nodesQueue), 0, sizeof(List)); ListInit(&(nodesQueue));
    memset(&(neighborsList), 0, sizeof(List)); ListInit(&(neighborsList));

    /* Insert all nodes except the sink */
    for(ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        ListAppend(&nodesQueue, (void *)node);

        if (node->type != SINK)
        {
            node->dagRank = DEFAULTDAGRANK;
        }
        else
        {
            node->dagRank = MINHOPRANKINCREASE;
        }

        RPL_Neighbor_t *neighbor = newNeighbor(node->id);
        ListAppend(&neighborsList, (void *)neighbor);
    }

    while (!ListEmpty(&nodesQueue))
    {
        /* Find element with smaller dagRank */
        ListElem *elem_u = dijkstraMinCost(&nodesQueue);
        u = (Node_t *)elem_u->obj;

        /* This node was already assigned to a parent */
        u->synced = true;

        /* Remove u from queue */
        ListUnlink(&nodesQueue, elem_u);

        /* For all neighbors of u still in the queue update the cost and parent */
        for(ListElem *elem = ListFirst(&nodesQueue); elem != NULL; elem = ListNext(&nodesQueue, elem))
        {
            v = (Node_t *)elem->obj;

            RPL_Neighbor_t *u_neighbor = getNeighbor(u->id, &v->candidate_parents);
            if (u_neighbor == NULL)
            {
                u_neighbor = newNeighbor(u->id);
                ListAppend(&v->candidate_parents, (void *)u_neighbor);
            }

            uint16_t dagRank = dijkstraGetRank(u, v, prrMatrix);
            if (v->dagRank > dagRank)
            {
                v->dagRank = dagRank;
                dijkstraSetPreferedParent(v, u_neighbor);
            }
        }
    }

    return;
}

ListElem *dijkstraMinCost(List *nodesQueue)
{
    uint16_t min_cost = MAXDAGRANK;
    ListElem *node_min_cost = NULL;

    /* Insert all nodes except the sink */
    for(ListElem *elem = ListFirst(nodesQueue); elem != NULL; elem = ListNext(nodesQueue, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        if (node->dagRank <= min_cost)
        {
            min_cost = node->dagRank;
            node_min_cost = elem;
        }
    }

    return (node_min_cost);
}

uint16_t dijkstraGetRank(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS])
{
    uint16_t average_prr = 0;
    uint16_t rank_increase;

    /* Calculate the average PRR */
    for (uint8_t i = 0; i < 16; i++)
    {
        average_prr += prrMatrix[child->id][parent->id][i];
    }

    average_prr /= 16;

    if (average_prr != 0 && average_prr > STABLE_NEIGHBOR_THRESHOLD)
    {
        rank_increase = 100.0/(float)average_prr * 2.0 * (float)MINHOPRANKINCREASE;

        return (parent->dagRank + rank_increase);
    }
    else
    {
        return (MAXDAGRANK);
    }
}

void dijkstraSetPreferedParent(Node_t *v, RPL_Neighbor_t *u_neighbor)
{
    for(ListElem *elem = ListFirst(&v->candidate_parents); elem != NULL; elem = ListNext(&v->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor == u_neighbor)
        {
            neighbor->prefered_parent = true;
        }
        else
        {
            neighbor->prefered_parent = false;
        }
    }
}

