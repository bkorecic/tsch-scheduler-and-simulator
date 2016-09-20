#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "rpl.h"
#include "../util/defs.h"
#include "../util/debug.h"
#include "../util/files.h"
#include "mrhof_rpl.h"
#include "tamu_rpl.h"
#include "../mcc/time_schedule.h"
#include "../schedule/fhss.h"

RPL_Neighbor_t *newNeighbor(uint16_t node_id);
RPL_Neighbor_t *findNeighbor (Node_t *node, uint16_t neighborID);
void rplPrintTree(List *nodesList);

int execute_rpl(uint8_t rpl_alg, List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t channel, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka)
{
    uint32_t tamu_sample_round = 0;

    /* This list has all nodes that have a DIO do transmit */
    List dio_to_transmit;
    memset(&dio_to_transmit, 0, sizeof(List)); ListInit(&dio_to_transmit);

    /* This list has all nodes that have a Keep Alive do transmit */
    List ka_to_transmit;
    memset(&ka_to_transmit, 0, sizeof(List)); ListInit(&ka_to_transmit);

    /* Initialize the RPL fields for all nodes */
    init_rpl(nodesList, sink_id);

    /* Schedule first TX of DIO (from sink) */
    Node_t *sink = getNode(sink_id, nodesList);
    rplScheduleDIO(&dio_to_transmit, sink, rplGetNextDIOASN(sink, min_asn_per_dio));

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
            /* Calculate the current channel */
            uint8_t freq = fhssOpenwsnChan(channel, asn);

            /* Check if we have to start a new round of sampling on TAMU_RPL */
            uint16_t cur_tamu_sample_round = asn % N_TIMESLOTS_TAMU_RPL;
            if (rpl_alg == RPL_TAMU && cur_tamu_sample_round > tamu_sample_round)
            {
                tamuUpdateParents(nodesList);
                tamu_sample_round = cur_tamu_sample_round;
            }

            /* Find who is the next node to TX a DIO */
            ListElem *dio_elem = ListFirst(&dio_to_transmit);
            Node_t *dioNode = NULL;
            uint64_t asn_dio = LONG_MAX;
            if (dio_elem != NULL)
            {
                dioNode = (Node_t *)dio_elem->obj;
                asn_dio = dioNode->nextAsnToTxDIO;
            }

            /* Find who is the next node to TX a KA */
            ListElem *ka_elem = ListFirst(&ka_to_transmit);
            Node_t *kaNode = NULL;
            uint64_t asn_ka = LONG_MAX;
            if (ka_elem != NULL)
            {
                kaNode = (Node_t *)ka_elem->obj;
                asn_ka = kaNode->nextAsnToTxKA;
            }

            if (asn_dio < asn_ka)
            {
                asn = asn_dio;

                /* Lets transmit a DIO message */
                ListUnlink(&dio_to_transmit, dio_elem);
                rplTXDIO(rpl_alg, dioNode, nodesList, prrMatrix, freq, asn, &dio_to_transmit, &ka_to_transmit, min_asn_per_dio, min_asn_per_ka);
            }
            else if (asn_dio > asn_ka)
            {
                asn = asn_ka;

                /* Lets transmit a KA message */
                ListUnlink(&ka_to_transmit, ka_elem);
                rplTXKA(rpl_alg, kaNode, nodesList, prrMatrix, freq, asn, &ka_to_transmit, min_asn_per_ka);
            }
            else
            {
                asn = asn_dio;

                /* Lets transmit both messages */
                ListUnlink(&dio_to_transmit, dio_elem);
                rplTXDIO(rpl_alg, dioNode, nodesList, prrMatrix, freq, asn, &dio_to_transmit, &ka_to_transmit, min_asn_per_dio, min_asn_per_ka);
                ListUnlink(&ka_to_transmit, ka_elem);
                rplTXKA(rpl_alg, kaNode, nodesList, prrMatrix, freq, asn, &ka_to_transmit, min_asn_per_ka);
            }
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

uint64_t rplGetNextDIOASN(Node_t *node, uint32_t min_asn_per_dio)
{
    /* Lets set the next DIO interval to be average_asn_per_dio + randomness */

    uint64_t nextDIO = min_asn_per_dio + (rand() % min_asn_per_dio) / 10;

    return (nextDIO);
}

uint64_t rplGetNextKAASN(Node_t *node, uint32_t min_asn_per_ka)
{
    /* Lets set the next DIO interval to be average_asn_per_dio + randomness */

    uint64_t nextKA = min_asn_per_ka + (rand() % min_asn_per_ka) / 10;

    return (nextKA);
}

void rplScheduleDIO(List *dio_to_transmit, Node_t *node, uint64_t asn)
{
    node->nextAsnToTxDIO = asn;

    /* Check where to insert the new DIO on the list of transmissions */
    for (ListElem *elem = ListFirst(dio_to_transmit); elem != NULL; elem = ListNext(dio_to_transmit, elem))
    {
        /* Get the current node */
        Node_t *n = (Node_t *)elem->obj;

        if (n->nextAsnToTxDIO >= asn)
        {
            ListInsertBefore(dio_to_transmit, (void *)node, elem);

            return;
        }
    }

    ListAppend(dio_to_transmit, (void *)node);

    return;
}

void rplScheduleKA(List *ka_to_transmit, Node_t *node, uint64_t asn)
{
    node->nextAsnToTxKA = asn;

    /* Check where to insert the new KA on the list of transmissions */
    for (ListElem *elem = ListFirst(ka_to_transmit); elem != NULL; elem = ListNext(ka_to_transmit, elem))
    {
        /* Get the current node */
        Node_t *n = (Node_t *)elem->obj;

        if (n->nextAsnToTxKA >= asn)
        {
            ListInsertBefore(ka_to_transmit, (void *)node, elem);

            return;
        }
    }

    ListAppend(ka_to_transmit, (void *)node);

    return;
}

bool rplProcessTXDIO(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka)
{
    bool flag = false;

    /* For all nodes in the network, check if it will receive the EB */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *rxNode = (Node_t *)elem->obj;

        if (rxNode->id != txNode->id && rxNode->type != SINK)
        {
            /* Probability of packet reception */
            uint8_t probRx = rand() % 100;

            if (prrMatrix[txNode->id][rxNode->id][freq] > probRx)
            {
                /* Packet was succesfully received */
                rplRxDIO(rpl_alg, rxNode, txNode, prrMatrix[txNode->id][rxNode->id][freq]);

                if (rpl_alg == RPL_MRHOF)
                {
                    /* Update all DAG rank calculations and return if there was a change in the tree*/
                    bool updateDag = mrhofUpdateDAGRanks(rxNode);

                    if (!flag && updateDag)
                    {
                        flag = true;
                    }
                }
            }
        }
    }

    return (flag);
}

