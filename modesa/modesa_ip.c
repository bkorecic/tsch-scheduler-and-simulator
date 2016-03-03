#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/glpk.h"
#include "modesa.h"
#include "../util/files.h"
#include "../util/debug.h"

#define LP_FILE "data/modesa_ip.lp"

bool main_modesa_ip(List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t sink_interfaces, \
                    bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel)
{
    /* List of sink nodes (Vg) */
    List Vg; memset(&Vg, 0, sizeof(List)); ListInit(&Vg);
    Node_t *sink_node = getNode(sink_id, nodesList);
    ListAppend(&Vg, (void *)sink_node);

    /* List of source nodes (Vs) */
    List Vs; memset(&Vs, 0, sizeof(List)); ListInit(&Vs);
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;
        if (node != sink_node)
        {
            ListAppend(&Vs, (void *)node);
        }
    }

    /* Set the number of interface in the sink node */
    sink_node->interfaces = sink_interfaces;

    /* Calculate Tmax */
    updateTreeHopCount(tree, 0);
    uint16_t Tmax = 0;
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;
        Tmax += node->q * node->hop_count;
    }

    /* Create a list with all links in the graph G */
    List linksList; memset(&linksList, 0, sizeof(List)); ListInit(&linksList);
    generateLinksList(tree, &linksList);

    /* Generate the list of interfering nodes for each node */
    generateNodesInterfering(confMatrix, nodesList, channel);

    /* Write the CPLEX file with the problem */
    writeLPFile(tree, nodesList, &Vg, &Vs, &linksList, Tmax);

    /* GLPK problem */
    glp_prob *lp;

    /* Create the problem */
    lp = glp_create_prob();

    /* Set the name of the problem */
    glp_set_prob_name(lp, "ModesaIP");

    /* Read the problem from file */
    if (glp_read_lp(lp, NULL, LP_FILE))
    {
        PRINTF("Problem reading LP.\n");
    }

    /* Setting the MIP parameters */
    glp_iocp param;
    glp_init_iocp(&param);
    param.presolve = GLP_ON;
    param.tm_lim = 30000;       /* One minute of time limit */

    uint8_t ret;
    ret = glp_intopt(lp, &param);
    if (ret)
    {
        PRINTF("Branch-and-cut returned error: %d.\n", ret);
    }

    PRINTF("MIP result %d.\n", glp_mip_status(lp));

    /* Get the objective value */
    //double z;
    //z = glp_mip_obj_val(lp);

    /* Create the index of variables */
    glp_create_index(lp);

    /* Checking all activities (variable a) that are equal to 1 */
    for (uint16_t t = 0; t < Tmax; t++)
    {
        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            for (ListElem *elem = ListFirst(&linksList); elem != NULL; elem = ListNext(&linksList, elem))
            {
                Link_t *link_e = (Link_t *)elem->obj;

                char variable[20];
                sprintf(variable, "a_%d,%d,%d", link_e->id, c, t);

                int col = glp_find_col(lp, variable);

                if (glp_mip_col_val(lp, col) != 0)
                {
                    PRINTF("Variable = %s = %e\n", variable, glp_mip_col_val(lp, col));

                    Node_t *node_tx = link_e->n1;
                    Node_t *node_rx = link_e->n2;

                    TimeSlot_t *ts = newTimeSlot(t+1, c, TS_TX, node_rx, false);
                    ListAppend(&node_tx->timeslots, (void *)ts);
                    ts = newTimeSlot(t+1, c, TS_RX, node_tx, false);
                    ListAppend(&node_rx->timeslots, (void *)ts);
                }
            }
        }
    }

    /* Calculating an array with all valid timeslots and channels.
     * This is necessary because we may have gaps of timeslots and channels not used */
    bool timeslots[Tmax + 1];
    bool channels[NUM_CHANNELS + 1];
    for (uint8_t t = 0; t < Tmax+1; t++)
    {
        timeslots[t] = false;
    }
    for (uint8_t c = 0; c < NUM_CHANNELS + 1; c++)
    {
        channels[c] = false;
    }

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        for (ListElem *elem2 = ListFirst(&node->timeslots); elem2 != NULL; elem2 = ListNext(&node->timeslots, elem2))
        {
            TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;

            timeslots[ts->time] = true;
            channels[ts->freq] = true;
        }
    }

    for (uint8_t t = 0; t < Tmax+1; t++)
    {
        if (timeslots[t]) PRINTF("Timeslot %d\n", t);
    }
    for (uint8_t c = 0; c <  NUM_CHANNELS + 1; c++)
    {
        if (channels[c]) PRINTF("Channel %d\n", c);
    }

    /* Updating the time slots os all nodes */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        for (ListElem *elem2 = ListFirst(&node->timeslots); elem2 != NULL; elem2 = ListNext(&node->timeslots, elem2))
        {
            TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;

            uint8_t sub_t = 0;
            uint8_t sub_c = 0;
            for (uint8_t t = 1; t < ts->time; t++)
            {
                if (!timeslots[t]) sub_t++;
            }
            for (uint8_t c = 0; c < ts->freq; c++)
            {
                if (!channels[c]) sub_c++;
            }

            ts->time -= sub_t;
            ts->freq -= sub_c;
        }
    }

    glp_delete_prob(lp);

    return (true);
}

