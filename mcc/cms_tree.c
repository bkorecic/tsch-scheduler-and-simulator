#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include "cms_tree.h"
#include "../graphs/graphs.h"
#include "../util/defs.h"
#include "../util/debug.h"

Tree_t *constructCMSTreeSingleChannel(Node_t *sink, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t channel)
{
    int max_hop_count = 0, i = 0;

    /* Create the output tree rooted at sink */
    Tree_t *cmst = newTree(sink, CMS);

    /* Calculate the hop count, candidate parents and candidate children of all nodes and update nodesList */
    constructHopCountParentsAndChildren(sink, nodesList, conMatrix, channel);

    /* Check if all nodes have at least one candidate parent. Otherwise stop the execution */
    checkAllNodesHaveParents(nodesList);

    /* Print the list of nodes with their candidate parents and children */
    printListNodes(nodesList);

    /* Insert all nodes with hop count 1 as branches of the root */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        if (node->hop_count == 1)
        {
            /* Add the node as a new branch to the final tree */
            connectToTree(node, cmst->root, cmst);
        }

        /* Calculate the maximum hop count */
        if (node->hop_count > max_hop_count)
        {
            max_hop_count = node->hop_count;
        }
    }

    /* Calculate the growth set for all nodes */
    constructGS(cmst, nodesList, conMatrix, channel);

    /* Create an array with all branches. They will form the fat tree we are going to work with */
    Tree_t *branches[ListLength(&cmst->subtrees_list)];
    i = 0;
    for (ListElem *elem = ListFirst(&cmst->subtrees_list); elem != NULL; elem = ListNext(&cmst->subtrees_list, elem))
    {
        /* Get the current node */
        Tree_t *tree = (Tree_t *)elem->obj;

        branches[i++] = createTree(tree->root, nodesList);
    }

    /* Printing the fat branches */
    for (i = 0; i < ListLength(&cmst->subtrees_list); i++)
    {
        PRINTF("\nBranch %d", i+1);
        printTree(branches[i]);
    }

    /* While h < max_hop_count */
    for (int h=2; h<=max_hop_count; h++)
    {
        /* Find all unconnected nodes at hop h */
        List unconnectedNodes; memset(&unconnectedNodes, 0, sizeof(List)); ListInit(&unconnectedNodes);

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
             Node_t *node = (Node_t *)elem1->obj;

            /* If node is at hop count h and is not connected yet */
            if (node->hop_count == h && !isNodeInTree(node, cmst, NULL))
            {
                /* If node has one single candidate parent, connect it to the tree */
                if (ListLength(&node->candidate_parents) == 1)
                {
                    connectToTree(node, (Node_t *)ListFirst(&node->candidate_parents)->obj, cmst);
                }
                /* Else, insert into the list of unconnected nodes */
                else
                {
                    ListAppend(&unconnectedNodes, node);
                }
            }
        }

        /* Sort the unconnected list in non-increasing order of gs */
        List unconnectedNodes_sorted; memset(&unconnectedNodes_sorted, 0, sizeof(List)); (void)ListInit(&unconnectedNodes_sorted);

        sortListNonIncreasingByGS(&unconnectedNodes, &unconnectedNodes_sorted);

        /* Printing statistics or debug */
        PRINTF("--- h %d\n", h);
        PRINTF("CMST:\n"); printTree(cmst);
        PRINTF("Fat branches:\n");
        for (i = 0; i<ListLength(&cmst->subtrees_list); i++)
        {
            PRINTF("Branch %d", i+1);
            printTree(branches[i]);
        }
        PRINTF("Unsorted list:"); printListNodes(&unconnectedNodes);
        PRINTF("Sorted list:"); printListNodes(&unconnectedNodes_sorted);
        PRINTF("---");

        /* Going over all unconnected nodes in non-increasing order of |GS| */
        for (ListElem *elem2 = ListFirst(&unconnectedNodes_sorted); elem2 != NULL; elem2 = ListNext(&unconnectedNodes_sorted, elem2))
        {
            Node_t *node = (Node_t *)elem2->obj;

            /* Find all branches the node can connect to */
            List *branchesList = branchesNodeIsConnectTo(node, branches, ListLength(&cmst->subtrees_list), NULL);

            /* Lets create an array with all SS (search set) of all branches the node can connect to */
            List *SS[ListLength(branchesList)];

            /* Going over all branches and creating the corresponding SS */
            i = 0;
            for (ListElem *elem3 = ListFirst(branchesList); elem3 != NULL; elem3 = ListNext(branchesList, elem3))
            {
                Tree_t *branch = (Tree_t *)elem3->obj;

                SS[i++] = createSS(node, branch, nodesList, branches, ListLength(&cmst->subtrees_list));
            }

            /* Lets find the branch b with smaller W(b) + |SS| */
            int weight = INT_MAX;   /* Holds the maximum weight */
            int index = 0;          /* Holds the indes of the maximum weight */
            Tree_t *b = NULL;       /* Holds the branch b */
            i = 0;
            for (ListElem *elem3 = ListFirst(branchesList); elem3 != NULL; elem3 = ListNext(branchesList, elem3))
            {
                Tree_t *t = (Tree_t *)elem3->obj;

                /* Find the corresponding branch in the CMST to check its weight */
                Tree_t *cmstBranch = getTree(t->root->id, &cmst->subtrees_list);

                /* Find the branch with minimum weight + |SS| */
                if (cmstBranch->weight + ListLength(SS[i++]) < weight)
                {
                    index = i-1;
                    b = cmstBranch;
                    weight = cmstBranch->weight + ListLength(SS[i-1]);
                }
            }

            /* Connect node to branch b */
            Node_t *parent = connectToTreeAnyParent(node, b);
            cmst->weight++; /* We need to add one manually the CMST root weigth */

            /* Remove all other connections in the fat tree to that node */
            for (i = 0; i < ListLength(&cmst->subtrees_list); i++)
            {
                disconnectOtherParents(node, branches[i], parent);
            }

            /* Connect all nodes in SS to the cmst */
            for (ListElem *elem3 = ListFirst(SS[index]); elem3 != NULL; elem3 = ListNext(SS[index], elem3))
            {
                Node_t *ss_node = (Node_t *)elem3->obj;

                /* Connect ss_node to branch b */
                connectToTreeAnyParent(ss_node, b);
                cmst->weight++; /* We need to add one manually the CMST root weigth */

                /* Remove all other connections in the fat tree to that node */
                for (i = 0; i < ListLength(&cmst->subtrees_list); i++)
                {
                    disconnectOtherParents(ss_node, branches[i], parent);
                }
            }

            /* Update the GS of node i */
            updateGS(cmst, node, nodesList, conMatrix, channel);
        }
    }

    return (cmst);
}

