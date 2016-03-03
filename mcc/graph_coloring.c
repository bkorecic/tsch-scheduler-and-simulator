#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/debug.h"
#include "graph_coloring.h"

bool assignChannelNodes(List *nodesList, bool confMatrix[][MAX_NODES][NUM_CHANNELS], CHANNEL_TYPE type, Tree_t *cmst, int8_t channel)
{
    uint8_t n_nodes = ListLength(nodesList);

    /* List that holds all nodes sorted by non-decreasing order of degree */
    List nodesSorted; memset(&nodesSorted, 0, sizeof(List)); ListInit(&nodesSorted);

    /* Calculate the degree of each node */
    for (uint8_t i = 0; i < n_nodes; i++)
    {
        uint8_t degree = 0;

        for (uint8_t j = 0; j < n_nodes; j++)
        {
            if (confMatrix[i][j][channel] == true)
            {
                degree++;
            }
        }

        Node_t *node = getNode(i, nodesList);
        node->degree = degree;
    }

    /* Create the list of sorted nodes */
    for (uint8_t i = 0; i < n_nodes; i++)
    {
        Node_t *node = getNode(i, nodesList);

        ListElem *elem = NULL;
        for(elem = ListFirst(&nodesSorted); elem != NULL; elem = ListNext(&nodesSorted,elem)) /* Find the position to insert i */
        {
            Node_t *n = (Node_t *)elem->obj;

            if (n->degree <= node->degree)
            {
                break;
            }
        }

        if (elem == NULL)
        {
            ListAppend(&nodesSorted, (void *)node);
        }
        else
        {
            ListInsertBefore(&nodesSorted, (void *)node, elem);
        }
    }

    /* If we are coloring based on RX (parents determine the color), lets remove all leaves */
    if (type == RX_BASED)
    {
        for(ListElem *elem = ListFirst(&nodesSorted); elem != NULL; elem = ListNext(&nodesSorted,elem)) /* Find the position to insert i */
        {
            Node_t *n = (Node_t *)elem->obj;

            if (n->type == LEAF)
            {
                ListUnlink(&nodesSorted, elem);
                elem = ListFirst(&nodesSorted);
            }
        }
    }
    /* If we are coloring based on TX (children determine the color), lets remove the sink node */
    else if (type == TX_BASED)
    {
        for(ListElem *elem = ListFirst(&nodesSorted); elem != NULL; elem = ListNext(&nodesSorted,elem)) /* Find the position to insert i */
        {
            Node_t *n = (Node_t *)elem->obj;

            if (n->type == SINK)
            {
                ListUnlink(&nodesSorted, elem);
                break;
            }
        }
    }

    /* Keep painting the nodes until there is no more colors to be used */
    while(paintNodes(&nodesSorted, confMatrix, channel))
    {
        PRINTF("New coloring:\n");
        printListNodes(nodesList);
    }

    /* We have painted all nodes, but we actually need to paint their time slots */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        if (type == RX_BASED)
        {
            /* Paint for the RX channel allocation */
            for (ListElem *elem2 = ListFirst(&node->timeslots); elem2 != NULL; elem2 = ListNext(&node->timeslots, elem2))
            {
                TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;
                if (ts->type == TS_RX)
                {
                    ts->freq = (uint8_t)ListFirst(&node->channels)->obj;
                }
            }

            Tree_t *tree = getSubTree(cmst, node);
            for (ListElem *elem3 = ListFirst(&tree->subtrees_list); elem3 != NULL; elem3 = ListNext(&tree->subtrees_list, elem3))
            {
                Tree_t *subTree = (Tree_t *)elem3->obj;
                for (ListElem *elem4 = ListFirst(&subTree->root->timeslots); elem4 != NULL; elem4 = ListNext(&subTree->root->timeslots, elem4))
                {
                    TimeSlot_t *ts = (TimeSlot_t *)elem4->obj;
                    if (ts->type == TS_TX)
                    {
                        ts->freq = (uint8_t)ListFirst(&node->channels)->obj;
                    }
                }
            }
        }
        else
        {
            /* Paint for the TX channel allocation */
            for (ListElem *elem2 = ListFirst(&node->timeslots); elem2 != NULL; elem2 = ListNext(&node->timeslots, elem2))
            {
                TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;
                if (ts->type == TS_TX)
                {
                    ts->freq = (uint8_t)ListFirst(&node->channels)->obj;
                }
            }

            Node_t *parent = getParent(cmst, node);
            for (ListElem *elem3 = ListFirst(&parent->timeslots); elem3 != NULL; elem3 = ListNext(&parent->timeslots, elem3))
            {
                TimeSlot_t *ts = (TimeSlot_t *)elem3->obj;
                if (ts->type == TS_RX)
                {
                    ts->freq = (uint8_t)ListFirst(&node->channels)->obj;
                }
            }

        }
    }

    return (true);
}

