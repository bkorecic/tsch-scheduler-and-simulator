#include <stdio.h>
#include "matching.h"

bool tasaMatching(List *DCFL, uint16_t q[][MAX_TIMESLOTS], uint16_t Q[][MAX_TIMESLOTS], Tree_t *tree, uint8_t k, Node_t *nx)
{
    /* Find the subtree rooted at node */
    Tree_t *subtree_nx = getSubTree(tree, nx);

    /* For all children of node check if there is any one that satisfy Eq 1 of paper
    " On optimal Scheduling in Duty-Cycle Industrial IoT Applications Using IEEE 802.15.4e TSCH */
    Node_t *nj = getChildEq1(q, Q, subtree_nx, k);

    if (nj != NULL)
    {
        /* DCFL(k) = DCFL(k) + [(nj,nx)] */
        Link_t *link = newLink(nj, nx, 1.0, 0, UNIDIRECTIONAL, 0);
        ListAppend(DCFL, (void *)link);

        Tree_t *subTree_nj = getSubTree(tree, nj);
        while (lengthChildren(subTree_nj) > 0)
        {
            /* nz in children of nj */
            Tree_t *subtree_nz = getValidChild(subTree_nj);
            Node_t *nz = subtree_nz->root;

            /* ch(nj) = ch(nj) - nz */
            subtree_nz->valid = false;

            /* DCFL(k) = DCFL(k) + MATCHING(G,q,Q,nz,k) */
            tasaMatching(DCFL, q, Q, tree, k, nz);
        }
        subTree_nj->valid = false;
    }

    while (lengthChildren(subtree_nx) > 0)
    {
        /* nw in children of nx */
        Tree_t *subtree_nw = getValidChild(subtree_nx);
        Node_t *nw = subtree_nw->root;

        /* ch(nx) = ch(nx) - nw */
        subtree_nw->valid = false;

        /* DCFL(k) = DCFL(k) + MATCHING(G,q,Q,nw,k) */
        tasaMatching(DCFL, q, Q, tree, k, nw);
    }

    return (true);
}

Node_t *getChildEq1(uint16_t q[][MAX_TIMESLOTS], uint16_t Q[][MAX_TIMESLOTS], Tree_t *tree, uint8_t ts)
{
    uint16_t max_Q = 0;
    Node_t *node_max_Q = NULL;

    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        if (subTree->valid)
        {
            if (q[subTree->root->id][ts] > 0)
            {
                if (Q[subTree->root->id][ts] > max_Q)
                {
                    max_Q = Q[subTree->root->id][ts];
                    node_max_Q = subTree->root;
                }
            }
        }
    }

    return (node_max_Q);
}

Tree_t *getValidChild(Tree_t *tree)
{
    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        if (subTree->valid)
        {
            return (subTree);
        }
    }
    return (NULL);
}

uint8_t lengthChildren(Tree_t *tree)
{
    uint8_t length = 0;

    for (ListElem *elem = ListFirst(&tree->subtrees_list); elem != NULL; elem = ListNext(&tree->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        if (subTree->valid)
        {
            length++;
        }
    }

    return (length);
}
