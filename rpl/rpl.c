#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "rpl.h"
#include "../util/defs.h"
#include "../util/debug.h"

int execute_rpl(List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t fhss, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint32_t average_asn_per_dio)
{
    /* This list has all nodes that have a DIO do transmit */
    List dio_to_transmit;
    memset(&dio_to_transmit, 0, sizeof(List)); ListInit(&dio_to_transmit);

    /* Initialize the RPL fields for all nodes */
    init_rpl(List *nodesList, uint8_t sink_id);

    /* Schedule first TX of DIO (from sink) */
    Node_t *sink = getNode(sink_id, nodesList);
    rplScheduleDIO(&dio_to_transmit, sink, rplGetNextDIOTime(sink));

    List linksList[NUM_CHANNELS];
    for (uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        memset(&linksList[i], 0, sizeof(List)); ListInit(&linksList[i]);
    }

    uint8_t prrMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];

    /* Absolute Slot Number */
    uint64_t asn = 0;

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
            /* Find who is the next node to TX a DIO */
            ListElem *elem = ListFirst(&dio_to_transmit);
            Node_t *nextNode = (Node_t *)elem1->obj;
            ListUnlink(&dio_to_transmit, elem);

            /* Update the current ASN */
            asn = nextNode->nextAsnToTxDIO;


        }

        /* Reading next file */
        file_suffix++;
        snprintf(prr_filename, 100, "%s_%d.dat", prr_file_prefix, file_suffix);
        res = openFile(&fp_prr_file, prr_filename, "r");
    }

    return (true);
}

void init_rpl(List *nodesList, uint8_t sink_id)
{
    /* Create the list of timeslots for all nodes */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        if (node->id == sink_id)
        {
            node->dagRank = MINHOPRANKINCREASE;
            node->synced = true;
        }
        else
        {
            node->dagRank = DEFAULTDAGRANK;
            node->synced = false;
        }
    }
}

uint64_t rplGetNextDIOASN(Node_t *node, uint32_t average_asn_per_dio)
{
    uint64_t nextDIO = node->nextAsnToTxDIO + average_asn_per_dio;

    return (nextDIO);
}