bool assignChannelLinks(List *nodesList, float etxMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], Tree_t *cmst)
{
    /* Create a list with all links in the graph G */
    List linksList; memset(&linksList, 0, sizeof(List)); ListInit(&linksList);
    generateLinksList(cmst, &linksList);

    uint16_t n_links = ListLength(&linksList);

    /* List of links allocated for each channel */
    List CA[NUM_CHANNELS];
    for (uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        memset(&CA[i], 0, sizeof(List)); ListInit(&CA[i]);
    }

    /* Sort all channel according to ETX for each link */
    int ch_order[n_links][NUM_CHANNELS];
    memset(ch_order, -1, n_links * NUM_CHANNELS * sizeof(int));
    for (ListElem *elem = ListFirst(&linksList); elem != NULL; elem = ListNext(&linksList, elem))
    {
        Link_t *link = (Link_t *)elem->obj;

        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            float etx_c = etxMatrix[link->n1->id][link->n2->id][c] + etxMatrix[link->n2->id][link->n1->id][c];

            /* Look for the position to insert channel c into vector ch_order */
            uint8_t i;
            for (i = 0; i < NUM_CHANNELS && (etxMatrix[link->n1->id][link->n2->id][ch_order[link->id][i]] + etxMatrix[link->n2->id][link->n1->id][ch_order[link->id][i]]) <= etx_c && ch_order[link->id][i] != -1; i++);

            if (ch_order[link->id][i] != -1)
            {
                memmove(&ch_order[link->id][i+1], &ch_order[link->id][i], (NUM_CHANNELS - i)*sizeof(int));
            }

            ch_order[link->id][i] = c;
        }
    }

    bool confLinkMatrix[n_links][n_links][NUM_CHANNELS];
    memset(confLinkMatrix, false, n_links * n_links * NUM_CHANNELS * sizeof(bool));

    /* Create the list of interfering links for each link */
    for (ListElem *elem1 = ListFirst(&linksList); elem1 != NULL; elem1 = ListNext(&linksList, elem1))
    {
        Link_t *link1 = (Link_t *)elem1->obj;
        Node_t *n1_link1 = link1->n1;

        for (ListElem *elem2 = ListFirst(&linksList); elem2 != NULL; elem2 = ListNext(&linksList, elem2))
        {
            Link_t *link2 = (Link_t *)elem2->obj;
            Node_t *n1_link2 = link2->n1;

            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                if (confMatrix[n1_link1->id][n1_link2->id][c])
                {
                    confLinkMatrix[link1->id][link2->id][c] = true;
                }
            }
        }
    }

    PRINTF("\nConflict links matrices\n");
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        PRINTF("Channel %d:\n", c);
        for (uint8_t i = 0; i < n_links; i++)
        {
            for (uint8_t j = 0; j < n_links; j++)
            {
                if (confLinkMatrix[i][j][c]) PRINTF("1, ");
                else PRINTF("0, ");
            }
            PRINTF("\n");
        }
        PRINTF("\n");
    }

    /* Calculate the weight for each link - The weight is calculated according to this formula */
    /* w(l) = ( THETA * subtree_size + KAPPA * conflict_size ) / PHI * good_channel_size */
    for (ListElem *elem1 = ListFirst(&linksList); elem1 != NULL; elem1 = ListNext(&linksList, elem1))
    {
        Link_t *link = (Link_t *)elem1->obj;

        Node_t *n1 = link->n1;
        Node_t *n2 = link->n2;

        uint16_t conflict_size = 0;
        for (uint8_t l = 0; l < n_links; l++)
        {
            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                if (confLinkMatrix[link->id][l][c])
                {
                    conflict_size++;
                }
            }
        }

        Tree_t *subtree = getSubTree(cmst, n1);
        uint16_t subtree_size = subtree->weight;

        uint16_t good_channel_size = 0;
        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            if (etxMatrix[n1->id][n2->id][c] <= (1.0/ETX_THRESHOLD) && etxMatrix[n2->id][n1->id][c] <= (1.0/ETX_THRESHOLD))
            {
                good_channel_size++;
            }
        }

        /* Set the weight of the link */
        link->weight = (THETA * subtree_size + KAPPA * conflict_size) / (PHI * good_channel_size);

    }

    /* Copy list linksList to Lp */
    List Lp; memset(&Lp, 0, sizeof(List)); ListInit(&Lp);
    for (ListElem *elem1 = ListFirst(&linksList); elem1 != NULL; elem1 = ListNext(&linksList, elem1))
    {
        Link_t *link1 = (Link_t *)elem1->obj;

        ListElem *elem2;
        for (elem2 = ListFirst(&Lp); elem2 != NULL; elem2 = ListNext(&Lp, elem2))
        {
            Link_t *link2 = (Link_t *)elem2->obj;

            if (link1->weight > link2->weight)
            {
                ListInsertBefore(&Lp, (void *)link1, elem2);
                break;
            }
        }

        if (elem2 == NULL)
        {
            ListAppend(&Lp, (void *)link1);
        }
    }

    while (!ListEmpty(&Lp))
    {
        ListElem *elem = ListFirst(&Lp);
        Link_t *link = (Link_t *)elem->obj;

        for (uint8_t i = 0; i < NUM_CHANNELS; i++)
        {
            uint8_t cl = ch_order[link->id][i];

            bool conflict = false;
            for (ListElem *elem = ListFirst(&CA[cl]); elem != NULL; elem = ListNext(&CA[cl], elem))
            {
                Link_t *link_conf = (Link_t *)elem->obj;
                if (confLinkMatrix[link->id][link_conf->id][cl])
                {
                    conflict = true;
                }
            }

            if (!conflict)
            {
                ListAppend(&CA[cl], (void *)link);
                break;
            }
        }

        ListUnlink(&Lp, elem);
    }

    /* Going over all links and updating the time slot information of the pair of nodes */
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        for (ListElem *elem = ListFirst(&CA[c]); elem != NULL; elem = ListNext(&CA[c], elem))
        {
            Link_t *link = (Link_t *)elem->obj;

            Node_t *n1 = link->n1;

            for (ListElem *elem2 = ListFirst(&n1->timeslots); elem2 != NULL; elem2 = ListNext(&n1->timeslots, elem2))
            {
                TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;

                if (ts->type == TS_TX)
                {
                    ts->freq = c;
                    TimeSlot_t *ts2 = getTimeSlot(ts->time, &link->n2->timeslots);
                    ts2->freq = c;
                }
            }
        }
    }

    return (true);
}

