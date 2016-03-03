#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasa.h"
#include "matching.h"
#include "coloring.h"
#include "../util/list.h"
#include "../util/debug.h"
#include "../util/files.h"
#include "../util/files.h"
#include "../util/defs.h"
#include "../graphs/graphs.h"

bool main_tasa(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id,
               bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel)
{
    uint16_t n_nodes = 0;

    /* Number of nodes in the network */
    n_nodes = ListLength(nodesList);

    uint16_t totalQ = totalTraffic(nodesList);

    /* Matrix q will hold the number of packets locally stored at node i during time slot j */
    uint16_t q[n_nodes][MAX_TIMESLOTS];
    memset(q, 0, sizeof(uint16_t)*n_nodes * MAX_TIMESLOTS);

    /* qi(k) = qi if k = 0 */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;
        q[node->id][0] = node->q;
    }

    /* Matrix Q will hold the number of packets globally stored at subtree rooted at node i during time slot j */
    uint16_t Q[n_nodes][MAX_TIMESLOTS];
    memset(Q, 0, sizeof(uint16_t)*n_nodes * MAX_TIMESLOTS);

    for (uint8_t i = 0; i < n_nodes; i++)
    {
        Node_t *node = getNode(i, nodesList);
        Q[i][0] = calculateQ(node, 0, q, tree);
    }

    uint16_t k = 0;

    while (q[sink_id][k] != totalQ)
    {
        /* Duplex Conflict Free Link during timeslot k */
        List DCFL; memset(&DCFL, 0, sizeof(List)); ListInit(&DCFL);

        /* Validate all nodes in the tree */
        validadeAllSubtrees(tree);

        /* DCFL(k) = MATCHING(G,q,Q,n0,k) */
        tasaMatching(&DCFL, q, Q, tree, k, getNode(sink_id, nodesList));

        /* Print the Duplex Conflic Free Links */
        PRINTF("Links scheduled at time slot %d\n", k+1);
        printListLinks(&DCFL);

        /* We also create a list of transmitter nodes in this time slot for coloring purpose */
        List nodesScheduled; memset(&nodesScheduled, 0, sizeof(List)); ListInit(&nodesScheduled);

        /* Create the list of transmitter nodes */
        for (ListElem *elem = ListFirst(&DCFL); elem != NULL; elem = ListNext(&DCFL, elem))
        {
            Link_t *link = (Link_t *)elem->obj;

            /* Getting the transmitter and receiver */
            Node_t *tx = link->n1;

            /* Inserting the transmitter into the list of scheduled nodes */
            if (!ListFind(&nodesScheduled, (void *)tx))
            {
                ListAppend(&nodesScheduled, (void *)tx);
            }
        }

        /* Coloring the links scheduled at this time slot */
        uint8_t max_color = tasaColoring(&nodesScheduled, confMatrix, Q, k, channel);

        printListNodes(nodesList);

        if (max_color >= NUM_CHANNELS)
        {
            /* Lets remove the links corresponding to the colors greater that NUM_CHANNELS */
            for (ListElem *elem = ListFirst(&DCFL); elem != NULL; elem = ListNext(&DCFL, elem))
            {
                Link_t *link = (Link_t *)elem->obj;
                if ((uint8_t)ListFirst(&link->n1->channels)->obj >= NUM_CHANNELS)
                {
                    ListUnlink(&DCFL, elem);
                }
            }
        }

        /* Convert the list of links into a list of time slot and insert into the corresponding node */
        for (ListElem *elem = ListFirst(&DCFL); elem != NULL; elem = ListNext(&DCFL, elem))
        {
            Link_t *link = (Link_t *)elem->obj;

            /* Getting the transmitter and receiver */
            Node_t *tx = link->n1;
            Node_t *rx = link->n2;

            TimeSlot_t *ts = newTimeSlot(k+1, (uint8_t)ListFirst(&tx->channels)->obj, TS_TX, rx, false);
            ListAppend(&tx->timeslots, (void *)ts);
            ts = newTimeSlot(k+1, (uint8_t)ListFirst(&tx->channels)->obj, TS_RX, tx, false);
            ListAppend(&rx->timeslots, (void *)ts);
        }

        /* Go to next time slot */
        k++;

        /* Updating q */
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            q[i][k] = q[i][k-1];
        }

        /* Lets update the q array */
        for (ListElem *elem = ListFirst(&DCFL); elem != NULL; elem = ListNext(&DCFL, elem))
        {
            Link_t *link = (Link_t *)elem->obj;

            /* Getting the transitter and receiver */
            Node_t *tx = link->n1;
            Node_t *rx = link->n2;

            /* Updating the values of q */
            q[tx->id][k]--;
            q[rx->id][k]++;
        }

        /* Updating Q */
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            Node_t *node = getNode(i, nodesList);
            Q[i][k] = calculateQ(node, k, q, tree);
        }

        printListNodes(nodesList);
    }

    printListNodes(nodesList);

    return (true);
}

uint16_t calculateQ(Node_t *node, uint16_t k, uint16_t q[][MAX_TIMESLOTS], Tree_t *tree)
{
    List listChildren; memset(&listChildren, 0, sizeof(List)); ListInit(&listChildren);

    Tree_t *subTree = getSubTree(tree, node);
    getListNodesInTree(subTree, &listChildren);

    uint16_t res = 0;
    for (ListElem *elem = ListFirst(&listChildren); elem != NULL; elem = ListNext(&listChildren, elem))
    {
        Node_t *node = (Node_t *)elem->obj;
        res += q[node->id][k];
    }

    return (res);
}
