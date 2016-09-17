#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "time_schedule.h"
#include "../util/debug.h"
#include "../graphs/graphs.h"

Action_t *newAction(uint8_t branch, uint8_t hop)
{
    Action_t *action = (Action_t *)malloc(sizeof(Action_t));

    if (action == NULL)
    {
        ERROR("Not enough memory.\n");
    }
    else
    {
        memset(action, 0, sizeof(Action_t));
    }

    action->branch = branch;
    action->hop = hop;

    return (action);
}

List *nodesWithHopCount (List *nodesList, Tree_t *tree, uint8_t hopCount)
{
    List *list = (List *)malloc(sizeof(List)); memset(list, 0, sizeof(List)); ListInit(list);

    /* Look for all nodes and check the hopCount and if it in the correct tree */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        if (node->hop_count == hopCount && isNodeInTree(node, tree, NULL))
        {
            ListAppend(list, (void *)node);
        }
    }

    return (list);
}

LineTree_t *createLineTree (List *nodesList, Tree_t *tree)
{
    uint8_t hop = 1;

    if (tree == NULL)
    {
        return (NULL);
    }

    LineTree_t *lineTree = newLineTree(hop);
    LineTree_t *aux = lineTree;
    lineTree->nodes = nodesWithHopCount(nodesList, tree, hop);

    hop++;
    List *list = nodesWithHopCount(nodesList, tree, hop);
    while (ListLength(list) != 0)
    {
        aux->nextTree = newLineTree(hop);
        aux = aux->nextTree;
        aux->nodes = list;
        hop++;
        list = nodesWithHopCount(nodesList, tree, hop);
    }

    return (lineTree);
}

