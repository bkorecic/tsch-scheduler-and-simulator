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

#define FHSS_NONE 0
#define FHSS_OPENWSN 1
#define FHSS_CENTRALIZED_BLACKLIST 2
#define FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM 3
#define FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM 4
#define FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM 5
#define FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL 6

#define FHSS FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL

int execute_schedule(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, char *prr_file_prefix, uint64_t n_timeslots_per_file, uint16_t n_timeslots_log)
{
    List blacklist; memset(&blacklist, 0, sizeof(List)); ListInit(&blacklist);
    uint8_t prrMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];

    /* The FHSS technique to be used */
    uint8_t fhss = FHSS;

    /* Absolute Slot Number */
    static uint64_t asn = 0;

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

        /* Freeing the linksList */
        ListUnlinkAll(linksList);

        /* Read the new list of links */
        readLinksFile(fp_prr_file, nodesList, linksList, 100);

        /* Create the prrMatrix */
        createPrrMatrix(prrMatrix, linksList);

        /* Create the current centralized blacklist if needed */
        if (fhss == FHSS_CENTRALIZED_BLACKLIST)
        {
            /* Create the black list of channel where at least one PRR is less than THRESHOLD_BLACKCHANNEL */
            ListUnlinkAll(&blacklist);
            createBlacklist(&blacklist, prrMatrix, nodesList, tree, THRESHOLD_BLACKCHANNEL, 10);
            for (ListElem *elem = ListFirst(&blacklist); elem != NULL; elem = ListNext(&blacklist, elem))
            {
                uint8_t channel = (uint8_t)elem->obj;
                PRINTF("Channel blacked %d\n", channel);
            }
        }

        /* Calculate the slotframe size */
        uint8_t superframe_length = 0;
        for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
        {
            Node_t *node = (Node_t *)elem->obj;
            if (ListLength(&node->timeslots) > superframe_length)   /* We start the timeslots in zero */
            {
                superframe_length = ListLength(&node->timeslots);
            }
        }

        uint64_t n = (uint64_t)(n_timeslots_per_file * (uint64_t)(file_suffix));
        while (asn < n)
        {
            uint16_t time = asn % superframe_length;

            /* Check if we need to output the log */
            if ((asn % n_timeslots_log) == 0)
            {
                outputRegretFile(nodesList, fhss);
                outputThroughputFile(nodesList, fhss);
                outputPullArms(nodesList, fhss);
            }

            /* Finding nodes that transmit at time slot 'time' */
            for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
            {
                Node_t *node = (Node_t *)elem->obj;
                TimeSlot_t *ts = getTimeSlot(time + 1, &node->timeslots);

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

                    /* Check if we need to transmit, because it may be a relay packet and the last RX may have been lost */
                    if (ts->relay && node->last_rx == false)
                    {
                        continue;
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

                    /* Check if transmission will succeed */
                    uint8_t draw = rand() % 100;
                    if (draw <= prrMatrix[node->id][parent->id][freq])
                    {
                        node->pkt_tx_success++;
                        parent->pkt_rx_success++;
                        node->last_rx = true;

                        /* Update the reward for that channel with a sucessful transmission */
                        parent->avg_reward[node->id][freq] = parent->avg_reward[node->id][freq]*(1.0 - MAB_REWARD_SUCESS_WEIGHT) + MAB_REWARD_SUCESS * MAB_REWARD_SUCESS_WEIGHT;

                    }
                    else
                    {
                        node->pkt_tx_failed++;
                        parent->pkt_rx_failed++;
                        parent->last_rx = false;

                        /* Update the reward for that channel with a failed transmission */
                        parent->avg_reward[node->id][freq] = parent->avg_reward[node->id][freq]*(1.0 - MAB_REWARD_SUCESS_WEIGHT) + MAB_REWARD_FAILED * MAB_REWARD_SUCESS_WEIGHT;

                        /* Update the cumulative regret */
                        if (draw <= prrMatrix[node->id][parent->id][parent->optimal_freq])
                        {
                            parent->cumulative_regret += (MAB_REWARD_SUCESS - MAB_REWARD_FAILED); /* The optimal policy would have otbained MAB_REWARD_SUCESS */
                            node->cumulative_regret += (MAB_REWARD_SUCESS - MAB_REWARD_FAILED); /* The optimal policy would have otbained MAB_REWARD_SUCESS */
                        }
                    }

                    /*if (parent->id == 0)
                    {
                        char line[100];
                        snprintf(line, 100, "FHSS - ts = %ld, node %d, freq = %d, optimal_freq = %d, regret = %d\n", asn, node->id, freq, parent->optimal_freq, parent->cumulative_regret);
                        printFile("fhss.dat", line);
                    }*/

                    /* We keep track of the wors prr to calculate the minimum throughput obtained in each path */
                    if (node->worst_prr < prrMatrix[node->id][parent->id][freq])
                    {
                        node->worst_prr = prrMatrix[node->id][parent->id][freq];
                    }
                }
            }

            /* Go to the next time slot */
            asn++;
        }

        /* Reading the next file */
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

void outputRegretFile(List *nodesList, uint8_t fhss)
{
    /* Opening file */
    FILE *fp_regret_output = NULL;
    char file_name[100];

    static bool first_time = true;

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

void outputThroughputFile(List *nodesList, uint8_t fhss)
{
    /* Opening file */
    FILE *fp_throughput_output = NULL;
    char file_name[100];

    static bool first_time = true;

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

void outputPullArms(List *nodesList, uint8_t fhss)
{
    /* Opening file */
    FILE *fp_arms_output = NULL;
    char file_name[100];

    static bool first_time = true;

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

            fprintf(fp_arms_output, "n_pulls_%d, n_optimal_pulls_%d, perc_optimal_%d ", node->id, node->id, node->id);
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

