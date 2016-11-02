#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/list.h"
#include "../util/files.h"
#include "../util/print.h"
#include "../util/debug.h"
#include "../rpl/rpl.h"
#include "../graphs/graphs.h"
#include "fhss.h"
#include "no-schedule.h"

void noScheduleOutputReliabilityDelayFile(List *nodesList, bool first_time);
void noScheduleOutputEnergyFile(List *nodesList, bool first_time);
List *noScheduleNodesToTX(uint8_t sink_id, List *nodesList, uint16_t time, uint8_t prob_tx);
void noSchedulePrintPktSink(uint8_t sink_id, List *nodesList);
bool noScheduleReceivePkt(Node_t *node_tx, Node_t *node_rx, Packet_t *pkt, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t asn);

bool main_no_schedule(List *nodesList, uint8_t slotframe_size, uint8_t n_beacon_timeslot, float duty_cycle)
{
    TimeSlot_t *ts = NULL;

    /* Create the list of timeslots for all nodes */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        uint8_t cur_time = 1;

        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        /* Create the timeslots with type Beacon */
        for (; cur_time <= n_beacon_timeslot; cur_time++)
        {
            ts = newTimeSlot(cur_time, 0, TS_BEACON, NULL, false);
            ListAppend(&node->timeslots, (void *)ts);
        }

        /* Create the timeslots with type Shared */
        uint8_t n_shared_timeslot = (uint8_t)((float)slotframe_size * duty_cycle);
        for (; cur_time <= n_shared_timeslot; cur_time++)
        {
            ts = newTimeSlot(cur_time, 0, TS_SHARED, NULL, false);
            ListAppend(&node->timeslots, (void *)ts);
        }

        /* Create the timeslots with type Idle */
        for (; cur_time <= slotframe_size; cur_time++)
        {
            ts = newTimeSlot(cur_time, 0, TS_IDLE, NULL, false);
            ListAppend(&node->timeslots, (void *)ts);
        }
    }

    return (true);
}