Tree_t *constructCMSTreeMultipleChannel(Node_t *sink, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[])
{
    int max_hop_count = 0, i = 0;

    /* Create the output tree rooted at sink */
    Tree_t *cmst = newTree(sink, CMS);

    /* Calculate the hop count, candidate parents and candidate children of all nodes and update nodesList */
    constructHopCountParentsAndChildren(sink, nodesList, conMatrix, -1);

    /* Print the list of nodes with their candidate parents and children */
    printListNodes(nodesList);

    /* Insert all nodes with hop count 1 as branches of the root and calculate the max hop count */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        if (node->hop_count == 1)
        {
            /* Add the node as a new branch to the final tree */
            connectToTree(node, cmst->root, cmst);
        }

        /* Calculate the maximum hop count */
        if (node->hop_count > max_hop_count)
        {
            max_hop_count = node->hop_count;
        }
    }

    /* Calculate the growth set for all nodes */
    constructGS(cmst, nodesList, conMatrix, -1);

    /* Create an array with all branches. They will form the fat tree we are going to work with */
    Tree_t *branches[ListLength(&cmst->subtrees_list)];
    i = 0;
    for (ListElem *elem = ListFirst(&cmst->subtrees_list); elem != NULL; elem = ListNext(&cmst->subtrees_list, elem))
    {
        /* Get the current node */
        Tree_t *tree = (Tree_t *)elem->obj;

        branches[i++] = createTree(tree->root, nodesList);
    }

    /* Printing the fat branches */
    for (i = 0; i < ListLength(&cmst->subtrees_list); i++)
    {
        PRINTF("\nBranch %d", i+1);
        printTree(branches[i]);
    }

    /* While h < max_hop_count */
    for (int h = 2; h <= max_hop_count; h++)
    {
        /* Find all unconnected nodes at hop h */
        List unconnectedNodes; memset(&unconnectedNodes, 0, sizeof(List)); ListInit(&unconnectedNodes);

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
             Node_t *node = (Node_t *)elem1->obj;

            /* If node is at hop count h and is not connected yet */
            if (node->hop_count == h && !isNodeInTree(node, cmst, NULL))
            {
                /* If node has one single candidate parent, connect it to the tree */
                if (ListLength(&node->candidate_parents) == 1)
                {
                    connectToTree(node, (Node_t *)ListFirst(&node->candidate_parents)->obj, cmst);
                }
                /* Else, insert into the list of unconnected nodes */
                else
                {
                    ListAppend(&unconnectedNodes, node);
                }
            }
        }

        /* Sort the unconnected list in non-increasing order of gs */
        List unconnectedNodes_sorted; memset(&unconnectedNodes_sorted, 0, sizeof(List)); (void)ListInit(&unconnectedNodes_sorted);

        sortListNonIncreasingByGS(&unconnectedNodes, &unconnectedNodes_sorted);

        /* Printing statistics or debug */
        PRINTF("--- h %d\n", h);
        PRINTF("CMST:\n"); printTree(cmst);
        PRINTF("Fat branches:\n");
        for (i = 0; i < ListLength(&cmst->subtrees_list); i++)
        {
            PRINTF("Branch %d", i+1);
            printTree(branches[i]);
        }
        PRINTF("Unsorted list:"); printListNodes(&unconnectedNodes);
        PRINTF("Sorted list:"); printListNodes(&unconnectedNodes_sorted);
        PRINTF("---");

        /* Going over all unconnected nodes in non-increasing order of |GS| */
        for (ListElem *elem2 = ListFirst(&unconnectedNodes_sorted); elem2 != NULL; elem2 = ListNext(&unconnectedNodes_sorted, elem2))
        {
            Node_t *node = (Node_t *)elem2->obj;

            /* Find all branches the node can connect to */
            List *branchesList = branchesNodeIsConnectTo(node, branches, ListLength(&cmst->subtrees_list), NULL);

            /* If n can only connect to one branch */
            if (ListLength(branchesList) == 1)
            {
                connectToParentMaxChannelVar(node, cmst, conMatrix);
            }
            else
            {
                /* Calculate U, the number of unconnected nodes */
                uint16_t u = ListLength(nodesList) - cmst->weight;
                float n_plus_one_over_two = (ListLength(nodesList) + 1.0)/2.0;
                bool flag = true;

                /* Check if W(b) + |U| < (N+1)/2 for all branches */
                for (ListElem *elem3 = ListFirst(branchesList); elem3 != NULL; elem3 = ListNext(branchesList, elem3))
                {
                    Tree_t *b = (Tree_t *)elem3->obj;

                    Tree_t *cmstBranch = getTree(b->root->id, &cmst->subtrees_list);
                    if (cmstBranch->weight + u >= n_plus_one_over_two)
                    {
                        flag = false;
                        break;
                    }
                }

                /* W(b) + |U| < (N+1)/2 for all branches */
                if (flag)
                {
                    connectToParentMaxChannelVar(node, cmst, conMatrix);
                }
                else
                {

                    /* Lets create an array with all SS (search set) of all branches the node can connect to */
                    List *SS[ListLength(branchesList)];

                    /* Going over all branches and creating the corresponding SS */
                    i = 0;
                    for (ListElem *elem3 = ListFirst(branchesList); elem3 != NULL; elem3 = ListNext(branchesList, elem3))
                    {
                        Tree_t *branch = (Tree_t *)elem3->obj;

                        SS[i++] = createSS(node, branch, nodesList, branches, ListLength(&cmst->subtrees_list));
                    }

                    PRINTF("SS for node %d\n", node->id);
                    for (uint8_t x = 0; x < ListLength(branchesList); x++)
                    {
                        PRINTF("\nSS[%d] = ", x);
                        for (ListElem *elem9 = ListFirst(SS[x]); elem9 != NULL; elem9 = ListNext(SS[x], elem9))
                        {
                            Node_t *node9 = (Node_t *)elem9->obj;
                            PRINTF("%d, ", node9->id);
                        }
                        PRINTF("\n");
                    }

                    /* Lets find the candidate parent with minimum weight */
                    float weight = FLT_MAX;   /* Holds the maximum weight */
                    Node_t *best_parent = NULL;
                    Tree_t *b = NULL;       /* Holds the branch b */
                    i = 0;
                    for (ListElem *elem3 = ListFirst(branchesList); elem3 != NULL; elem3 = ListNext(branchesList, elem3))
                    {
                        Tree_t *t = (Tree_t *)elem3->obj;

                        /* Find the corresponding branch in the CMST to check its weight */
                        Tree_t *cmstBranch = getTree(t->root->id, &cmst->subtrees_list);

                        /* Look for all candidate parents and use the one with maximum channel variety */
                        for (ListElem *elem4 = ListFirst(&node->candidate_parents); elem4 != NULL; elem4 = ListNext(&node->candidate_parents, elem4))
                        {
                            Node_t *p = (Node_t *)elem4->obj;

                            if (isNodeInTree(p, cmstBranch, NULL))
                            {
                                uint8_t ch_var = calculateChannelVar(node, p, conMatrix);

                                /* Find the parent with minimum weight */
                                float new_weight = ALPHA *(cmstBranch->weight + ZETA * ListLength(SS[i])) - BETA * ch_var;
                                if (new_weight < weight)
                                {
                                    b = cmstBranch;
                                    weight = new_weight;
                                    best_parent = p;
                                }
                            }
                        }
                        i++;
                    }

                    connectToTree(node, best_parent, b);
                    cmst->weight++; /* We need to add one manually the CMST root weigth */

                    /* Remove all other connections in the fat tree to that node */
                    for (i = 0; i < ListLength(&cmst->subtrees_list); i++)
                    {
                        disconnectOtherParents(node, branches[i], best_parent);
                    }
                }
            }

            /* Update the GS of node i */
            updateGS(cmst, node, nodesList, conMatrix, -1);
        }
    }

    return (cmst);
}

