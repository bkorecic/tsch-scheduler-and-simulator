#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/list.h"
#include "../util/files.h"
#include "../util/print.h"
#include "../util/debug.h"
#include "../graphs/graphs.h"
#include "fhss.h"
#include "schedule.h"

uint16_t blacklist_size = CENTRALIZED_BLACKLIST_SIZE;

int execute_schedule(uint8_t fhss, List *draws, List *nodesList, Tree_t *tree, uint8_t sink_id, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint16_t n_timeslots_log, uint8_t pkt_gen_prob)
{
    bool first_general_log = true;
    bool first_ts_log = true;

    List linksList[NUM_CHANNELS];
    for (uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        memset(&linksList[i], 0, sizeof(List)); ListInit(&linksList[i]);
    }
    List blacklist; memset(&blacklist, 0, sizeof(List)); ListInit(&blacklist);
    uint8_t prrMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];

    /* Absolute Slot Number */
    uint64_t asn = 0;

    /* Lets read the random numbers */
    ListElem *drawElem = ListFirst(draws);

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

        /* Clean the main statistics regarding transmissions */
        node->pkt_rx_failed = node->pkt_rx_success = node->pkt_tx_failed = node->pkt_tx_success = 0;
        node->n_pull = node->n_optimal_pull = 0;
        memset(node->avg_reward, 100, MAX_NODES*NUM_CHANNELS);
        node->cumulative_regret = 0;
        node->optimal_freq = 0;
        /* Go over all packets and unlink and free them */
        ListElem *elem3 = ListFirst(&node->packets);
        while (elem3 != NULL)
        {
            Packet_t *pkt = (Packet_t *)elem3->obj;
            ListUnlink(&node->packets, elem3);
            elem3 = ListFirst(&node->packets);
            free(pkt);
        }
        node->cur_dsn = 0;
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

        /* Create the black list of channel where at least one PRR is less than THRESHOLD_BLACKCHANNEL */
        ListUnlinkAll(&blacklist);
        createBlacklist(&blacklist, prrMatrix, nodesList, tree, THRESHOLD_BLACKCHANNEL, blacklist_size);
        for (ListElem *elem = ListFirst(&blacklist); elem != NULL; elem = ListNext(&blacklist, elem))
        {
            uint8_t channel = (uint8_t)elem->obj;
            PRINTF("Channel blacked %d\n", channel);
        }

        /* Calculate the maximum asn to be considered for the current file */
        uint64_t n = (uint64_t)(n_timeslots_per_file * (uint64_t)(file_suffix));

        while(asn < n)
        {
            uint16_t time = asn % superframe_length;

            /* Check if we need to output the log */
            if ((asn % n_timeslots_log) == 0)
            {
                outputRegretFile(nodesList, fhss, first_general_log);
                outputThroughputFile(nodesList, fhss, first_general_log);
                outputPullArms(nodesList, fhss, first_general_log);
                outputReliabilityTxPerPkt(nodesList, fhss, sink_id, first_general_log);
                first_general_log = false;
            }

            /* Finding nodes that transmit at time slot 'time' */
            for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
            {
                Node_t *node = (Node_t *)elem->obj;

                /* Generate new packet if we have to */
                if ((time % superframe_length) == 0)
                {
                    /* Check if the queue is not full, if we should tx in this timeslot and if we are not the sink node */
                    uint8_t tx_attempty = rand() % 100;
                    if ((ListLength(&node->packets) < NODE_QUEUE_SIZE) && (tx_attempty < pkt_gen_prob) && (node->id != sink_id))
                    {
                        Packet_t *pkt = newPacket(node->cur_dsn, node->id);
                        node->cur_dsn++;
                        ListAppend(&node->packets, (void *)pkt);
                    }
                }

                TimeSlot_t *ts = getTimeSlot(time + 1, &node->timeslots);

                /* Check if we need to transmit, because it may be a relay packet and the last RX may have been lost */
                if (ListLength(&node->packets) == 0)
                {
                    continue;
                }

                if (ts != NULL && ts->type == TS_TX)
                {
                    /* Find the parent */
                    Node_t *parent = getParent(tree, node);

                    /* Calculate the actual frequency that will be used */
                    uint8_t freq;
                    if (fhss == FHSS_OPENWSN)
                    {
                        freq = fhssOpenwsnChan(ts->freq, asn);
                    }
                    else if (fhss == FHSS_CENTRALIZED_BLACKLIST)
                    {
                        freq = fhssCentralizedBlacklistChan(parent, &blacklist, asn);
                    }
                    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM)
                    {
                        freq = fhssDistributedBlacklistMABBestArmChan(parent, node, asn);
                    }
                    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM)
                    {
                        freq = fhssDistributedBlacklistMABFirstBestArmChan(parent, node, asn);
                    }
                    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM)
                    {
                        freq = fhssDistributedBlacklistMABFirstGoodArmChan(parent, node, asn);
                    }
                    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL)
                    {
                        freq = fhssDistributedBlacklistOptimalChan(parent, node, prrMatrix, asn);
                    }
                    else if (fhss == FHSS_NONE)
                    {
                        freq = ts->freq;
                    }

                    /* Calculate what would be the optimal channel to be used */
                    parent->optimal_freq = fhssDistributedBlacklistOptimalChan(parent, node, prrMatrix, asn);

                    /* We just pulled one arm */
                    parent->n_pull++;
                    node->n_pull++;
                    if (freq == parent->optimal_freq) {
                        parent->n_optimal_pull++;
                        node->n_optimal_pull++;
                    }

                    uint8_t draw = (uint8_t)drawElem->obj;
                    drawElem = ListNext(draws, drawElem);

                    /* Check if transmission will succeed */
                    if (draw <= prrMatrix[node->id][parent->id][freq])
                    {
                        node->pkt_tx_success++;
                        parent->pkt_rx_success++;

                        /* Remove packet from node */
                        ListElem *elem = ListFirst(&node->packets);
                        Packet_t *pkt = (Packet_t *)elem->obj;
                        ListUnlink(&node->packets, elem);

                        /* Add packet to parent's queue */
                        pkt->n_retries = 0;
                        pkt->n_transmissions++;
                        pkt->n_hops++;
                        /* Check if parent can accommodate the packet */
                        if ((ListLength(&parent->packets) < NODE_QUEUE_SIZE) || (parent->id == sink_id))
                        {
                            ListAppend(&parent->packets, (void *)pkt);
                        }
                        else
                        {
                            /* Packet dropped due to queue overflow */
                            free(pkt);
                        }

                        /* Update the reward for that channel with a sucessful transmission */
                        parent->avg_reward[node->id][freq] = parent->avg_reward[node->id][freq]*(1.0 - MAB_REWARD_SUCESS_WEIGHT) + MAB_REWARD_SUCESS * MAB_REWARD_SUCESS_WEIGHT;

                    }
                    else
                    {
                        node->pkt_tx_failed++;
                        parent->pkt_rx_failed++;

                        /* Check if we have to remove from queue (each packet can be retransmitted a few times) */
                        ListElem *elem = ListFirst(&node->packets);
                        Packet_t *pkt = (Packet_t *)elem->obj;
                        if (pkt->n_retries == MAX_PKT_RETRIES)
                        {
                            ListUnlink(&node->packets, elem);
                            /* Packet dropped due to max n retransmissions */
                            free(pkt);
                        }
                        else
                        {
                            pkt->n_retries++;
                            pkt->n_transmissions++;
                        }

                        /* Update the reward for that channel with a failed transmission */
                        parent->avg_reward[node->id][freq] = parent->avg_reward[node->id][freq]*(1.0 - MAB_REWARD_SUCESS_WEIGHT) + MAB_REWARD_FAILED * MAB_REWARD_SUCESS_WEIGHT;

                        /* Update the cumulative regret */
                        if (draw <= prrMatrix[node->id][parent->id][parent->optimal_freq])
                        {
                            parent->cumulative_regret += (MAB_REWARD_SUCESS - MAB_REWARD_FAILED); /* The optimal policy would have otbained MAB_REWARD_SUCESS */
                            node->cumulative_regret += (MAB_REWARD_SUCESS - MAB_REWARD_FAILED); /* The optimal policy would have otbained MAB_REWARD_SUCESS */
                        }
                    }

                    if (parent->id == 0)
                    {
                        outputTSFile(fhss, asn, freq, prrMatrix[node->id][parent->id][freq], draw, parent->optimal_freq, prrMatrix[node->id][parent->id][parent->optimal_freq], \
                                     parent->pkt_rx_success, first_ts_log);
                        first_ts_log = false;
                    }
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
    return (true);
}

