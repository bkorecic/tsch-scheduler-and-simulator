#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "graphs.h"
#include "../util/defs.h"
#include "../util/debug.h"
#include "../mcc/time_schedule.h"

Link_t *newLink(Node_t *n1, Node_t *n2, float etx, uint8_t ch, LINK_TYPE type, uint8_t link_id)
{
    Link_t* link = (Link_t*)malloc(sizeof(Link_t));

    if (link == NULL)
    {
        EXIT("Not enough memory.\n");
    }
    else
    {
        memset(link, '\0', sizeof(Link_t));
    }

    link->n1 = n1;
    link->n2 = n2;
    link->weight = 1;
    link->etx = etx;
    link->type = type;
    link->channel = ch;
/* MODESA IP code */
    link->id = link_id;
/* MODESA IP code */

    return link;
}

Node_t *newNode(uint16_t id, NODE_TYPE type)
{
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));

    if (node == NULL)
    {
        EXIT("Not enough memory.\n");
    }
    else
    {
        memset(node, '\0', sizeof(Node_t));
    }

    node->id = id;
    node->type = type;
    memset(&(node->timeslots), 0, sizeof(List)); ListInit(&(node->timeslots));
    memset(&(node->packets), 0, sizeof(List)); ListInit(&(node->packets));

/* MCC code */
    memset(&(node->channels), 0, sizeof(List)); ListInit(&(node->channels));
    node->hop_count = MAX_HOP_COUNT;
    memset(&(node->candidate_parents), 0, sizeof(List)); ListInit(&(node->candidate_parents));
    memset(&(node->candidate_children), 0, sizeof(List)); ListInit(&(node->candidate_children));
    memset(&(node->gs), 0, sizeof(List)); ListInit(&(node->gs));
/* MCC code */

/* MODESA code */
    node->priority = 1;
    node->interfaces = 1;
/* MODESA code */

/* MODESA IP code */
    memset(&(node->links_tx), 0, sizeof(List)); ListInit(&(node->links_tx));
    memset(&(node->links_rx), 0, sizeof(List)); ListInit(&(node->links_rx));
    memset(&(node->nodes_int), 0, sizeof(List)); ListInit(&(node->nodes_int));
/* MODESA IP code */

/* Schedule */
    node->pkt_tx_failed = node->pkt_tx_success = node->pkt_rx_failed = node->pkt_rx_success = 0;
/* Schedule */

/* Blacklist */
    memset(node->avg_reward, 0, MAX_NODES*NUM_CHANNELS);
    node->cumulative_regret = 0;
    node->optimal_freq = 0;
/* Blacklist */

    return node;
}

Tree_t *newTree(Node_t *root, TREE_TYPE type)
{
    Tree_t *tree = (Tree_t *)malloc(sizeof(Tree_t));

    if (tree == NULL)
    {
        ERROR("Not enough memory.\n");
    }
    else
    {
        memset(tree, '\0', sizeof(Tree_t));
    }

    tree->root = root;

    memset(&(tree->subtrees_list), 0, sizeof(List)); ListInit(&(tree->subtrees_list));
    memset(&(tree->children_list), 0, sizeof(List)); ListInit(&(tree->children_list));

    tree->weight = 1;
    tree->type = type;

/* TASA code */
    tree->valid = 0;
/* TASA code */

    return tree;
}

LineTree_t *newLineTree(uint8_t hop_count)
{
    LineTree_t *lineTree = (LineTree_t *)malloc(sizeof(LineTree_t));

    if (lineTree == NULL)
    {
        ERROR("Not enough memory.\n");
    }
    else
    {
        memset(lineTree, 0, sizeof(LineTree_t));
    }

    lineTree->hop = hop_count;

    return (lineTree);
}

TimeSlot_t *newTimeSlot(uint16_t time, uint8_t freq, TIMESLOT_TYPE type, Node_t *neighbor, bool relay)
{
    TimeSlot_t *ts = (TimeSlot_t *)malloc(sizeof(TimeSlot_t));

    if (ts == NULL)
    {
        ERROR("Not enough memory.\n");
    }
    else
    {
        memset(ts, 0, sizeof(TimeSlot_t));
    }

    ts->time = time;
    ts->freq = freq;
    ts->type = type;
    if ((type != TS_SHARED) && (type != TS_BEACON))
    {
        ts->neighbor = neighbor;
    }
    ts->relay = relay;

    return (ts);
}