uint8_t calculateChannelVar(Node_t *node, Node_t *parent, bool conMatrix[][MAX_NODES][NUM_CHANNELS])
{
    uint8_t ch_var = 0;

    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        if (conMatrix[node->id][parent->id][c])
        {
            ch_var++;
        }
    }

    return (ch_var);
}

int disconnectOtherParents(Node_t *node, Tree_t *tree, Node_t *parent)
{
    /* If the tree is not rooted at the real 'parent' */
    if (tree->root->id != parent->id)
    {
        /* Visit all subtrees */
        for (ListElem *elem1 = ListFirst(&tree->subtrees_list); elem1 != NULL; elem1 = ListNext(&tree->subtrees_list, elem1))
        {
            Tree_t *subtree = (Tree_t *)elem1->obj;

            /* If the node is part of one of the subtrees, lets disconnect it */
            if (subtree->root->id == node->id)
            {
                /* Lets remove this connection */
                ListUnlink(&tree->subtrees_list, elem1);
                elem1 = ListFirst(&tree->subtrees_list);

                /* Remove 'node' from the list of candidate children of the 'root' */
                ListElem *elem2 = ListFind(&tree->root->candidate_children, (void *)node);
                if (elem2)
                {
                    ListUnlink(&tree->root->candidate_children, elem2);
                }

                /* Remove 'root' from the list of candidate parent of the 'node' */
                elem2 = ListFind(&node->candidate_parents, (void *)tree->root);
                if (elem2)
                {
                    ListUnlink(&node->candidate_parents, elem2);
                }
            }
            else
            {
                /* Recursively lets look at the subtree */
                disconnectOtherParents(node, subtree, parent);
            }
        }
    }

    return (true);
}