void createBlacklist(List *blacklist, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], List *nodesList, Tree_t *tree, uint8_t prrThreshold, uint8_t n_channels)
{
    uint16_t nBadLinks[NUM_CHANNELS];   /* This array will store the number of links where channel i is bad */
    uint8_t  nChannels[NUM_CHANNELS];   /* This array will store the sorted channels */

    /* Cleaning the nBadLinks */
    memset(nBadLinks, 0, sizeof(uint16_t)*NUM_CHANNELS);

    /* Setting up the array of channels */
    for (uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        nChannels[i] = i;
    }

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *child = (Node_t *)elem1->obj;

        Node_t *parent = getParent(tree, child);

        if (parent != NULL)
        {
            for (uint8_t c = 0; c < NUM_CHANNELS; c++)
            {
                if ((prrMatrix[child->id][parent->id][c] < prrThreshold) || (prrMatrix[parent->id][child->id][c] < prrThreshold))
                {
                    nBadLinks[c]++;
                }
            }
        }
    }

    /* Bublesort to order nBadLinks */
    for (uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        for (uint8_t j = 0; j < NUM_CHANNELS; j++)
        {
            if (nBadLinks[nChannels[i]] > nBadLinks[nChannels[j]])
            {
                uint8_t aux = nChannels[i];
                nChannels[i] = nChannels[j];
                nChannels[j] = aux;
            }
        }
    }

    /* Adding the n_channel channels with more bad links */
    for (uint8_t i = 0; i < n_channels; i++)
    {
        ListAppend(blacklist, (void *)nChannels[i]);
    }
}