bool createOptimalTimeSlotSchedule(Tree_t *cmst, List *nodesList, bool optimal_sched)
{
    /* Number of branches */
    uint8_t n_branches = ListLength(&cmst->subtrees_list);

    /* Create an array with all line trees */
    LineTree_t *multiLineNetwork[n_branches];

    uint8_t i = 0;
    for (ListElem *elem = ListFirst(&cmst->subtrees_list); elem != NULL; elem = ListNext(&cmst->subtrees_list, elem))
    {
        Tree_t *subTree = (Tree_t *)elem->obj;

        multiLineNetwork[i] = createLineTree(nodesList, subTree);
        printLineTree(multiLineNetwork[i]);

        /* Packets left for each branch */
        multiLineNetwork[i]->pkts_left = subTree->weight;

        /* All branches are legal initially */
        multiLineNetwork[i]->prev_legal = multiLineNetwork[i]->legal = 1;

        i++;
    }

    /* Packets left for the whole network */
    uint16_t pkts_left = 0;
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *n = (Node_t *)elem->obj;
        if (n->type != SINK && n->type != DISCONNECTED && isNodeInTree(n, cmst, NULL))
        {
            pkts_left += n->q;
        }
    }

    /* Calculating the est_trans_time vector, which is the maximum final time for transmitting all packets
     * from each line tree */
    for (i = 0; i < n_branches; i++)
    {
        /* Number of hops in each branch */
        uint8_t n_hops_branch = 0;
        for (LineTree_t *lineTree = multiLineNetwork[i]; lineTree != NULL; lineTree = lineTree->nextTree)
        {
            n_hops_branch++;
        }

        /* Number of packets stored at each hop */
        uint16_t temp_nu_vector[n_hops_branch];
        uint8_t j = 0;
        for (LineTree_t *lineTree = multiLineNetwork[i]; lineTree != NULL; lineTree = lineTree->nextTree)
        {
            temp_nu_vector[j++] = ListLength(lineTree->nodes);
        }

        /* Calculate the lower bound for all hops of the line */
        uint16_t max_low_bound = 0;
        for (j = 0; j < n_hops_branch; j++)
        {
            /* Sum of nu all over the line */
            uint16_t sum_pkt = 0;
            for (uint8_t k = j+1; k < n_hops_branch; k++)
            {
                sum_pkt += temp_nu_vector[k];
            }
            uint16_t new_low_bound = (j+1) - 1 + temp_nu_vector[j] + 2*sum_pkt;

            if (new_low_bound > max_low_bound)
            {
                max_low_bound = new_low_bound;
            }
        }

        /* Update the est_trans_time for each line tree */
        multiLineNetwork[i]->est_trans_time = max_low_bound;
    }

    /* Create the list of actions */
    List actionsList; memset(&actionsList, 0, sizeof(List)); ListInit(&actionsList);

    while (pkts_left != 0)
    {
        uint16_t legal_est_trans_time[n_branches];
        uint16_t max_est_time = 0;
        uint8_t idx = 0;

        /* Calculate est_trans_time * legal and get the maximum estimated time */
        for (i = 0; i < n_branches; i++)
        {
            legal_est_trans_time[i] = multiLineNetwork[i]->est_trans_time * multiLineNetwork[i]->legal;
            if (legal_est_trans_time[i] > max_est_time)
            {
                max_est_time = legal_est_trans_time[i];
                idx = i;
            }
        }

        /* If could not find the maximum, it means all branches are busy (ilegal) */
        if (max_est_time == 0)
        {
            /* Invalid action - Branch 0 and Node 0 */
            Action_t *action = newAction(0, 0);
            ListAppend(&actionsList, (void *)action);
        }
        else
        {
            /* Check if we are transmitting to hop greater than 1 */
            if (multiLineNetwork[idx]->pkts_left > ListLength(multiLineNetwork[idx]->nodes))
            {
                multiLineNetwork[idx]->time_to_be_legal = 2;  /* We will be legal after 2 time slots (TX + RX) */

                int16_t curr_pkt_left = multiLineNetwork[idx]->pkts_left;

                /* Lets check to whom we need to send */
                uint8_t curr_hop = 1;
                for (LineTree_t *tree = multiLineNetwork[idx]; tree != NULL; tree = tree->nextTree)
                {
                    curr_pkt_left -= ListLength(tree->nodes);
                    if (curr_pkt_left <= 0)
                    {
                        break;
                    }
                    else
                    {
                        curr_hop++;
                    }
                }

                /* Send to hop curr_hop */
                Action_t *action = newAction(idx + 1, curr_hop);
                ListAppend(&actionsList, (void *)action);
            }
            else    /* We are transmitting to hop 1 */
            {
                multiLineNetwork[idx]->time_to_be_legal = 1;  /* We will be legal after 1 time slot (TX) */

                /* Send to hop 1 */
                Action_t *action = newAction(idx + 1, 1);
                ListAppend(&actionsList, (void *)action);
            }

            /* Transmitted one packet */
            pkts_left--;
            multiLineNetwork[idx]->pkts_left--;
        }

        /* Update time to be legal */
        for (int j = 0; j < n_branches; j++)
        {
            if (multiLineNetwork[j]->time_to_be_legal > 0)
            {
                multiLineNetwork[j]->time_to_be_legal--;
            }
        }

        /* Check which branches are ilegal */
        for (int j = 0; j < n_branches; j++)
        {
            if (multiLineNetwork[j]->pkts_left == 0)
            {
                multiLineNetwork[j]->legal = 0;
            }
            else if (multiLineNetwork[j]->time_to_be_legal > 0)
            {
                multiLineNetwork[j]->legal = 0;
            }
            else
            {
                multiLineNetwork[j]->legal = 1;
            }
        }

        /* Update est_trans_time of all branches that were not "used" in this round */
        for (int j = 0; j < n_branches; j++)
        {
            if (multiLineNetwork[j]->prev_legal && j != idx)
            {
                multiLineNetwork[j]->est_trans_time++;
            }
        }

        /* prev_legal = legal */
        for (int j = 0; j < n_branches; j++)
        {
            multiLineNetwork[j]->prev_legal = multiLineNetwork[j]->legal;
        }
    }

    /* Find the times slot (transmission times) from the actions list */
    actionsToTimeSlots(&actionsList, multiLineNetwork, cmst);

    if (!optimal_sched)
    {
        changeScheduleToNonOptimal(cmst, nodesList);
    }

    /* Find the maximum time slot value */
    uint16_t max_time_slot = maxTimeSlot(nodesList);

    /* Convert the distribution problem to collection problem */
    distributionToCollection(nodesList, max_time_slot);

    /* Print the time schedule */
    printTimeSlots(nodesList);

    return (true);
}