Tree_t *createTree(Node_t *root, List *nodesList)
{
    Tree_t *branch = newTree(root, BRANCH);

    /* Go over all nodes in the list of nodes */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        /* Check if node is one hop away from root and if root is its parent candidate */
        if (node->hop_count == root->hop_count + 1 && ListFind(&node->candidate_parents, (void *)root))
        {
            /* Recursively create a branch, now rooted at 'node' */
            Tree_t *newSubTree = createTree(node, nodesList);

            /* Update list of subtrees and the weight of the branch */
            ListAppend(&branch->subtrees_list, newSubTree);

            for (ListElem *elem2 = ListFirst(&newSubTree->children_list); elem2 != NULL; elem2 = ListNext(&newSubTree->children_list, elem2))
            {
                Node_t *child = (Node_t *)elem2->obj;

                if (!ListFind(&branch->children_list, child))
                {
                    ListAppend(&branch->children_list, child);
                }
            }
            ListAppend(&branch->children_list, node);

            branch->weight = ListLength(&branch->children_list) + 1;
        }
    }

    return (branch);
}

void constructHopCountParentsAndChildren(Node_t *sink, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel)
{
    int i;

    /* Hop count of sink is 0 */
    sink->hop_count = 0;

    /* Our search list */
    List s_list; memset(&s_list, 0, sizeof(List)); (void)ListInit(&s_list);

    /* Insert the sink node in our list */
    ListAppend(&s_list, (void*)sink);

    /* We keep looking at the list while it is not empty */
    while (!ListEmpty(&s_list))
    {
        /* Remove the first node in our list */
        Node_t *n = (Node_t *)ListFirst(&s_list)->obj;
        ListUnlink(&s_list, ListFirst(&s_list));

        /* Look for all the neighbors of the node */
        for (i=0; i<ListLength(nodesList); i++)
        {
            /* Consider only one single channel */
            if (channel >= 0)
            {
                if (conMatrix[n->id][i][channel])
                {
                    Node_t *neighbor = getNode(i, nodesList);

                    /* Neighbor hop_count is larger than node's hop_count */
                    if (neighbor->hop_count > n->hop_count)
                    {
                        /* Updating the hop count of the neighbor */
                        neighbor->hop_count = n->hop_count + 1;

                        /* Inserting the neighbor into the nodes' children list */
                        if (!ListFind(&n->candidate_children, neighbor))
                        {
                            ListAppend(&n->candidate_children, neighbor);
                        }

                        /* Inserting the current node into the neighbor's parent list */
                        if (!ListFind(&neighbor->candidate_parents, n))
                        {
                            ListAppend(&neighbor->candidate_parents, n);
                        }

                        /* Insert the new neighbor into the search list */;
                        if (!ListFind(&s_list, (void *)neighbor))
                        {
                            ListAppend(&s_list, neighbor);
                        }
                    }
                }
            }
            /* Consider all channels */
            else
            {
                for (uint8_t c = 0; c < NUM_CHANNELS; c++)
                {
                    if (conMatrix[n->id][i][c])
                    {
                        Node_t *neighbor = getNode(i, nodesList);

                        /* Neighbor hop_count is larger than node's hop_count */
                        if (neighbor->hop_count > n->hop_count)
                        {
                            /* Updating the hop count of the neighbor */
                            neighbor->hop_count = n->hop_count + 1;

                            /* Inserting the neighbor into the nodes' children list */
                            if (!ListFind(&n->candidate_children, neighbor))
                            {
                                ListAppend(&n->candidate_children, neighbor);
                            }

                            /* Inserting the current node into the neighbor's parent list */
                            if (!ListFind(&neighbor->candidate_parents, n))
                            {
                                ListAppend(&neighbor->candidate_parents, n);
                            }

                            /* Insert the new neighbor into the search list */;
                            if (!ListFind(&s_list, (void *)neighbor))
                            {
                                ListAppend(&s_list, neighbor);
                            }
                        }
                        /* Stop the for loop */
                        break;
                    }
                }
            }
        }
    }

    /* Lets check all nodes that are not connected to any parent and set the ho count to -1
       in order to prevent mistakes */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *n = (Node_t *)elem->obj;
        if (ListLength(&n->candidate_parents) == 0)
        {
            n->hop_count = -1;
        }
    }
}

