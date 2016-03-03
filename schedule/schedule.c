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
#define FHSS_TSCH_F0 2
#define FHSS_BLACKLIST 3
#define FHSS_DISTRIBUTED_BLACKLIST 4

#define FHSS FHSS_BLACKLIST

int execute_schedule(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, char *prr_file_prefix, uint64_t n_timeslots_per_file)
{
    List blacklist; memset(&blacklist, 0, sizeof(List)); ListInit(&blacklist);
    uint8_t prrMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];

    /* The FHSS technique to be used */
    uint8_t fhss = FHSS;

    /* Absolute Slot Number */
    static uint64_t asn = 0;

    /* Calculate which file to use */
    uint8_t file_suffix = 0;

    /* File name */
    char prr_filename[100];
    snprintf(prr_filename, 100, "%s_%d.dat", prr_file_prefix, file_suffix);

    /* Opening file */
    FILE *fp = NULL;
    int res = openFile(&fp, prr_filename, "r");
    while (res)
    {
        /* Freeing the linksList */
        ListUnlinkAll(linksList);

        /* Read the new list of links */
        readLinksFile(fp, nodesList, linksList, 100);

        /* Create the prrMatrix */
        createPrrMatrix(prrMatrix, linksList);

        /* Print the prrMatrix */
        printPrrMatrix(prrMatrix, ListLength(nodesList));

        if (FHSS == FHSS_BLACKLIST)
        {
            /* Create the black list of channel where at least one PRR is less than THRESHOLD_BLACKCHANNEL */
            ListUnlinkAll(&blacklist);
            createBlacklist(&blacklist, prrMatrix, nodesList, tree, THRESHOLD_BLACKCHANNEL, 5);
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

        uint64_t n = (uint64_t)(n_timeslots_per_file * (uint64_t)(file_suffix + 1));
        while (asn < n)
        {
            uint16_t time = asn % superframe_length;

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
                        freq = openwsn_fhss_calculate_chan(ts->freq, asn, superframe_length);
                    }
                    else if (fhss == FHSS_TSCH_F0)
                    {
                        freq = tsch_function0_calculate_chan(ts->freq, asn, superframe_length);
                    }
                    else if (fhss == FHSS_BLACKLIST)
                    {
                        freq = blacklist_calculate_chan(&blacklist, ts->freq, asn, superframe_length);
                    }
                    else if (fhss == FHSS_DISTRIBUTED_BLACKLIST)
                    {
                        freq = distributed_blacklist_calculate_chan(parent, node, prrMatrix, asn, superframe_length);
                    }
                    else if (fhss == FHSS_NONE)
                    {
                        freq = ts->freq;
                    }

                    /* Check if we need to transmit, because it may be a relay packet and the last RX may have been lost */
                    if (ts->relay && node->last_rx == false)
                    {
                        node->last_rx = true;
                        continue;
                    }

                    /* Check if transmission will succeed */
                    uint8_t draw = rand() % 100;
                    if (draw <= prrMatrix[node->id][parent->id][freq])
                    {
                        node->pkt_tx_success++;
                        parent->pkt_rx_success++;
                    }
                    else
                    {
                        node->pkt_tx_failed++;
                        parent->pkt_rx_failed++;
                        parent->last_rx = false;
                    }

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
        res = openFile(&fp, prr_filename, "r");
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
