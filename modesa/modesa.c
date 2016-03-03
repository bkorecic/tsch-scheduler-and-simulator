#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modesa.h"
#include "../util/debug.h"

bool main_modesa(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, uint8_t sink_interfaces, \
                bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel)
{
    uint16_t n_nodes = 0;

    /* Number of nodes in the network */
    n_nodes = ListLength(nodesList);

    /* Parameter iu, number of radio interfaces */
    uint8_t availableInterfaces[n_nodes];

    /* Set the number of interface in the sink node */
    Node_t *sink_node = getNode(sink_id, nodesList);
    sink_node->interfaces = sink_interfaces;

    /* Current time slot */
    uint16_t t = 0;

    /* In Modesa we use the parameter q of a node to keep track of how many packets the nodes
     * currently stores in its buffer */
    while (totalTraffic(nodesList) != 0)
    {
        /* Update priority of nodes and initialize the number of available interfaces */
        for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
        {
            /* Get the current node */
            Node_t *node = (Node_t *)elem->obj;

            /* Update the priority */
            node->priority = node->q * calculateParentRcv(node, tree);

            /* Initialize the number of interfaces */
            availableInterfaces[node->id] = node->interfaces;
        }

        /* Create an array of lists with conflicting nodes on channel c */
        List conflictLists[NUM_CHANNELS];
        for (uint8_t i = 0; i < NUM_CHANNELS; i++)
        {
            memset(&conflictLists[i], 0, sizeof(List));
            ListInit(&conflictLists[i]);
        }

        /* Create N, the list of nodes having data to transmit and sorted according to their priorities */
        List N; memset(&N, 0, sizeof(List)); ListInit(&N);
        createListNodeWithData(nodesList, &N);

        /* While N != 0 */
        while(ListLength(&N))
        {
            bool tx = false;
            bool nChannelReached = false;

            Node_t *selectedNode = NULL;
            Node_t *selectedParent = NULL;

            /* Remove nodes from N until we get a node with available interface and whose parent also has an interface */
            do
            {
                ListElem *elem = ListFirst(&N);

                if (elem == NULL)
                {
                    selectedNode = NULL;
                    break;
                }
                else
                {
                    selectedNode = (Node_t *)elem->obj;
                }
                ListUnlink(&N, elem);

                selectedParent = getParent(tree, selectedNode);
            } while (availableInterfaces[selectedNode->id] == 0 || availableInterfaces[selectedParent->id] == 0);

            if (selectedNode == NULL)
            {
                break;
            }

            uint8_t c = 0;

            /* Try to schedule until TX or nChannelReached */
            do
            {
                /* If selectedNode is not in the conflict list of channel c */
                if (!ListFind(&conflictLists[c], (void *)selectedNode))
                {
                    /* Node selectedNode transmits in slot t on channel c */
                    TimeSlot_t *ts = newTimeSlot(t+1, c, TS_TX, selectedParent, false);
                    ListAppend(&selectedNode->timeslots, (void *)ts);
                    ts = newTimeSlot(t+1, c, TS_RX, selectedNode, false);
                    ListAppend(&selectedParent->timeslots, (void *)ts);

                    /* Update the current traffic queue */
                    selectedNode->q--;
                    if (selectedParent->id != sink_id)
                    {
                        selectedParent->q++;
                    }

                    /* Update the number of available interfaces */
                    availableInterfaces[selectedNode->id]--;
                    availableInterfaces[selectedParent->id]--;

                    /* Update the list of conflicting nodes on channel c */
                    ListAppend(&conflictLists[c], (void *)selectedNode);
                    for (uint8_t i = 0; i < n_nodes; i++)
                    {
                        if (confMatrix[selectedNode->id][i][channel] == true)
                        {
                            Node_t *confNode = getNode(i, nodesList);
                            if (!ListFind(&conflictLists[c], (void *)confNode))
                            {
                                ListAppend(&conflictLists[c], (void *)confNode);
                            }
                        }
                    }

                    tx = true;
                }
                else
                {
                    if (c < NUM_CHANNELS)
                    {
                        /* Next channel */
                        c++;
                    }
                    else
                    {
                        /* No more available channels */
                        nChannelReached = true;
                    }
                }

            } while (!tx && !nChannelReached);
        }

        /* t = t + 1 */
        t++;
    }

    return (true);
}

void createListNodeWithData(List *nodesList, List *N)
{

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        /* Get the current node */
        Node_t *node1 = (Node_t *)elem1->obj;

        if (node1->priority != 0)
        {
            /* Insert in the right position inside list N */
            ListElem *elem2 = ListFirst(N);

            while (elem2 != NULL)
            {
                Node_t *node2 = (Node_t *)elem2->obj;

                /* Checking the priority and the node id */
                if ((node1->priority < node2->priority) || \
                    ((node1->priority == node2->priority) && (node1->id > node2->id)))
                {
                    elem2 = ListNext(N, elem2);
                }
                else
                {
                    ListInsertBefore(N, elem1->obj, elem2);
                    break;
                }
            }

            /* If sorted_list is empty or elem1 is smaller than everyone in the sorted list */
            if (elem2 == NULL)
            {
                ListAppend(N, elem1->obj);
            }
        }
    }
}

uint16_t calculateParentRcv(Node_t *node, Tree_t *tree)
{
    List listChildren; memset(&listChildren, 0, sizeof(List)); ListInit(&listChildren);

    Tree_t *subTree = getSubTree(tree, node);
    getListNodesInTree(subTree, &listChildren);

    uint16_t res = 0;
    for (ListElem *elem = ListFirst(&listChildren); elem != NULL; elem = ListNext(&listChildren, elem))
    {
        Node_t *node = (Node_t *)elem->obj;
        res += node->q;
    }

    return (res);
}