void constructGS(Tree_t *cmst, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel)
{
    /* For every node in the network */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem1->obj;

        /* Find all neighbors */
        for (ListElem *elem2 = ListFirst(nodesList); elem2 != NULL; elem2 = ListNext(nodesList, elem2))
        {
            Node_t *neighbor = (Node_t *)elem1->obj;

            /* Consider only one single channel */
            if (channel >= 0)
            {
                /* Check if nodes are neighbors and if hop count of neighbor is greater */
                if (conMatrix[node->id][neighbor->id][channel] && neighbor->hop_count > node->hop_count)
                {
                    /* If the neighbor is not connected yet to the CMST */
                    if (!isNodeInTree(neighbor, cmst, NULL))
                    {
                        if (!ListFind(&node->gs, neighbor))
                        {
                            ListAppend(&node->gs, neighbor);
                        }
                    }
                }
            }
            /* Consider all channels */
            else
            {
                for (uint8_t c = 0; c < NUM_CHANNELS; c++)
                {
                    /* Check if nodes are neighbors and if hop count of neighbor is greater */
                    if (conMatrix[node->id][neighbor->id][c] && neighbor->hop_count > node->hop_count)
                    {
                        /* If the neighbor is not connected yet to the CMST */
                        if (!isNodeInTree(neighbor, cmst, NULL))
                        {
                            if (!ListFind(&node->gs, neighbor))
                            {
                                ListAppend(&node->gs, neighbor);
                            }
                        }
                    }
                }
            }
        }
    }
}