void rplRxDIO(uint8_t rpl_alg, Node_t *rxNode, Node_t *txNode, uint8_t prr)
{
    RPL_Neighbor_t *neighbor = findNeighbor(rxNode, txNode->id);
    if (neighbor != NULL)
    {
        /* The txNode is already a neighbor, just update the DAGrank of the neighbor */
        neighbor->dagRank = txNode->dagRank;
        neighbor->hop_count = txNode->hop_count;
    }
    else
    {
        /* The txNode is a new neighbor, create a new entry on the candidate parents list */
        neighbor = newNeighbor(txNode->id);
        neighbor->dagRank = txNode->dagRank;
        neighbor->hop_count = txNode->hop_count;
        ListAppend(&rxNode->candidate_parents, (void *)neighbor);
    }

    if (prr >= STABLE_NEIGHBOR_THRESHOLD)
    {
        neighbor->stable = true;
    }
    else
    {
        neighbor->stable = false;
    }
}

bool rplProcessTXKA(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq)
{
    /* Probability of packet reception */
    uint8_t probRx = rand() % 100;

    Node_t *parentNode = rplPreferedParent(txNode, nodesList);
    if (prrMatrix[txNode->id][parentNode->id][freq] > probRx)
    {
        /* KA succesfully received */
        rplRxKA(txNode, parentNode, true, prrMatrix[txNode->id][parentNode->id][freq]);
    }
    else
    {
        /* KA failed */
        rplRxKA(txNode, parentNode, false, prrMatrix[txNode->id][parentNode->id][freq]);
    }
    if (rpl_alg == RPL_MRHOF)
    {
        /* Update all DAG rank calculations and return if there was a change in the tree */
        return (mrhofUpdateDAGRanks(txNode));
    }
    else
    {
        return (false);
    }
}