Packet_t *newPacket(uint16_t dsn, uint16_t src_id, uint64_t ts_generated, uint16_t burst_id)
{
    Packet_t *pkt = (Packet_t *)malloc(sizeof(Packet_t));

    if (pkt == NULL)
    {
        ERROR("Not enough memory.\n");
    }
    else
    {
        memset(pkt, 0, sizeof(Packet_t));
    }

    pkt->dsn = dsn;
    pkt->src_id = src_id;
    pkt->relay_id = src_id;
    pkt->ts_generated = ts_generated;
    pkt->burst_id = burst_id;

    return (pkt);
}

bool isNodeInTree(Node_t *node, Tree_t *tree, Node_t *avoidRoot)
{
    if (tree->root != avoidRoot && tree->root->id == node->id)
    {
        return (true);
    }
    else
    {
        ListElem *elem = NULL;
        for (elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
        {
            /* Get the current subtree */
            Tree_t *subtree = (Tree_t *)elem->obj;

            if (subtree->root != avoidRoot)
            {
                /* Call recursively the function for the neighbor */
                if(isNodeInTree(node, subtree, avoidRoot))
                {
                    return (true);
                }
            }
        }
        return (false);
    }
}

Node_t *getParent(Tree_t *tree, Node_t *node)
{
    /* Lets check if the node is in our list of children */
    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        /* Found the node, I am the parent */
        if (subTree->root->id == node->id)
        {
            return (tree->root);
        }
    }

    /* Search recursively for all the children in the tree */
    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;
        Node_t *parent = NULL;
        if ((parent = getParent(subTree, node)) != NULL)
        {
            return (parent);
        }
    }

    return (NULL);
}

Node_t *connectToTreeAnyParent(Node_t *new_node, Tree_t *tree)
{
    for (ListElem *elem = ListFirst(&new_node->candidate_parents); elem != NULL; elem = ListNext(&new_node->candidate_parents, elem))
    {
        Node_t *parent = (Node_t *)elem->obj;

        if (isNodeInTree(parent, tree, NULL))
        {
            connectToTree(new_node, parent, tree);

            return (parent);
        }
    }
    return (NULL);
}

bool connectToTree(Node_t *new_node, Node_t *parent, Tree_t *tree)
{
    if (tree->root->id == parent->id)
    {
        Tree_t *subtree = newTree(new_node, BRANCH);
        ListAppend(&tree->subtrees_list, subtree);
        tree->weight++;
        new_node->type = CONNECTED;

        return (true);
    }
    else
    {
        for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
        {
            /* Get the current subtree */
            Tree_t *subtree = (Tree_t *)elem->obj;

            /* Call recursively the function for the subtree */
            if(connectToTree(new_node, parent, subtree))
            {
                tree->weight++;

                return (true);
            }
        }
        return (false);
    }
}

void printTree(Tree_t *tree)
{
    PRINTF("\nNode %d(%d) [ ", tree->root->id, tree->weight);
    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        /* Get the current subtree */
        Tree_t *subtree = (Tree_t *)elem->obj;

        PRINTF("%d ", subtree->root->id);
    }
    PRINTF("]\n");

    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        /* Get the current subtree */
        Tree_t *subtree = (Tree_t *)elem->obj;
        printTree(subtree);
    }
    fflush(stdout);
}

void setTypeOfNodes(uint8_t sink_id, Tree_t *tree)
{
    if (ListLength(&tree->subtrees_list) == 0)
    {
        if (tree->root->id == sink_id)
        {
            tree->root->type = SINK;
        }
        else
        {
            tree->root->type = LEAF;
        }
    }
    else
    {
        if (tree->root->id == sink_id)
        {
            tree->root->type = SINK;
        }
        else
        {
            tree->root->type = RELAY;
        }
        for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
        {
            /* Get the current subtree */
            Tree_t *subtree = (Tree_t *)elem->obj;
            setTypeOfNodes(sink_id, subtree);
        }
    }
    return;
}

void printLineTree(LineTree_t *lineTree)
{
    PRINTF("\nHop %d [ ", lineTree->hop);
    for (ListElem *elem = ListFirst(lineTree->nodes); elem != NULL; elem = ListNext(lineTree->nodes, elem))
    {
        /* Get the current subtree */
        Node_t *node = (Node_t *)elem->obj;

        PRINTF("%d ", node->id);
    }
    PRINTF("]\n");

    if (lineTree->nextTree != NULL)
    {
        printLineTree(lineTree->nextTree);
    }
}