void updateGS(Tree_t *cmst, Node_t *node, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel)
{
    /* Unlink all current nodes in the GS */
    ListElem *elem;
    while((elem = ListFirst(&node->gs)) != NULL)
    {
        ListUnlink(&node->gs, elem);
    }

    /* Re-create the list of nodes in growth set (GS) */
    for (int i=0; i<ListLength(nodesList); i++)
    {
        Node_t *neighbor = getNode(i, nodesList);

        /* Consider only one single channel */
        if (channel >= 0)
        {
            /* Check if nodes are neighbors and if hop count of neighbor is greater */
            if (neighbor->hop_count > node->hop_count && conMatrix[node->id][i][channel] != false)
            {
                /* If the neighbor is not connected yet to the CMST */
                if (!isNodeInTree(neighbor, cmst, NULL))
                {
                    if (!ListFind(&node->gs, neighbor))
                    {
                        ListAppend(&node->gs, neighbor);
                    }
                }
            }
        }
        /* Consider all channels */
        else
        {
            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                /* Check if nodes are neighbors and if hop count of neighbor is greater */
                if (neighbor->hop_count > node->hop_count && conMatrix[node->id][i][c] != false)
                {
                    /* If the neighbor is not connected yet to the CMST */
                    if (!isNodeInTree(neighbor, cmst, NULL))
                    {
                        if (!ListFind(&node->gs, neighbor))
                        {
                            ListAppend(&node->gs, neighbor);
                        }
                    }
                }
            }
        }
    }
}

