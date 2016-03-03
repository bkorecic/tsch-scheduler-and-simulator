#include <string.h>
#include <stdlib.h>
#include "coloring.h"

uint8_t tasaColoring(List *nodesScheduled, bool confMatrix[][MAX_NODES][NUM_CHANNELS], uint16_t Q[][MAX_TIMESLOTS], uint16_t ts, int8_t channel)
{
    uint8_t max_color = 0;

    /* List that holds all nodes sorted by non-decreasing order of degree */
    List nodesSorted; memset(&nodesSorted, 0, sizeof(List)); ListInit(&nodesSorted);

    /* Create the list of sorted nodes (sorting by Q) */
    for (ListElem *elem1 = ListFirst(nodesScheduled); elem1 != NULL; elem1 = ListNext(nodesScheduled, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        ListElem *elem2 = NULL;
        for(elem2 = ListFirst(&nodesSorted); elem2 != NULL; elem2 = ListNext(&nodesSorted,elem2)) /* Find the position to insert i */
        {
            Node_t *n = (Node_t *)elem2->obj;

            if (Q[n->id][ts] <= Q[node->id][ts])
            {
                break;
            }
        }

        if (elem2 == NULL)
        {
            ListAppend(&nodesSorted, (void *)node);
        }
        else
        {
            ListInsertBefore(&nodesSorted, (void *)node, elem2);
        }

        /* Clean up the allocated channel for node */
        ListUnlinkAll(&node->channels);
    }

    /* Color each node */
    for (ListElem *elem1 = ListFirst(&nodesSorted); elem1 != NULL; elem1 = ListNext(&nodesSorted, elem1))
    {
        uint8_t color = 0;
        Node_t *nodeToColor = (Node_t *)elem1->obj;

        /* Check if there is any neighbor of ith node with this color */
        bool foundColor = false;
        while (!foundColor)
        {
            uint8_t old_color = color;

            /* Look at all nodes with conflict */
            for (ListElem *elem2 = ListFirst(&nodesSorted); elem2 != NULL; elem2 = ListNext(&nodesSorted, elem2))
            {
                Node_t *n = (Node_t *)elem2->obj;

                if (confMatrix[nodeToColor->id][n->id][channel])
                {
                    if (ListFind(&n->channels, (void *)color))
                    {
                        color++;
                        break;
                    }
                }
            }

            /* If we did not change the color, we evaluated everyone and did not find any problem */
            if (old_color == color)
            {
                foundColor = true;
            }
        }

        /* Paint the node with the right color */
        ListAppend(&nodeToColor->channels, (void *)color);

        if (color > max_color)
        {
            max_color = color;
        }
    }

    return (max_color);
}