void outputRegretFile(List *nodesList, uint8_t fhss, bool first_time)
{
    /* Opening file */
    FILE *fp_regret_output = NULL;
    char file_name[100];

    if (fhss == FHSS_OPENWSN)
    {
        snprintf(file_name, 100, "regret_fhss_openwsn.csv");
    }
    else if (fhss == FHSS_CENTRALIZED_BLACKLIST)
    {
        snprintf(file_name, 100, "regret_fhss_centralized_blacklist.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM)
    {
        snprintf(file_name, 100, "regret_fhss_distributed_blacklist_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM)
    {
        snprintf(file_name, 100, "regret_fhss_distributed_blacklist_first_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM)
    {
        snprintf(file_name, 100, "regret_fhss_distributed_blacklist_first_good_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL)
    {
        snprintf(file_name, 100, "regret_fhss_distributed_blacklist_optimal.csv");
    }
    else if (fhss == FHSS_NONE)
    {
        snprintf(file_name, 100, "regret_fhss_none.csv");
    }

    if (first_time)
    {
        openFile(&fp_regret_output, file_name, "w");

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_regret_output, "node_%d, ", node->id);
        }

        fprintf(fp_regret_output, "\n");
        first_time = false;
    }
    else
    {
        openFile(&fp_regret_output, file_name, "a");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_regret_output, "%d, ", node->cumulative_regret);
        }

        fprintf(fp_regret_output, "\n");
    }

    fclose(fp_regret_output);
}

void outputThroughputFile(List *nodesList, uint8_t fhss, bool first_time)
{
    /* Opening file */
    FILE *fp_throughput_output = NULL;
    char file_name[100];

    if (fhss == FHSS_OPENWSN)
    {
        snprintf(file_name, 100, "throughput_fhss_openwsn.csv");
    }
    else if (fhss == FHSS_CENTRALIZED_BLACKLIST)
    {
        snprintf(file_name, 100, "throughput_fhss_centralized_blacklist.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM)
    {
        snprintf(file_name, 100, "throughput_fhss_distributed_blacklist_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM)
    {
        snprintf(file_name, 100, "throughput_fhss_distributed_blacklist_first_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM)
    {
        snprintf(file_name, 100, "throughput_fhss_distributed_blacklist_first_good_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL)
    {
        snprintf(file_name, 100, "throughput_fhss_distributed_blacklist_optimal.csv");
    }
    else if (fhss == FHSS_NONE)
    {
        snprintf(file_name, 100, "throughput_fhss_none.csv");
    }

    if (first_time)
    {
        openFile(&fp_throughput_output, file_name, "w");

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_throughput_output, "rx_suc_%d, tx_suc_%d, rx_failed_%d, tx_failed_%d, ", node->id, node->id, node->id, node->id);
        }

        fprintf(fp_throughput_output, "\n");
        first_time = false;
    }
    else
    {
        openFile(&fp_throughput_output, file_name, "a");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_throughput_output, "%d, %d, %d, %d, ", node->pkt_rx_success, node->pkt_tx_success, node->pkt_rx_failed, node->pkt_tx_failed);
        }

        fprintf(fp_throughput_output, "\n");
    }

    fclose(fp_throughput_output);
}

void outputPullArms(List *nodesList, uint8_t fhss, bool first_time)
{
    /* Opening file */
    FILE *fp_arms_output = NULL;
    char file_name[100];

    if (fhss == FHSS_OPENWSN)
    {
        snprintf(file_name, 100, "arms_fhss_openwsn.csv");
    }
    else if (fhss == FHSS_CENTRALIZED_BLACKLIST)
    {
        snprintf(file_name, 100, "arms_fhss_centralized_blacklist.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM)
    {
        snprintf(file_name, 100, "arms_fhss_distributed_blacklist_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM)
    {
        snprintf(file_name, 100, "arms_fhss_distributed_blacklist_first_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM)
    {
        snprintf(file_name, 100, "arms_fhss_distributed_blacklist_first_good_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL)
    {
        snprintf(file_name, 100, "arms_fhss_distributed_blacklist_optimal.csv");
    }
    else if (fhss == FHSS_NONE)
    {
        snprintf(file_name, 100, "arms_fhss_none.csv");
    }

    if (first_time)
    {
        openFile(&fp_arms_output, file_name, "w");

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_arms_output, "n_pulls_%d, n_optimal_pulls_%d, perc_optimal_%d, ", node->id, node->id, node->id);
        }

        fprintf(fp_arms_output, "\n");
        first_time = false;
    }
    else
    {
        openFile(&fp_arms_output, file_name, "a");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_arms_output, "%d, %d, %.4f, ", node->n_pull, node->n_optimal_pull, (float)node->n_optimal_pull/(float)node->n_pull);
        }

        fprintf(fp_arms_output, "\n");
    }

    fclose(fp_arms_output);
}

void outputReliabilityTxPerPkt(List *nodesList, uint16_t fhss, uint16_t sink_id, bool first_time)
{
    /* Opening file */
    FILE *fp_reliability_output = NULL;
    char file_name[100];

    if (fhss == FHSS_OPENWSN)
    {
        snprintf(file_name, 100, "reliability_fhss_openwsn.csv");
    }
    else if (fhss == FHSS_CENTRALIZED_BLACKLIST)
    {
        snprintf(file_name, 100, "reliability_fhss_centralized_blacklist.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM)
    {
        snprintf(file_name, 100, "reliability_fhss_distributed_blacklist_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM)
    {
        snprintf(file_name, 100, "reliability_fhss_distributed_blacklist_first_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM)
    {
        snprintf(file_name, 100, "reliability_fhss_distributed_blacklist_first_good_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL)
    {
        snprintf(file_name, 100, "reliability_fhss_distributed_blacklist_optimal.csv");
    }
    else if (fhss == FHSS_NONE)
    {
        snprintf(file_name, 100, "reliability_fhss_none.csv");
    }

    if (first_time)
    {
        openFile(&fp_reliability_output, file_name, "w");

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_reliability_output, "reliability_%d, n_tx_per_pkt_%d, n_rtx_per_pkt_%d, ", node->id, node->id, node->id);
        }

        fprintf(fp_reliability_output, "\n");
        first_time = false;
    }
    else
    {
        openFile(&fp_reliability_output, file_name, "a");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            float reliability = calculateReliability(node, nodesList, sink_id);
            float n_tx_per_pkt = calculteNTxPerPkt(node, nodesList, sink_id);
            float n_rtx_per_pkt = calculteNRTxPerPkt(node, nodesList, sink_id);

            fprintf(fp_reliability_output, "%.4f, %.4f, %.4f, ", reliability, n_tx_per_pkt, n_rtx_per_pkt);
        }

        fprintf(fp_reliability_output, "\n");
    }

    fclose(fp_reliability_output);
}

void outputTSFile(uint8_t fhss, uint64_t asn, uint8_t my_freq, uint8_t prr, uint8_t draw, uint8_t optimal_freq, uint8_t optimal_prr, uint32_t n_rx_pkt, bool first_time)
{
    /* Opening file */
    FILE *fp_ts_output = NULL;
    char file_name[100];

    if (fhss == FHSS_OPENWSN)
    {
        snprintf(file_name, 100, "ts_fhss_openwsn.csv");
    }
    else if (fhss == FHSS_CENTRALIZED_BLACKLIST)
    {
        snprintf(file_name, 100, "ts_fhss_centralized_blacklist.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM)
    {
        snprintf(file_name, 100, "ts_fhss_distributed_blacklist_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM)
    {
        snprintf(file_name, 100, "ts_fhss_distributed_blacklist_first_best_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM)
    {
        snprintf(file_name, 100, "ts_fhss_distributed_blacklist_first_good_arm.csv");
    }
    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL)
    {
        snprintf(file_name, 100, "ts_fhss_distributed_blacklist_optimal.csv");
    }
    else if (fhss == FHSS_NONE)
    {
        snprintf(file_name, 100, "ts_fhss_none.csv");
    }

    if (first_time)
    {
        openFile(&fp_ts_output, file_name, "w");
        fprintf(fp_ts_output, "asn, freq, prr, draw, opt_freq, opt_prr, n_rx_pkts, \n");
        first_time = false;
    }
    else
    {
        openFile(&fp_ts_output, file_name, "a");
        fprintf(fp_ts_output, "%lld, %d, %d, %d, %d, %d, %ld,\n", (long long)asn, my_freq, prr, draw, optimal_freq, optimal_prr, (long)n_rx_pkt);
    }

    fclose(fp_ts_output);
}

void schedulSetBlacklistSize(uint16_t new_blacklist_size)
{
    blacklist_size = new_blacklist_size;
}

float calculateReliability(Node_t *node, List *nodesList, uint16_t sink_id)
{
    Node_t *aux_node;

    /* Find the sink node */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        aux_node = (Node_t *)elem1->obj;

        if (aux_node->id == sink_id)
        {
            break;
        }
    }

    uint32_t n_rcv_pkts = 0;    /* How many packets were received from 'node' */
    uint32_t n_tx_pkts = 0;     /* How many packets were transmitted by 'node' */

    /* Look at all packets received by sink */
    for (ListElem *elem2 = ListFirst(&aux_node->packets); elem2 != NULL; elem2 = ListNext(&aux_node->packets, elem2))
    {
        Packet_t *pkt = (Packet_t *)elem2->obj;

        /* See if the packet is one of interest (if we are calculating for sink, all packets are of interest) */
        if ((pkt->src_id == node->id) || (node->id == sink_id))
        {
            n_rcv_pkts++;
        }
    }

    /* Lets check the number of packets that were generated */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        aux_node = (Node_t *)elem1->obj;

        if ((aux_node->id == node->id) || (node->id == sink_id))
        {
            n_tx_pkts += aux_node->cur_dsn;
        }
    }

    float reliability = 0.0;
    if (n_tx_pkts > 0)
    {
        reliability = (float)n_rcv_pkts/(float)n_tx_pkts;
    }

    return reliability;
}

float calculteNTxPerPkt(Node_t *node, List *nodesList, uint16_t sink_id)
{
    Node_t *aux_node;

    /* Find the sink node */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        aux_node = (Node_t *)elem1->obj;

        if (aux_node->id == sink_id)
        {
            break;
        }
    }

    uint32_t n_rcv_pkts = 0;    /* How many packets were received from 'node' */
    uint32_t n_transmissions = 0;

    /* Look at all packets received by sink */
    for (ListElem *elem2 = ListFirst(&aux_node->packets); elem2 != NULL; elem2 = ListNext(&aux_node->packets, elem2))
    {
        Packet_t *pkt = (Packet_t *)elem2->obj;

        /* See if the packet is one of interest (if we are calculating for sink, all packets are of interest) */
        if ((pkt->src_id == node->id) || (node->id == sink_id))
        {
            n_rcv_pkts++;
            n_transmissions += pkt->n_transmissions;
        }
    }

    float tx_per_pkt = 0.0;
    if (n_rcv_pkts > 0)
    {
        tx_per_pkt = (float)n_transmissions/(float)n_rcv_pkts;
    }

    return tx_per_pkt;
}

float calculteNRTxPerPkt(Node_t *node, List *nodesList, uint16_t sink_id)
{
    Node_t *aux_node;

    /* Find the sink node */
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        aux_node = (Node_t *)elem1->obj;

        if (aux_node->id == sink_id)
        {
            break;
        }
    }

    uint32_t n_rcv_pkts = 0;    /* How many packets were received from 'node' */
    uint32_t n_retransmissions = 0;

    /* Look at all packets received by sink */
    for (ListElem *elem2 = ListFirst(&aux_node->packets); elem2 != NULL; elem2 = ListNext(&aux_node->packets, elem2))
    {
        Packet_t *pkt = (Packet_t *)elem2->obj;

        /* See if the packet is one of interest (if we are calculating for sink, all packets are of interest) */
        if ((pkt->src_id == node->id) || (node->id == sink_id))
        {
            n_rcv_pkts++;
            n_retransmissions += pkt->n_transmissions - pkt->n_hops;
        }
    }

    float tx_per_pkt = 0.0;
    if (n_rcv_pkts > 0)
    {
        tx_per_pkt = (float)n_retransmissions/(float)n_rcv_pkts;
    }

    return tx_per_pkt;
}