bool run_no_schedule(uint8_t sink_id, uint8_t sensor_id, uint32_t average_gen_pkt_ts, uint8_t prob_tx, List *nodesList, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint16_t n_timeslots_log)
{
    bool first_general_log = true;

    List linksList[NUM_CHANNELS];
    for (uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        memset(&linksList[i], 0, sizeof(List)); ListInit(&linksList[i]);
    }
    List blacklist; memset(&blacklist, 0, sizeof(List)); ListInit(&blacklist);
    uint8_t prrMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];

    /* Absolute Slot Number */
    uint64_t asn = 0;

    /* Calculate the slotframe size and clean the information regarding # of pkts transmitted and received */
    uint8_t superframe_length = 0;
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        /* Go over all timeslots and find the one with largest timeslot offset */
        for (ListElem *elem2 = ListFirst(&node->timeslots); elem2 != NULL; elem2 = ListNext(&node->timeslots, elem2))
        {
            TimeSlot_t *ts = (TimeSlot_t *)elem2->obj;
            if (ts->time > superframe_length)   /* We start the timeslots in zero */
            {
                superframe_length = ts->time;
            }
        }
    }


    /* Calculate which file to use - It must start at 1*/
    uint8_t file_suffix = 1;

    /* File name */
    char prr_filename[100];
    snprintf(prr_filename, 100, "%s_%d.dat", prr_file_prefix, file_suffix);

    /* Opening file */
    FILE *fp_prr_file = NULL;
    int res = openFile(&fp_prr_file, prr_filename, "r");
    while (res)
    {
        PRINTF("Processing file %s\n", prr_filename);

        /* Print the time schedule */
        printTimeSlots(nodesList);

        /* Freeing the linksList */
        ListUnlinkAll(&linksList);

        /* Read the new list of links */
        readLinksFile(fp_prr_file, nodesList, &linksList, 100);

        /* Create the prrMatrix */
        createPrrMatrix(prrMatrix, &linksList);


        /* Calculate the maximum asn to be considered for the current file */
        uint64_t n = (uint64_t)(n_timeslots_per_file * (uint64_t)(file_suffix));

        while(asn < n)
        {
            uint16_t time = asn % superframe_length;

            /* Check if we need to output the log */
            if ((asn % n_timeslots_log) == 0)
            {
                noScheduleOutputReliabilityDelayFile(nodesList, first_general_log);
                noScheduleOutputEnergyFile(nodesList, first_general_log);
                first_general_log = false;
            }

            /* Get the sensor node */
            Node_t *sensor_node = getNode(sensor_id, nodesList);

            /* Schedule the next data packet */
            if (sensor_node->nextDataTs < asn)
            {
                sensor_node->nextDataTs = asn + average_gen_pkt_ts  + (rand() % average_gen_pkt_ts) / 10;
            }
            if (sensor_node->nextDataTs == asn)
            {
                if (ListLength(&sensor_node->packets) < NODE_QUEUE_SIZE)
                {
                    Packet_t *pkt = newPacket(sensor_node->cur_dsn, sensor_node->id, asn, sensor_node->curBurstId);
                    sensor_node->cur_dsn++;
                    sensor_node->curBurstId++;
                    ListAppend(&sensor_node->packets, (void *)pkt);
                }
            }

            List *nodesToTX = noScheduleNodesToTX(sink_id, nodesList, time, prob_tx);

            if (ListLength(nodesToTX) > 1)
            {
                /* Update the number of tx pkts and release the packet from nodes */
                for (ListElem *elem = ListFirst(nodesToTX); elem != NULL; elem = ListNext(nodesToTX, elem))
                {
                    Node_t *node = (Node_t *)elem->obj;

                    /* TX failed */
                    node->ts_tx_data++;
                    node->flood_checked = true;

                    /* Release the pkt */
                    ListElem *pkt_elem = ListFirst(&node->packets);
                    ListUnlink(&node->packets, pkt_elem);
                }
            }
            else if(ListLength(nodesToTX) == 1)
            {
                /* Get the node to TX */
                ListElem *node_elem = ListFirst(nodesToTX);
                Node_t *node_tx = (Node_t *)node_elem->obj;

                /* Get the packet to be transmitted */
                ListElem *pkt_elem = ListFirst(&node_tx->packets);
                Packet_t *pkt = (Packet_t *)pkt_elem->obj;

                /* TX successful */
                node_tx->ts_tx_data++;
                node_tx->flood_checked = true;

                /* Get the timeslot */
                TimeSlot_t *ts = getTimeSlot(time + 1, &node_tx->timeslots);

                /* Calculate the frequency to transmit */
                uint8_t freq = fhssOpenwsnChan(ts->freq, asn);

                /* Lets see if our node has a preferred parent (found with RPL) */
                RPL_Neighbor_t *parent = rplGetPreferedParent(node_tx);

                if (parent == NULL)
                {
                    /* For all nodes check if one will receive */
                    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
                    {
                        Node_t *node_rx = (Node_t *)elem->obj;

                        if (node_rx->id != node_tx->id && getNode(node_rx->id, nodesToTX) == NULL)
                        {
                            noScheduleReceivePkt(node_tx, node_rx, pkt, prrMatrix, freq, asn);
                        }
                    }

                    /* Release the packet from transmitter */
                    ListUnlink(&node_tx->packets, pkt_elem);
                }
                else
                {
                    Node_t *node_rx = getNode(parent->id, nodesList);

                    /* Packet received */
                    if (noScheduleReceivePkt(node_tx, node_rx, pkt, prrMatrix, freq, asn))
                    {
                        /* Release the packet from transmitter */
                        ListUnlink(&node_tx->packets, pkt_elem);
                    }
                    else
                    {
                        pkt->n_retries++;
                        if (pkt->n_retries == MAX_PKT_RETRIES)
                        {
                            ListUnlink(&node_tx->packets, pkt_elem);
                        }
                    }
                }
            }
            else
            {
                /* No nodes to TX */
                for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
                {
                    Node_t *node = (Node_t *)elem->obj;

                    TimeSlot_t *ts = getTimeSlot(time + 1, &node->timeslots);
                    if (ts->type == TS_BEACON)
                    {
                        uint8_t draw = rand() % 100;
                        if (draw <= prob_tx)
                        {
                            node->ts_tx_beacon++;
                        }
                        else
                        {
                            node->ts_rx_sucess++;
                        }
                        node->flood_checked = true;
                    }
                    else if(ts->type == TS_SHARED)
                    {
                        /* Empty timeslot */
                        node->ts_rx_failed++;
                        node->flood_checked = true;
                    }
                    else if (ts->type == TS_IDLE)
                    {
                        /* Sleep timeslot */
                        node->ts_sleep++;
                        node->flood_checked = true;
                    }
                }
            }

            /* Go to the next time slot */
            asn++;

            /* Uncheck the flood for all nodes */
            for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
            {
                Node_t *node = (Node_t *)elem->obj;

                if (node->flood_checked == false)
                {
                    continue;
                }
                node->flood_checked = false;
            }
        }

        /* Reading next file */
        file_suffix++;
        snprintf(prr_filename, 100, "%s_%d.dat", prr_file_prefix, file_suffix);
        res = openFile(&fp_prr_file, prr_filename, "r");
    }

    noSchedulePrintPktSink(sink_id, nodesList);

    return (true);
}