bool paintNodes(List *nodesSorted, bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel)
{
    uint8_t n_nodes = ListLength(nodesSorted);
    bool paintedOneNode = false;    /* Check if you could paint at least one node */

    /* Paint each node */
    for (ListElem *elem1 = ListFirst(nodesSorted); elem1 != NULL; elem1 = ListNext(nodesSorted, elem1))
    {
        uint8_t color = 1;
        Node_t *nodeToColor = (Node_t *)elem1->obj;

        /* Check if we already have used this color */
        while (ListFind(&nodeToColor->channels, (void *)color))
        {
            color++;
        }

        /* Check if there is any neighbor of ith node with this color */
        bool foundColor = false;
        while (!foundColor)
        {
            uint8_t old_color = color;

            /* Look at all nodes with conflict */
            for (ListElem *elem2 = ListFirst(nodesSorted); elem2 != NULL; elem2 = ListNext(nodesSorted, elem2))
            {
                Node_t *n = (Node_t *)elem2->obj;

                if (confMatrix[nodeToColor->id][n->id][channel] == true)
                {
                    if (ListFind(&n->channels, (void *)color))
                    {
                        color++;
                        /* Check if we already have used this color */
                        while (ListFind(&nodeToColor->channels, (void *)color))
                        {
                            color++;
                        }
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

        if (color < NUM_CHANNELS)
        {
            /* Paint the node with the right color */
            ListAppend(&nodeToColor->channels, (void *)color);
            paintedOneNode = true;
        }
    }

    return (paintedOneNode);
}