void writeLPFile(Tree_t *tree, List *nodesList, List *Vg, List *Vs, List *linksList, uint16_t Tmax)
{
    FILE *fp = NULL;
    uint8_t res;
    bool first = true;

    res = openFile(&fp, LP_FILE, "w");

    if (res != true)
    {
        EXIT("Error while writing file %s", LP_FILE);
    }

    /* Objective function */
    fprintf(fp, "Minimize\n");
    fprintf(fp, "\tobj: ");
    first = true;
    for (uint8_t t = 0; t < Tmax; t++)
    {
        if (first)
        {
            fprintf(fp, "u_%d ", t);
            first = false;
        }
        else
        {
            fprintf(fp, "+ u_%d ", t);
        }
    }
    fprintf(fp, "\n");

    fprintf(fp, "Subject To\n");

    /* Constraint 1 */
    for (ListElem *elem = ListFirst(linksList); elem != NULL; elem = ListNext(linksList, elem))
    {
        Link_t *link = (Link_t *)elem->obj;

        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            for (uint16_t t = 0; t < Tmax; t++)
            {
                fprintf(fp, "\tc1_%d,%d,%d: a_%d,%d,%d - u_%d <= 0\n", link->id,c,t, link->id,c,t, t);
            }
        }
    }

    /* Constraint 2 */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node_v = (Node_t *)elem1->obj;

        for (ListElem *elem2 = ListFirst(&node_v->links_tx); elem2 != NULL; elem2 = ListNext(&node_v->links_tx, elem2))
        {
            Link_t *link_e = (Link_t *)elem2->obj;

            for (ListElem *elem3 = ListFirst(&node_v->nodes_int); elem3 != NULL; elem3 = ListNext(&node_v->nodes_int, elem3))
            {
                Node_t *node_w = (Node_t *)elem3->obj;

                for (ListElem *elem4 = ListFirst(&node_w->links_tx); elem4 != NULL; elem4 = ListNext(&node_w->links_tx, elem4))
                {
                    Link_t *link_ep = (Link_t *)elem4->obj;

                    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
                    {
                        for (uint16_t t = 0; t < Tmax; t++)
                        {
                            fprintf(fp, "\tc2_%d,%d,%d,%d,%d,%d: a_%d,%d,%d + a_%d,%d,%d <= 1\n", \
                                                node_v->id,link_e->id,node_w->id,link_ep->id,c,t, \
                                                link_e->id,c,t, \
                                                link_ep->id,c,t);
                        }
                    }
                }
            }
        }
    }

    /* Constraint 3 */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node_v = (Node_t *)elem1->obj;

        for (uint16_t t = 0; t < Tmax; t++)
        {
            fprintf(fp, "\tc3_%d,%d: ", node_v->id, t);

            bool first = true;

            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                for (ListElem *elem2 = ListFirst(&node_v->links_tx); elem2 != NULL; elem2 = ListNext(&node_v->links_tx, elem2))
                {
                    Link_t *link_e = (Link_t *)elem2->obj;

                    if (first)
                    {
                        fprintf(fp, "a_%d,%d,%d ", link_e->id, c, t);
                        first = false;
                    }
                    else
                    {
                        fprintf(fp, "+ a_%d,%d,%d ", link_e->id, c, t);
                    }
                }
            }

            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                for (ListElem *elem2 = ListFirst(&node_v->links_rx); elem2 != NULL; elem2 = ListNext(&node_v->links_rx, elem2))
                {
                    Link_t *link_ep = (Link_t *)elem2->obj;

                    if (first)
                    {
                        fprintf(fp, "a_%d,%d,%d ", link_ep->id, c, t);
                        first = false;
                    }
                    else
                    {
                        fprintf(fp, "+ a_%d,%d,%d ", link_ep->id, c, t);
                    }
                }
            }

            fprintf(fp, "<= %d\n", node_v->interfaces);
        }
    }

    /* Constraint 4 */
    for (ListElem *elem1 = ListFirst(linksList); elem1 != NULL; elem1 = ListNext(linksList, elem1))
    {
        Link_t *link_e = (Link_t *)elem1->obj;

        fprintf(fp, "\tc4_%d: ", link_e->id);

        bool first = true;
        for (ListElem *elem2 = ListFirst(Vs); elem2 != NULL; elem2 = ListNext(Vs, elem2))
        {
            Node_t *node_s = (Node_t *)elem2->obj;

            if (first)
            {
                fprintf(fp, "f_%d,%d ", link_e->id, node_s->id);
                first = false;
            }
            else
            {
                fprintf(fp, "+ f_%d,%d ", link_e->id, node_s->id);
            }
        }

        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            for (uint16_t t = 0; t < Tmax; t++)
            {
                fprintf(fp, "- a_%d,%d,%d ", link_e->id, c, t);
            }
        }

        fprintf(fp, "= 0\n");
    }

    /* Constraint 5 */
    for (ListElem *elem1 = ListFirst(Vs); elem1 != NULL; elem1 = ListNext(Vs, elem1))
    {
        Node_t *node_s = (Node_t *)elem1->obj;

        fprintf(fp, "\tc5_%d: ", node_s->id);

        bool first = true;
        for (ListElem *elem2 = ListFirst(&node_s->links_tx); elem2 != NULL; elem2 = ListNext(&node_s->links_tx, elem2))
        {
            Link_t *link_e = (Link_t *)elem2->obj;

            if (first)
            {
                fprintf(fp, "f_%d,%d ", link_e->id, node_s->id);
                first = false;
            }
            else
            {
                fprintf(fp, "+ f_%d,%d ", link_e->id, node_s->id);
            }
        }

        fprintf(fp, "= %d\n", node_s->q);
    }

    /* Constraint 6 */
    for (ListElem *elem1 = ListFirst(Vs); elem1 != NULL; elem1 = ListNext(Vs, elem1))
    {
        Node_t *node_s = (Node_t *)elem1->obj;

        fprintf(fp, "\tc6_%d: ", node_s->id);

        bool first = true;
        for (ListElem *elem2 = ListFirst(Vg); elem2 != NULL; elem2 = ListNext(Vg, elem2))
        {
            Node_t *node_g = (Node_t *)elem2->obj;

            for (ListElem *elem3 = ListFirst(&node_g->links_rx); elem3 != NULL; elem3 = ListNext(&node_g->links_rx, elem3))
            {
                Link_t *link_e = (Link_t *)elem3->obj;

                if (first)
                {
                    fprintf(fp, "f_%d,%d ", link_e->id, node_s->id);
                    first = false;
                }
                else
                {
                    fprintf(fp, "+ f_%d,%d ", link_e->id, node_s->id);
                }
            }
        }

        fprintf(fp, "= %d\n", node_s->q);
    }

    /* Constraint 7 */
    for (ListElem *elem1 = ListFirst(Vs); elem1 != NULL; elem1 = ListNext(Vs, elem1))
    {
        Node_t *node_i = (Node_t *)elem1->obj;

        fprintf(fp, "\tc7_%d: ", node_i->id);

        bool first = true;
        for (ListElem *elem2 = ListFirst(Vs); elem2 != NULL; elem2 = ListNext(Vs, elem2))
        {
            Node_t *node_s = (Node_t *)elem2->obj;

            for (ListElem *elem3 = ListFirst(&node_i->links_tx); elem3 != NULL; elem3 = ListNext(&node_i->links_tx, elem3))
            {
                Link_t *link_e = (Link_t *)elem3->obj;

                if (first)
                {
                    fprintf(fp, "f_%d,%d ", link_e->id, node_s->id);
                    first = false;
                }
                else
                {
                    fprintf(fp, "+ f_%d,%d ", link_e->id, node_s->id);
                }
            }
        }

        for (ListElem *elem2 = ListFirst(Vs); elem2 != NULL; elem2 = ListNext(Vs, elem2))
        {
            Node_t *node_s = (Node_t *)elem2->obj;

            for (ListElem *elem3 = ListFirst(&node_i->links_rx); elem3 != NULL; elem3 = ListNext(&node_i->links_rx, elem3))
            {
                Link_t *link_e = (Link_t *)elem3->obj;

                fprintf(fp, "- f_%d,%d ", link_e->id, node_s->id);
            }
        }

        fprintf(fp, "= %d\n", node_i->q);
    }

    /* Constraint 8 */
    for (ListElem *elem1 = ListFirst(Vs); elem1 != NULL; elem1 = ListNext(Vs, elem1))
    {
        Node_t *node_i = (Node_t *)elem1->obj;

        for (uint16_t t = 0; t < Tmax; t++)
        {
            fprintf(fp, "\tc8_%d,%d: ", node_i->id, t);

            bool first = true;
            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                for (ListElem *elem2 = ListFirst(&node_i->links_tx); elem2 != NULL; elem2 = ListNext(&node_i->links_tx, elem2))
                {
                    Link_t *link_e = (Link_t *)elem2->obj;

                    if (first)
                    {
                        fprintf(fp, "a_%d,%d,%d ", link_e->id, c, t);
                        first = false;
                    }
                    else
                    {
                        fprintf(fp, "+ a_%d,%d,%d ", link_e->id, c, t);
                    }
                }
            }

            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                for (ListElem *elem2 = ListFirst(&node_i->links_rx); elem2 != NULL; elem2 = ListNext(&node_i->links_rx, elem2))
                {
                    Link_t *link_e = (Link_t *)elem2->obj;

                    for (uint16_t tp = 0; tp < t; tp++)
                    {
                        fprintf(fp, "- a_%d,%d,%d ", link_e->id, c, tp);
                    }
                }
            }

            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                for (ListElem *elem2 = ListFirst(&node_i->links_tx); elem2 != NULL; elem2 = ListNext(&node_i->links_tx, elem2))
                {
                    Link_t *link_e = (Link_t *)elem2->obj;

                    for (uint16_t tp = 0; tp < t; tp++)
                    {
                        fprintf(fp, "- a_%d,%d,%d ", link_e->id, c, tp);
                    }
                }
            }

            fprintf(fp, "<= %d\n", node_i->q);
        }
    }

    /* Bounds */
    fprintf(fp, "Bounds\n");
    for (ListElem *elem1 = ListFirst(linksList); elem1 != NULL; elem1 = ListNext(linksList, elem1))
    {
        Link_t *link_e = (Link_t *)elem1->obj;

        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            for (uint8_t t = 0; t < Tmax; t++)
            {
                fprintf(fp, "\t0 <= a_%d,%d,%d <= 1\n", link_e->id,c,t);
            }
        }
    }
    for (uint8_t t = 0; t < Tmax; t++)
    {
        fprintf(fp, "\t0 <= u_%d <= 1\n", t);
    }
    for (ListElem *elem1 = ListFirst(linksList); elem1 != NULL; elem1 = ListNext(linksList, elem1))
    {
        Link_t *link_e = (Link_t *)elem1->obj;

        for (ListElem *elem2 = ListFirst(Vs); elem2 != NULL; elem2 = ListNext(Vs, elem2))
        {
            Node_t *node_s = (Node_t *)elem2->obj;

            fprintf(fp, "\tf_%d,%d >= 0\n", link_e->id,node_s->id);
        }
    }

    /* Integer */
    fprintf(fp, "Integer\n");
    for (ListElem *elem1 = ListFirst(linksList); elem1 != NULL; elem1 = ListNext(linksList, elem1))
    {
        Link_t *link_e = (Link_t *)elem1->obj;

        for (uint8_t c = 0; c < NUM_CHANNELS; c++)
        {
            for (uint8_t t = 0; t < Tmax; t++)
            {
                fprintf(fp, "\ta_%d,%d,%d\n", link_e->id,c,t);
            }
        }
    }
    for (uint8_t t = 0; t < Tmax; t++)
    {
        fprintf(fp, "\tu_%d\n", t);
    }
    for (ListElem *elem1 = ListFirst(linksList); elem1 != NULL; elem1 = ListNext(linksList, elem1))
    {
        Link_t *link_e = (Link_t *)elem1->obj;

        for (ListElem *elem2 = ListFirst(Vs); elem2 != NULL; elem2 = ListNext(Vs, elem2))
        {
            Node_t *node_s = (Node_t *)elem2->obj;

            fprintf(fp, "\tf_%d,%d\n", link_e->id,node_s->id);
        }
    }

    /* End */
    fprintf(fp, "End\n");

    fclose(fp);
}