List *branchesNodeIsConnectTo(Node_t *node, Tree_t *branches[], uint8_t size, Node_t *avoidNode)
{
    int i;

    /* List of branches to be returned */
    List *list = (List *)malloc(sizeof(List)); memset(list, 0, sizeof(List)); ListInit(list);

    /* Going over all branches */
    for (i = 0; i < size; i++)
    {
        /* Check if node is connected to that branch */
        if (isNodeInTree(node, branches[i], avoidNode))
        {
            ListAppend(list, (void *)branches[i]);
        }
    }

    return (list);
}

void sortListNonIncreasingByGS(List *unsorted, List *sorted)
{
    ListElem *elem1, *elem2;

    /* Lets perform InsertionSort. We need to traverse all elements in the list */
    for (elem1 = ListFirst(unsorted); elem1 != NULL; elem1 = ListNext(unsorted, elem1))
    {
        /* Lets traverse the sorted_list, trying to find the right place to put our elem1 */
        elem2 = ListFirst(sorted);

        while (elem2 != NULL)
        {
            Node_t *node1 = (Node_t *)elem1->obj;
            Node_t *node2 = (Node_t *)elem2->obj;

            /* Checking the gs size */
            if ((ListLength(&node1->gs) < ListLength(&node2->gs)) || \
                (ListLength(&node1->gs) == ListLength(&node2->gs) && node1->id > node2->id))
            {
                elem2 = ListNext(sorted, elem2);
            }
            else
            {
                ListInsertBefore(sorted, elem1->obj, elem2);
                break;
            }
        }

        /* If sorted_list is empty or elem1 is smaller than everyone in the sorted list */
        if (elem2 == NULL)
        {
            ListAppend(sorted, elem1->obj);
        }
    }
}

List *createSS(Node_t *node, Tree_t *branch, List *nodesList, Tree_t *branches[], int size)
{
    List *SS = (List *)malloc(sizeof(List)); memset(SS, 0, sizeof(List)); (void)ListInit(SS);

    /* Find all the children of node that can only connect to the 'branch'  */
    for (ListElem *elem1 = ListFirst(&node->candidate_children); elem1 != NULL; elem1 = ListNext(&node->candidate_children, elem1))
    {
        Node_t *child = (Node_t *)elem1->obj;

        /* We find all branches that child can connect to, avoiding (not using) 'node' */
        /* If it is an empty set or its size is one and the branch is equal to 'branch', this means
           the child can only connect to that branch if 'node' is part of it */
        List *listBranches = branchesNodeIsConnectTo(child, branches, size, node);
        if (ListLength(listBranches) == 0 || (ListLength(listBranches) == 1 && ListFirst(listBranches)->obj == branch))
        {
            /* Add the child node */
            ListAppend(SS, (void *)child);

            /* And all its children that can also only be connected to that branch */
            List *childrenSS = createSS(child, branch, nodesList, branches, size);
            for (ListElem *elem2 = ListFirst(childrenSS); elem2 != NULL; elem2 = ListNext(childrenSS, elem2))
            {
                Node_t *n = (Node_t *)elem2->obj;
                ListAppend(SS, (void *)n);
            }
        }
    }

    return (SS);
}

void connectToParentMaxChannelVar(Node_t *node, Tree_t *cmst, bool conMatrix[][MAX_NODES][NUM_CHANNELS])
{
    Node_t *parentToConnect = NULL;
    uint8_t max_channel_var = 0;

    for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        Node_t *next_parent = (Node_t *)elem->obj;

        /* Calculate the channel variety of node next_parent */
        uint8_t chan_var = 0;
        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            if (conMatrix[node->id][next_parent->id][c])
            {
                chan_var++;
            }
        }

        if (chan_var > max_channel_var)
        {
            parentToConnect = next_parent;
            max_channel_var = chan_var;
        }
    }

    /* Connect to the parent with maximum channel variety */
    connectToTree(node, parentToConnect, cmst);
}


void checkAllNodesHaveParents(List *nodesList)
{
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        /* Get the current node */
        Node_t *n1 = (Node_t *)elem1->obj;

        if (n1->type != SINK && ListLength(&n1->candidate_parents) == 0)
        {
            ERROR("Node %d has no parent. Cannot proceed with tree construction.\n", n1->id);
        }
    }
}
