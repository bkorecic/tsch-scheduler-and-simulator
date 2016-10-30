#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/list.h"
#include "../util/files.h"
#include "../util/print.h"
#include "../util/debug.h"
#include "../graphs/graphs.h"
#include "fhss.h"
#include "no-schedule.h"

void noScheduleOutputReliabilityFile(List *nodesList, bool first_time);
void noScheduleOutputEnergyFile(List *nodesList, bool first_time);
void noScheduleOutputDelayFile(List *nodesList, bool first_time);

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
                noScheduleOutputReliabilityFile(nodesList, first_general_log);
                noScheduleOutputEnergyFile(nodesList, first_general_log);
                noScheduleOutputDelayFile(nodesList, first_general_log);
                first_general_log = false;
            }

            /* Finding nodes that transmit at time slot 'time' */
            for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
            {
                Node_t *node_tx = (Node_t *)elem1->obj;

                /* Sensor node */
                if (node_tx->id == sensor_id)
                {
                    /* Schedule the next data packet */
                    if (node_tx->nextDataTs < asn)
                    {
                        node_tx->nextDataTs = asn + average_gen_pkt_ts  + (rand() % average_gen_pkt_ts) / 10;
                    }
                    if (node_tx->nextDataTs == asn)
                    {
                        if (ListLength(&node_tx->packets) < NODE_QUEUE_SIZE)
                        {
                            Packet_t *pkt = newPacket(node_tx->cur_dsn, node_tx->id, asn, node_tx->curBurstId);
                            node_tx->cur_dsn++;
                            node_tx->curBurstId++;
                            ListAppend(&node_tx->packets, (void *)pkt);
                        }
                    }
                }

                /* Check if we need to transmit something */
                /* We dont transmit if we dont have packet, or if we are the sink, or if we are not the sensor and we do not decide to TX */
                uint8_t draw = rand() % 100;
                if (ListLength(&node_tx->packets) == 0 || node_tx->id == sink_id || (node_tx->id != sensor_id && draw > prob_tx))
                {
                    continue;
                }

                TimeSlot_t *ts = getTimeSlot(time + 1, &node_tx->timeslots);
                if (ts != NULL && ts->type != TS_IDLE)
                {
                    /* Calculate the frequency to transmit */
                    uint8_t freq = fhssOpenwsnChan(ts->freq, asn);

                    /* Get the packet to be transmitted */
                    ListElem *pkt_elem = ListFirst(&node_tx->packets);
                    Packet_t *pkt = (Packet_t *)pkt_elem->obj;

                    /* For all nodes check if one will receive */
                    for (ListElem *elem2 = ListFirst(nodesList); elem2 != NULL; elem2 = ListNext(nodesList, elem2))
                    {
                        draw = rand() % 100;
                        Node_t *node_rx = (Node_t *)elem2->obj;
                        if (node_rx->id != node_tx->id)
                        {
                            if (draw <= prrMatrix[node_tx->id][node_rx->id][freq])
                            {
                                /* Check if receiver can accommodate the packet */
                                if ((ListLength(&node_rx->packets) < NODE_QUEUE_SIZE || node_rx->id == sink_id) && node_rx->curBurstId < pkt->burst_id)
                                {
                                    ListAppend(&node_rx->packets, (void *)pkt);

                                    /* Update the current burst ID */
                                    node_rx->curBurstId = pkt->burst_id;

                                    if (node_rx->id == sink_id)
                                    {
                                        pkt->delay = asn - pkt->ts_generated;
                                    }
                                }
                            }
                        }
                    }

                    /* Release the packet from transmitter */
                    ListUnlink(&node_tx->packets, pkt_elem);
                }
            }

            /* Go to the next time slot */
            asn++;
        }

        /* Reading next file */
        file_suffix++;
        snprintf(prr_filename, 100, "%s_%d.dat", prr_file_prefix, file_suffix);
        res = openFile(&fp_prr_file, prr_filename, "r");
    }

    noSchedulePrintPktSink(sink_id, nodesList);

    return (true);
}

void noScheduleOutputReliabilityFile(List *nodesList, bool first_time)
{
}

void noScheduleOutputEnergyFile(List *nodesList, bool first_time)
{
}

void noScheduleOutputDelayFile(List *nodesList, bool first_time)
{
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