void printListNodes(List *nodesList)
{
    PRINTF("\nList of nodes:\n");
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        /* Get the current node */
        Node_t *n1 = (Node_t *)elem1->obj;

        PRINTF("[ID: %d, TYPE: ", n1->id);

        switch(n1->type)
        {
            case SINK:
                PRINTF("Sink");
                break;
            case RELAY:
                PRINTF("Relay");
                break;
            case LEAF:
                PRINTF("Leaf");
                break;
            default:
                PRINTF("Undefined");
                break;
        }

        PRINTF(", Parents: ");
        for (ListElem *elem2 = ListFirst(&n1->candidate_parents); elem2 != NULL; elem2 = ListNext(&n1->candidate_parents, elem2))
        {
            Node_t *n2 = (Node_t *)elem2->obj;

            PRINTF("%d ", n2->id);
        }

        PRINTF(", Children: ");
        for (ListElem *elem2 = ListFirst(&n1->candidate_children); elem2 != NULL; elem2 = ListNext(&n1->candidate_children, elem2))
        {
            Node_t *n2 = (Node_t *)elem2->obj;

            PRINTF("%d ", n2->id);
        }
        PRINTF(", Channels: ");
        for (ListElem *elem2 = ListFirst(&n1->channels); elem2 != NULL; elem2 = ListNext(&n1->channels, elem2))
        {
            uint8_t c = (uint8_t)elem2->obj;

            PRINTF("%d ", c);
        }
        PRINTF(", TS: ");
        for (ListElem *elem2 = ListFirst(&n1->timeslots); elem2 != NULL; elem2 = ListNext(&n1->timeslots, elem2))
        {
            TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;

            if (ts->type == TS_BEACON) PRINTF("[%d,%d,%s] ", ts->time, ts->freq, ("BEACON"));
            else if (ts->type == TS_SHARED) PRINTF("[%d,%d,%s] ", ts->time, ts->freq, ("SHARED"));
            else if (ts->type == TS_IDLE) PRINTF("[%d,%d,%s] ", ts->time, ts->freq, ("IDLE"));
            else if (ts->type == TS_TX) PRINTF("[%d,%d,%s] ", ts->time, ts->freq, ("TX"));
            else if (ts->type == TS_RX) PRINTF("[%d,%d,%s] ", ts->time, ts->freq, ("RX"));
            else PRINTF("[%d,%d,%s] ", ts->time, ts->freq, ("UNDEFINED"));
        }
        PRINTF("\n");
    }
    fflush(stdout);
}

Tree_t *getTree(uint16_t root_id, List *treesList)
{
    for (ListElem *elem = ListFirst(treesList); elem != NULL; elem = ListNext(treesList, elem))
    {
        /* Get the current Node */
        Tree_t *t = (Tree_t *)elem->obj;
        if (t->root->id == root_id)
        {
            return t;
        }
    }
    return (NULL);
}

Node_t *getNode(uint16_t node_id, List *nodesList)
{
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* Get the current Node */
        Node_t *n = (Node_t *)elem->obj;
        if (n->id == node_id)
        {
            return n;
        }
    }
    return (NULL);
}

TimeSlot_t *getTimeSlot(uint16_t time, List *timeList)
{
    for (ListElem *elem = ListFirst(timeList); elem != NULL; elem = ListNext(timeList, elem))
    {
        /* Get the current Time slot */
        TimeSlot_t *ts = (TimeSlot_t *)elem->obj;

        if (ts->time == time)
        {
            return (ts);
        }
    }
    return (NULL);
}

bool createPrrMatrix (uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[])
{
    memset(prrMatrix, 0, MAX_NODES * MAX_NODES * NUM_CHANNELS * sizeof(uint8_t));

    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        for (ListElem *elem = ListFirst(&linksList[c]); elem != NULL; elem = ListNext(&linksList[c], elem))
        {
            /* Get the current Link */
            Link_t *link = (Link_t *)elem->obj;

            uint8_t prr = (uint8_t)(1.0/link->etx*100);
            prrMatrix[link->n1->id][link->n2->id][c] = prr;
        }
    }

    return (true);
}