bool noScheduleReceivePkt(Node_t *node_tx, Node_t *node_rx, Packet_t *pkt, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t asn)
{
    uint8_t draw = rand() % 100;

    if (draw <= prrMatrix[node_tx->id][node_rx->id][freq])
    {
        /* Check if receiver can receive the packet */
        if (ListLength(&node_rx->packets) < NODE_QUEUE_SIZE || node_rx->type == SINK)
        {
            if (node_rx->curBurstId < pkt->burst_id)
            {
                ListAppend(&node_rx->packets, (void *)pkt);

                /* Update the current burst ID */
                node_rx->curBurstId = pkt->burst_id;
                pkt->n_retries = 0;

                if (node_rx->type == SINK)
                {
                    pkt->delay = asn - pkt->ts_generated;
                }
            }
        }

        /* RX successful */
        node_rx->ts_rx_sucess++;
        node_rx->flood_checked = true;

        return (true);
    }
    else
    {
        /* RX failed */
        node_rx->ts_rx_failed++;
        node_rx->flood_checked = true;

        return (false);
    }
}

void noScheduleOutputReliabilityDelayFile(List *nodesList, bool first_time)
{
    /* Opening file */
    FILE *fp_reliability_delay_output = NULL;
    char file_name[100];

    snprintf(file_name, 100, "reability_delay_floooding.csv");

    if (first_time)
    {
        openFile(&fp_reliability_delay_output, file_name, "w");

        /* Header */
        fprintf(fp_reliability_delay_output, "max_signal, reliability, average_delay, ");

        fprintf(fp_reliability_delay_output, "\n");
        first_time = false;
    }
    else
    {
        openFile(&fp_reliability_delay_output, file_name, "a");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            if (node->type == SINK)
            {
                uint16_t max_burst = 0;
                uint64_t total_delay = 0;
                for (ListElem *elem2 = ListFirst(&node->packets); elem2 != NULL; elem2 = ListNext(&node->packets, elem2))
                {
                    Packet_t *pkt = (Packet_t *)elem2->obj;
                    if (pkt->burst_id > max_burst)
                    {
                        max_burst = pkt->burst_id;
                    }
                    total_delay += pkt->delay;
                }

                if (ListLength(&node->packets) == 0)
                {
                    fprintf(fp_reliability_delay_output, "-1, -1, -1, ");
                }
                else
                {
                    fprintf(fp_reliability_delay_output, "%d, %f, %f, ", max_burst, ListLength(&node->packets)/(float)max_burst, (double)total_delay/(double)ListLength(&node->packets));
                }
                break;
            }
        }

        fprintf(fp_reliability_delay_output, "\n");
    }

    fclose(fp_reliability_delay_output);
}

void noScheduleOutputEnergyFile(List *nodesList, bool first_time)
{
    /* Opening file */
    FILE *fp_energy_output = NULL;
    char file_name[100];

    snprintf(file_name, 100, "energy_floooding.csv");

    if (first_time)
    {
        openFile(&fp_energy_output, file_name, "w");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            /* Header */
            fprintf(fp_energy_output, "ts_tx_data_%d, ts_tx_beacon_%d, ts_rx_success_%d, ts_rx_failed_%d, ts_sleep_%d, ", node->id, node->id, node->id, node->id, node->id);
        }

        fprintf(fp_energy_output, "\n");
        first_time = false;
    }
    else
    {
        openFile(&fp_energy_output, file_name, "a");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_energy_output, "%d, %d, %d, %d, %d, ", node->ts_tx_data, node->ts_tx_beacon, node->ts_rx_sucess, node->ts_rx_failed, node->ts_sleep);
        }

        fprintf(fp_energy_output, "\n");
    }

    fclose(fp_energy_output);
}

void noSchedulePrintPktSink(uint8_t sink_id, List *nodesList)
{
    Node_t *sinkNode = getNode(sink_id, nodesList);

    for (ListElem *elem = ListFirst(&sinkNode->packets); elem != NULL; elem = ListNext(&sinkNode->packets, elem))
    {
        Packet_t *pkt = (Packet_t *)elem->obj;
        PRINTF("Pkt src(%d) DSN(%d) TS(%d) BurstId(%d) Delay(%d)\n", pkt->src_id, pkt->dsn, pkt->ts_generated, pkt->burst_id, pkt->delay);
    }
}

List *noScheduleNodesToTX(uint8_t sink_id, List *nodesList, uint16_t time, uint8_t prob_tx)
{
    /* List of nodes to tx */
    List *list = (List *)malloc(sizeof(List)); memset(list, 0, sizeof(List)); ListInit(list);

    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        /* Only check nodes that are not sink or sensor */
        if (node->id != sink_id)
        {
            TimeSlot_t *ts = getTimeSlot(time + 1, &node->timeslots);

            if(ts != NULL && ts->type == TS_SHARED)
            {
                uint8_t draw = rand() % 100;
                if (ListLength(&node->packets) > 0 &&  draw <= prob_tx)
                {
                    ListAppend(list, (void *)node);
                }
            }
        }
    }

    return (list);
}
