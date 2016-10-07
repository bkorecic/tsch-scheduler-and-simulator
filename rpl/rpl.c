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
uint8_t probOptimalNeighbor(Node_t *txNode, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq);

int execute_rpl(uint8_t rpl_alg, List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t channel, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka, uint32_t n_timeslots_per_log)
{
    uint32_t tamu_sample_round = 0;
    uint32_t log_round = 0;
    bool first_general_log = true;

    /* This list has all nodes that have a DIO do transmit */
    List dio_to_transmit;
    memset(&dio_to_transmit, 0, sizeof(List)); ListInit(&dio_to_transmit);

    /* This list has all nodes that have a Keep Alive do transmit */
    List ka_to_transmit;
    memset(&ka_to_transmit, 0, sizeof(List)); ListInit(&ka_to_transmit);

    /* Initialize the RPL fields for all nodes */
    init_rpl(nodesList, sink_id, rpl_alg);

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
            static int counter = 0;
            if ((rpl_alg == RPL_TAMU_GREEDY || rpl_alg == RPL_TAMU_MULTIHOP) && (asn / N_TIMESLOTS_TAMU_RPL) >= tamu_sample_round)
            {
                if (tamuUpdateParents(nodesList, rpl_alg))
                {
                    rplPrintTree(nodesList);
                }
                tamu_sample_round++;
                printf("\nCounter %d\n", counter++);
            }

            /* Check if we need to log the execution */
            if ((asn / n_timeslots_per_log) >= log_round)
            {
                rplOutputRegretFile(nodesList, rpl_alg, first_general_log);
                rplOutputPullArms(nodesList, rpl_alg, first_general_log);
                rplOutputFullLog(nodesList, rpl_alg, prrMatrix, first_general_log);
                rplOutputThroughputFile(nodesList, rpl_alg, first_general_log);
                log_round++;
                first_general_log = false;
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

void init_rpl(List *nodesList, uint8_t sink_id, uint8_t rpl_algo)
{
    /* Create the list of timeslots for all nodes */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        if (node->id == sink_id)
        {
            if (rpl_algo == RPL_MRHOF)
            {
                node->dagRank = MINHOPRANKINCREASE;
            }
            else if (rpl_algo == RPL_TAMU_GREEDY || rpl_algo == RPL_TAMU_MULTIHOP)
            {
                /* Consider Rank just as the sum of ETXs */
                node->dagRank = 0;
            }
            node->synced = true;
            node->hop_count = 0;
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

void rplScheduleDIO(List *dio_to_transmit, Node_t *txNode, uint64_t asn)
{
    txNode->nextAsnToTxDIO = asn;

    /* Check where to insert the new DIO on the list of transmissions */
    for (ListElem *elem = ListFirst(dio_to_transmit); elem != NULL; elem = ListNext(dio_to_transmit, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        if (node->nextAsnToTxDIO >= asn)
        {
            ListInsertBefore(dio_to_transmit, (void *)txNode, elem);

            return;
        }
    }

    ListAppend(dio_to_transmit, (void *)txNode);

    return;
}

void rplScheduleKA(List *ka_to_transmit, Node_t *txNode, uint64_t asn)
{
    txNode->nextAsnToTxKA = asn;

    /* Check where to insert the new KA on the list of transmissions */
    for (ListElem *elem = ListFirst(ka_to_transmit); elem != NULL; elem = ListNext(ka_to_transmit, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        if (node->nextAsnToTxKA >= asn)
        {
            ListInsertBefore(ka_to_transmit, (void *)txNode, elem);

            return;
        }
    }

    ListAppend(ka_to_transmit, (void *)txNode);

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
                rplRxDIO(rpl_alg, txNode, rxNode, rplAveragPRR(txNode->id, rxNode->id, prrMatrix));

                bool updateDag;
                if (rpl_alg == RPL_MRHOF)
                {
                    /* Update all DAG rank calculations and return if there was a change in the tree*/
                    updateDag = mrhofUpdateDAGRanks(rxNode);
                }
                else if (rpl_alg == RPL_TAMU_GREEDY || rpl_alg == RPL_TAMU_MULTIHOP)
                {
                    updateDag = tamuRxDio(rxNode);
                }

                if (!flag && updateDag)
                {
                    flag = true;
                }
            }
        }
    }

    return (flag);
}

void rplRxDIO(uint8_t rpl_alg, Node_t *txNode, Node_t *rxNode, uint8_t prr)
{
    RPL_Neighbor_t *neighbor = findNeighbor(rxNode, txNode->id);

    if (neighbor == NULL)
    {
        /* The txNode is a new neighbor, create a new entry on the candidate parents list */
        neighbor = newNeighbor(txNode->id);
        ListAppend(&rxNode->candidate_parents, (void *)neighbor);
    }

    neighbor->dagRank = txNode->dagRank;
    neighbor->hop_count = txNode->hop_count;

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
    if (parentNode == NULL)
    {
        /* Maybe the neighbor just became unstable */
        return (false);
    }

    uint8_t probOptimal = probOptimalNeighbor(txNode, prrMatrix, freq);
    if (prrMatrix[txNode->id][parentNode->id][freq] > probRx)
    {
        /* KA succesfully received */
        rplRxKA(txNode, parentNode, true);
    }
    else
    {
        /* KA failed */
        rplRxKA(txNode, parentNode, false);

        /* Check if the optimal neighbor would have received */
        if (probOptimal > probRx)
        {
            txNode->cumulative_regret++;
        }
    }

    txNode->n_pull++;
    if (prrMatrix[txNode->id][parentNode->id][freq] == probOptimal)
    {
        txNode->n_optimal_pull++;
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
            Node_t *n = getNode(neighbor->id, nodesList);
            if (n == NULL)
            {
                return (NULL);
            }
            return (n);
        }
    }

    return (NULL);
}

void rplRxKA(Node_t *txNode, Node_t *rxNode, bool succes)
{
    RPL_Neighbor_t *neighbor = findNeighbor(txNode, rxNode->id);

    if (succes)
    {
        neighbor->rx_success++;
        txNode->pkt_tx_success++;
        rxNode->pkt_rx_success++;
    }
    else
    {
        neighbor->rx_failed++;
        txNode->pkt_tx_failed++;
        rxNode->pkt_rx_failed++;
    }

    /* ETX = 1/PRR */
    neighbor->estimated_etx = (float)(neighbor->rx_failed + neighbor->rx_success) / (float)neighbor->rx_success;
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

void rplTXDIO(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka)
{
    /* Process the transmission of an DIO */
    if (rplProcessTXDIO(rpl_alg, txNode, nodesList, prrMatrix, freq, dio_to_transmit, ka_to_transmit, min_asn_per_dio, min_asn_per_ka))
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

void rplTXKA(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *ka_to_transmit, uint32_t min_asn_per_ka)
{
    /* Process the transmission of an KA */
    if (rplProcessTXKA(rpl_alg, txNode, nodesList, prrMatrix, freq))
    {
        /* Print the new tree */
        rplPrintTree(nodesList);
    }

    /* Schedule the next KA message for that node */
    if (txNode->synced && !ListFind(ka_to_transmit, (void *)txNode))
    {
        rplScheduleKA(ka_to_transmit, txNode, cur_asn + rplGetNextKAASN(txNode, min_asn_per_ka));
    }
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

void rplOutputRegretFile(List *nodesList, uint8_t rpl_algo, bool first_time)
{
    /* Opening file */
    FILE *fp_regret_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "regret_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_GREEDY)
    {
        snprintf(file_name, 100, "regret_rpl_tamu_greedy.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP)
    {
        snprintf(file_name, 100, "regret_rpl_tamu_multihop.csv");
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

void rplOutputPullArms(List *nodesList, uint8_t rpl_algo, bool first_time)
{
    /* Opening file */
    FILE *fp_arms_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "arms_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_GREEDY)
    {
        snprintf(file_name, 100, "arms_rpl_tamu_greedy.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP)
    {
        snprintf(file_name, 100, "arms_rpl_tamu_multihop.csv");
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

void rplOutputFullLog(List *nodesList, uint8_t rpl_algo, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], bool first_time)
{
    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        /* Opening file */
        FILE *fp_full_output = NULL;
        char file_name[100];

        if (rpl_algo == RPL_MRHOF)
        {
            snprintf(file_name, 100, "full_rpl_mrhof_%d.csv", node->id);
        }
        else if (rpl_algo == RPL_TAMU_GREEDY)
        {
            snprintf(file_name, 100, "full_rpl_tamu_greedy_%d.csv", node->id);
        }
        else if (rpl_algo == RPL_TAMU_MULTIHOP)
        {
            snprintf(file_name, 100, "full_rpl_tamu_multihop_%d.csv", node->id);
        }

        if (first_time)
        {
            openFile(&fp_full_output, file_name, "w");
        }
        else
        {
            openFile(&fp_full_output, file_name, "a");
        }

        /* Lets get all stable neighbors with minimum hop count */
        List stableNeighbors;
        memset(&stableNeighbors, 0, sizeof(List)); ListInit(&stableNeighbors);
        RPL_Neighbor_t *prefered_parent = NULL;

        for (ListElem *elem2 = ListFirst(&node->candidate_parents); elem2 != NULL; elem2 = ListNext(&node->candidate_parents, elem2))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem2->obj;

            if (neighbor->stable)
            {
                neighbor->average_prr = rplAveragPRR(node->id, neighbor->id, prrMatrix);

                ListAppend(&stableNeighbors, (void *)neighbor);
            }

            if (neighbor->prefered_parent)
            {
                prefered_parent = neighbor;
            }
        }

        /* Print the number of stable neighbors and enumerate them */
        fprintf(fp_full_output, "PP=%d Neighbors(%d)=", prefered_parent == NULL ? -1 : prefered_parent->id, ListLength(&stableNeighbors));

        for (ListElem *elem2 = ListFirst(&stableNeighbors); elem2 != NULL; elem2 = ListNext(&stableNeighbors, elem2))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem2->obj;
            if (rpl_algo == RPL_TAMU_GREEDY || rpl_algo == RPL_TAMU_MULTIHOP)
            {
                fprintf(fp_full_output, "(id=%d,hc=%d,bs=%.2f,ns=%d,ap=%.2f);", neighbor->id, neighbor->hop_count, neighbor->beta_sample, neighbor->n_sampled, (float)neighbor->average_prr/100.0);
            }
            else if (rpl_algo == RPL_MRHOF)
            {
                fprintf(fp_full_output, "(%d,%d,%.2f,%.2f);", neighbor->id, neighbor->dagRank, 1/neighbor->estimated_etx, (float)neighbor->average_prr/100.0);
            }
        }

        fprintf(fp_full_output, "\n");
        fclose(fp_full_output);
    }
}

void rplOutputThroughputFile(List *nodesList, uint8_t rpl_algo, bool first_time)
{
    /* Opening file */
    FILE *fp_throughput_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "throughput_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_GREEDY)
    {
        snprintf(file_name, 100, "throughput_rpl_tamu_greedy.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP)
    {
        snprintf(file_name, 100, "throughput_rpl_tamu_multihop.csv");
    }

    if (first_time)
    {
        openFile(&fp_throughput_output, file_name, "w");
    }
    else
    {
        openFile(&fp_throughput_output, file_name, "a");
    }

    if (first_time)
    {
        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_throughput_output, "tx_suc_%d, ", node->id);//rx_suc_%d, tx_suc_%d, rx_failed_%d, tx_failed_%d, ", node->id, node->id, node->id, node->id);
        }

        fprintf(fp_throughput_output, "\n");
    }
    else
    {
        openFile(&fp_throughput_output, file_name, "a");

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_throughput_output, "%d, ", node->pkt_tx_success);//%d, %d, %d, %d, ", node->pkt_rx_success, node->pkt_tx_success, node->pkt_rx_failed, node->pkt_tx_failed);
        }

        fprintf(fp_throughput_output, "\n");
    }

    fclose(fp_throughput_output);
}

uint8_t probOptimalNeighbor(Node_t *txNode, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq)
{
    uint8_t bestAveragePRR = 0;

    for (ListElem *elem = ListFirst(&txNode->candidate_parents); elem != NULL; elem = ListNext(&txNode->candidate_parents, elem))
    {
        RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

        if (neighbor->stable)
        {
            /* Check the average PRR over ALL frequencies */
            uint8_t average_prr = rplAveragPRR(txNode->id, neighbor->id, prrMatrix);
            if (average_prr > bestAveragePRR)
            {
                bestAveragePRR = average_prr;
            }
        }
    }

    return (bestAveragePRR);
}

uint8_t rplAveragPRR(uint8_t txID, uint8_t rxID, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS])
{
    uint16_t average_prr = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        average_prr += prrMatrix[txID][rxID][i];
    }
    return ((uint8_t)(average_prr/16));
}