bool createEtxMatrix (float etxMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[])
{
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        for (ListElem *elem = ListFirst(&linksList[c]); elem != NULL; elem = ListNext(&linksList[c], elem))
        {
            /* Get the current Link */
            Link_t *link = (Link_t *)elem->obj;

            etxMatrix[link->n1->id][link->n2->id][c] = link->etx;
        }

        for (uint8_t i = 0; i < MAX_NODES; i++)
        {
            for (uint8_t j = 0; j < MAX_NODES; j++)
            {
                if (etxMatrix[i][j][c] == 0) etxMatrix[i][j][c] = FLT_MAX;
            }
        }
    }

    return (true);
}

bool createConnectivityMatrix (bool conMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[], float con_thr)
{
    /* We need to insert connections only when both directions are with good ETX */

    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        /* First we insert all good links in conMatrix */
        for (ListElem *elem = ListFirst(&linksList[c]); elem != NULL; elem = ListNext(&linksList[c], elem))
        {
            /* Get the current Link */
            Link_t *link = (Link_t *)elem->obj;
            if (link->etx <= con_thr)
            {
                /* Inserting n1 -> n2 link into the matrix */
                conMatrix[link->n1->id][link->n2->id][c] = true;

                /* Check if the link is bidirectional */
                if (link->type == BIDIRECTIONAL)
                {
                    conMatrix[link->n2->id][link->n1->id][c] = true;
                }
            }
        }
    }

    /* Now we pass thru the list a second time and check if both directions are good */
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        for (ListElem *elem = ListFirst(&linksList[c]); elem != NULL; elem = ListNext(&linksList[c], elem))
        {
            /* Get the current Link */
            Link_t *link = (Link_t *)elem->obj;
            if (link->etx <= con_thr)
            {
                /* Check the reverse direction link */
                if (conMatrix[link->n2->id][link->n1->id][c] == false)
                {
                    conMatrix[link->n1->id][link->n2->id][c] = false;
                }
            }
        }
    }
    return (true);
}

bool createInterferenceMatrix(bool intMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[], float int_thr)
{
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        for (ListElem *elem = ListFirst(&linksList[c]); elem != NULL; elem = ListNext(&linksList[c], elem))
        {
            /* Get the current Link */
            Link_t *link = (Link_t *)elem->obj;
            if (link->etx >= int_thr)
            {
                /* Inserting n1 -> n2 link into the matrix */
                intMatrix[link->n1->id][link->n2->id][c] = true;

                /* Check if the link is bidirectional */
                if (link->type == BIDIRECTIONAL)
                {
                    intMatrix[link->n2->id][link->n1->id][c] = true;
                }
            }
        }
    }
    return (true);
}

bool createConflictMatrix(Tree_t *tree, bool intMatrix[][MAX_NODES][NUM_CHANNELS], List nodesList[], bool confMatrix[][MAX_NODES][NUM_CHANNELS], bool withSchedule)
{
    uint8_t n_nodes = ListLength(nodesList);

    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            /* Lets get the list of nodes that conflict with i in 2 hops */
            List *conflictNodes = getConflictingNodes(i, i, nodesList, intMatrix, c, 2);

            for (ListElem *elem=ListFirst(conflictNodes); elem != NULL; elem = ListNext(conflictNodes, elem))
            {
                Node_t *confNode = (Node_t *)elem->obj;

                confMatrix[i][confNode->id][c] = true;
            }
            ListUnlinkAll(conflictNodes);
        }
    }

    /* If we are going to consider the time slot schedule */
    if (withSchedule)
    {
        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
            {
                Node_t *node_i = (Node_t *)elem1->obj;

                for (ListElem *elem2 = ListFirst(nodesList); elem2 != NULL; elem2 = ListNext(nodesList, elem2))
                {
                    Node_t *node_j = (Node_t *)elem2->obj;

                    /* If nodes have a conflict */
                    if (confMatrix[node_i->id][node_j->id][c])
                    {
                        /* But they do not share any time slot, we can remove the conflict */
                        if (!shareTimeSlots(tree, node_i, node_j))
                        {
                            confMatrix[node_i->id][node_j->id][c] = false;
                            confMatrix[node_j->id][node_i->id][c] = false;
                        }
                    }
                }
            }
        }
    }

    return (true);
}