bool changeScheduleToNonOptimal(Tree_t *cmst, List *nodesList)
{
    /* Find maximum timeslot time */
    uint16_t max_time = maxTimeSlot(nodesList);

    /* For all values of 'time' get the first node with a timeslot and shift all others */
    for (uint16_t i = 1; i <= max_time; i++)
    {
        /* Print the time schedule */
        printTimeSlots(nodesList);

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *n1 = (Node_t *)elem1->obj;

            /* Check all of n1's time slots */
            for (ListElem *elem2 = ListFirst(&n1->timeslots); elem2 != NULL; elem2 = ListNext(&n1->timeslots, elem2))
            {
                TimeSlot_t *ts1 = (TimeSlot_t *)elem2->obj;

                /* If n1 has a time slot with 'time' */
                if (ts1->time == i && ts1->type == TS_RX)
                {
                    /* Get the parent and the time slot with 'time' */
                    Node_t *n2 = getParent(cmst, n1);
                    TimeSlot_t *ts2;
                    for (ListElem *elem3 = ListFirst(&n2->timeslots); elem3 != NULL; elem3 = ListNext(&n2->timeslots, elem3))
                    {
                        ts2 = (TimeSlot_t *)elem3->obj;
                        if (ts2->time == ts1->time && ts2->type == TS_TX)
                        {
                            break;
                        }
                    }

                    /* Shift all other nodes that have a time slot with 'time' */
                    for (ListElem *elem3 = ListFirst(nodesList); elem3 != NULL; elem3 = ListNext(nodesList, elem3))
                    {
                        Node_t *n3 = (Node_t *)elem3->obj;

                        /* Check all n3's time slots */
                        for (ListElem *elem4 = ListFirst(&n3->timeslots); elem4 != NULL; elem4 = ListNext(&n3->timeslots, elem4))
                        {
                            TimeSlot_t *ts3 = (TimeSlot_t *)elem4->obj;
                            if (ts3->time == ts1->time)
                            {
                                if ((n3 != n1 && n3 != n2) || \
                                    (n3 == n1 && ts3 != ts1) || \
                                    (n3 == n2 && ts3 != ts2))
                                {
                                    ts3->time++;

                                    if (ts3->time > max_time)
                                    {
                                        max_time = ts3->time;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return (true);
}

bool actionsToTimeSlots(List *actionsList, LineTree_t *multiLineNetwork[], Tree_t *cmst)
{
    /* Find the corresponding transmission time slot for the tree topology */
    uint16_t i = 1;
    for (ListElem *elem = ListFirst(actionsList); elem != NULL; elem = ListNext(actionsList, elem))
    {
        Action_t *action = (Action_t *)elem->obj;

        /* If it is a valid action (to a real branch) */
        if (action->branch != 0)
        {
            uint8_t n_hop = action->hop;

            /* Get the line tree */
            LineTree_t *lineTree = multiLineNetwork[action->branch - 1];

            /* Go into the line tree and find the right list of nodes (at hop distance) */
            while (--n_hop)
            {
                lineTree = lineTree->nextTree;
            }

            /* Take the first node in the list and remove it */
            ListElem *elem1 = ListFirst(lineTree->nodes);
            Node_t *node = (Node_t *)elem1->obj;
            ListUnlink(lineTree->nodes, elem1);

            Node_t *cur_parent = NULL;
            n_hop = action->hop;
            bool first_ts = true;

            /* We have the initial node. We are going up in the line allocating the time slots for
             * the parent of the node, the parent of the parent, the parent of the parent of the parent ... */
            while ((cur_parent = getParent(cmst, node)) != NULL)
            {
                /* Reduce the hop */
                n_hop--;

                TimeSlot_t *ts;

                /* Adding the time slot for node */
                ts = newTimeSlot(i + n_hop, 0, TS_RX, cur_parent, !first_ts);
                ListAppend(&node->timeslots, (void *)ts);

                /* Adding the time slot for parent */
                ts = newTimeSlot(i + n_hop, 0, TS_TX, node, !first_ts);
                ListAppend(&cur_parent->timeslots, (void *)ts);

                /* Invert first_ts flag because we already sent the first packet */
                if (first_ts)
                {
                    first_ts = false;
                }

                /* Keep going up in the line (towards the sink) */
                node = cur_parent;
            }
        }

        i++;
    }

    return (true);
}

bool distributionToCollection(List *nodesList, uint16_t max_time)
{
    /* For all nodes */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        /* Get all time slots */
        for (ListElem *elem2 = ListFirst(&node->timeslots); elem2 != NULL; elem2 = ListNext(&node->timeslots, elem2))
        {
            TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;

            /* Mirror the real time */
            ts->time = max_time - ts->time + 1;

            /* And invert the direction of flow */
            if (ts->type == TS_RX)
            {
                ts->type = TS_TX;
            }
            else if (ts->type == TS_TX)
            {
                ts->type = TS_RX;
            }
        }
    }

    return (true);
}

uint16_t maxTimeSlot (List *nodesList)
{
    uint16_t max_time_slot = 0;

    /* Search in all nodes */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        /* Search in all time slots */
        for (ListElem *elem2 = ListFirst(&node->timeslots); elem2 != NULL; elem2 = ListNext(&node->timeslots, elem2))
        {
            TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;

            if (ts->time > max_time_slot)
            {
                max_time_slot = ts->time;
            }
        }
    }

    return (max_time_slot);
}

void printTimeSlots(List *nodesList)
{
    PRINTF("\nList of time slots:\n");
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        /* Get the current node */
        Node_t *n = (Node_t *)elem1->obj;

        PRINTF("[ID: %d , TS: ", n->id);

        for (ListElem *elem2 = ListFirst(&n->timeslots); elem2 != NULL; elem2 = ListNext(&n->timeslots, elem2))
        {
            TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;

            PRINTF("(%d,", ts->time);
            if (ts->type == TS_RX)
            {
                PRINTF("RX) ");
            }
            else if (ts->type == TS_TX)
            {
                PRINTF("TX) ");
            }
            else if (ts->type == TS_SHARED)
            {
                PRINTF("SH) ");
            }
        }
        PRINTF("]\n");
    }
    fflush(stdout);
}

bool shareTimeSlots(Tree_t *tree, Node_t *node_i, Node_t *node_j)
{
    for (ListElem *elem1 = ListFirst(&node_i->timeslots); elem1 != NULL; elem1 = ListNext(&node_i->timeslots, elem1))
    {
        TimeSlot_t *ts1 = (TimeSlot_t *)elem1->obj;

        for (ListElem *elem2 = ListFirst(&node_j->timeslots); elem2 != NULL; elem2 = ListNext(&node_j->timeslots, elem2))
        {
            TimeSlot_t *ts2 = (TimeSlot_t *)elem2->obj;

            if (ts1->time == ts2->time)
            {
                Node_t *parent_i = getParent(tree, node_i);
                Node_t *parent_j = getParent(tree, node_j);

                /* There is a conflict only if the nodes are not communicating */
                if (parent_i != node_j && parent_j != node_i)
                {
                    return (true);
                }
            }
        }
    }

    return (false);
}