Node_t *rplPreferedParent(Node_t *node, List *nodesList)
{
    for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor->prefered_parent)
        {
            return (getNode(neighbor->id, nodesList));
        }
    }

    return (NULL);
}

void rplRxKA(Node_t *txNode, Node_t *rxNode, bool succes, uint8_t prr)
{
    RPL_Neighbor_t *neighbor = findNeighbor(txNode, rxNode->id);

    if (succes)
    {
        neighbor->rx_success++;
    }
    else
    {
        neighbor->rx_failed++;
    }

    neighbor->estimated_etx = (float)neighbor->rx_success / (float)(neighbor->rx_failed + neighbor->rx_success);

    if (prr >= STABLE_NEIGHBOR_THRESHOLD)
    {
        neighbor->stable = true;
    }
    else
    {
        neighbor->stable = false;
    }
}

RPL_Neighbor_t *newNeighbor(uint16_t node_id)
{
    RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)malloc(sizeof(RPL_Neighbor_t));

    if (neighbor == NULL)
    {
        ERROR("Not enough memory.\n");
    }
    else
    {
        memset(neighbor, 0, sizeof(RPL_Neighbor_t));
    }

    neighbor->id = node_id;

    return (neighbor);
}

RPL_Neighbor_t *findNeighbor (Node_t *node, uint16_t neighborID)
{
    for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor->id == neighborID)
        {
            return (neighbor);
        }
    }

    return (NULL);
}

void rplTXDIO(uint8_t rpl_alg, Node_t *dioNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka)
{
    /* Process the transmission of an DIO */
    if (rplProcessTXDIO(rpl_alg, dioNode, nodesList, prrMatrix, freq, dio_to_transmit, ka_to_transmit, min_asn_per_dio, min_asn_per_ka))
    {
        /* Print the new tree */
        rplPrintTree(nodesList);
    }

    /* Re-schedule the next DIO for all nodes that are synced and are not on the list of scheduled DIOs */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;

        if (node->synced && !ListFind(dio_to_transmit, (void *)node))
        {
            rplScheduleDIO(dio_to_transmit, node, cur_asn + rplGetNextDIOASN(node, min_asn_per_dio));
        }

        if (node->synced && node->type != SINK && !ListFind(ka_to_transmit, (void *)node))
        {
            rplScheduleKA(ka_to_transmit, node, cur_asn + rplGetNextKAASN(node, min_asn_per_ka));
        }
    }
}

void rplTXKA(uint8_t rpl_alg, Node_t *kaNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *ka_to_transmit, uint32_t min_asn_per_ka)
{
    /* Process the transmission of an KA */
    if (rplProcessTXKA(rpl_alg, kaNode, nodesList, prrMatrix, freq))
    {
        /* Print the new tree */
        rplPrintTree(nodesList);
    }

    /* Schedule the next KA message for that node */
    rplScheduleKA(ka_to_transmit, kaNode, cur_asn + rplGetNextKAASN(kaNode, min_asn_per_ka));
}

void rplPrintTree(List *nodesList)
{
    PRINTF("\nNew RPL tree:\n");
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        for (ListElem *elem2 = ListFirst(&node->candidate_parents); elem2 != NULL; elem2 = ListNext(&node->candidate_parents, elem2))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem2->obj;
            if (neighbor->prefered_parent)
            {
                PRINTF("%d <- %d\n", neighbor->id, node->id);
            }
        }
    }
    PRINTF("\n");
}