List *getConflictingNodes(uint8_t node_id, uint8_t last_node_id, List *nodesList, bool intMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t channel, uint8_t hops)
{
    uint8_t n_nodes = ListLength(nodesList);

    /* Create a new list */
    List *list = (List *)malloc(sizeof(List));
    memset(list, 0, sizeof(List));
    ListInit(list);

    if (hops == 1)
    {
        /* Insert all nodes that interfere with you directly */
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            if (intMatrix[node_id][i][channel] == true && i != last_node_id)
            {
                ListAppend(list, (void *)getNode(i, nodesList));
            }
        }
    }
    else
    {
        /* Look for all neighbors that interfere with you */
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            if (intMatrix[node_id][i][channel] == true && i != last_node_id)
            {
                Node_t *n1 = getNode(i, nodesList);

                /* Insert current node into the list if it is not there yet */
                if (!ListFind(list, (void *)n1))
                {
                    ListAppend(list, (void *)n1);
                }
                List *listNeighbor = getConflictingNodes(i, node_id, nodesList, intMatrix, channel, hops -1);

                for (ListElem *elem = ListFirst(listNeighbor); elem != NULL; elem = ListNext(listNeighbor, elem))
                {
                    Node_t *n2 = (Node_t *)elem->obj;
                    /* Insert current node into the list if it is not there yet */
                    if (n2->id != node_id && !ListFind(list, (void *)n2))
                    {
                        ListAppend(list, (void *)n2);
                    }
                }

                ListUnlinkAll(listNeighbor);
            }
        }
    }

    return (list);
}

uint16_t totalTraffic(List *nodesList)
{
    uint16_t Q = 0;
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        Q += node->q;
    }

    return (Q);
}

Tree_t *getSubTree(Tree_t *tree, Node_t *root)
{
    if (tree->root->id == root->id)
    {
        return (tree);
    }
    else
    {
        for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
        {
            Tree_t *tree = getSubTree((Tree_t *)elem->obj, root);

            if (tree != NULL)
            {
                return (tree);
            }
        }
    }

    return (NULL);
}

void getListNodesInTree(Tree_t *tree, List *listResult)
{
    ListAppend(listResult, (void *)tree->root);

    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        getListNodesInTree(subTree, listResult);
    }
}

void validadeAllSubtrees(Tree_t *tree)
{
    tree->valid = true;

    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        validadeAllSubtrees(subTree);
    }
}

void printListLinks(List *linksList)
{
    for (ListElem *elem = ListFirst(linksList); elem != NULL; elem = ListNext(linksList, elem))
    {
        Link_t *link = (Link_t *)elem->obj;

        PRINTF("Link (%d,%d) Etx %f\n", link->n1->id, link->n2->id, link->etx);
    }
}

void updateTreeHopCount(Tree_t *tree, uint8_t init_count)
{
    tree->root->hop_count = init_count;

    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        updateTreeHopCount(subTree, init_count + 1);
    }
}

void generateLinksList(Tree_t *tree, List *linksList)
{
    /* We also uniquely identify each link */
    static uint8_t link_id = 0;

    if (tree != NULL)
    {
        for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
        {
            Tree_t *subTree = (Tree_t *)elem->obj;

            /* Create the new link */
            Link_t *link = newLink(subTree->root, tree->root, 1, 0, UNIDIRECTIONAL, link_id);

            /* Append it to the list of links */
            ListAppend(linksList, (void *)link);

            /* Insert into the list of RX and TX links of both nodes */
            ListAppend(&subTree->root->links_tx, (void *)link);
            ListAppend(&tree->root->links_rx, (void *)link);

            /* Increment the link ID */
            link_id++;

            generateLinksList(subTree, linksList);
        }
    }
}

void generateNodesInterfering(bool confMatrix[][MAX_NODES][NUM_CHANNELS], List *nodesList, int8_t channel)
{
    for (uint8_t i = 0; i < ListLength(nodesList); i++)
    {
        Node_t *node_i = getNode(i, nodesList);

        for (uint8_t j = 0; j < ListLength(nodesList); j++)
        {
            if (confMatrix[i][j][channel])
            {
                Node_t *node_j = getNode(j, nodesList);

                /* Insert the node into the list of interfering nodes */
                ListAppend(&node_i->nodes_int, (void *)node_j);
            }
        }
    }
}
