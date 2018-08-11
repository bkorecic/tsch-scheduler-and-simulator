#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include "rpl.h"
#include "mrhof_rpl.h"
#include "tamu_rpl.h"
#include "dijkstra_rpl.h"
#include "../util/defs.h"
#include "../util/debug.h"
#include "../util/files.h"
#include "../mcc/time_schedule.h"
#include "../schedule/fhss.h"

RPL_Neighbor_t *findNeighbor (Node_t *node, uint16_t neighborID);
void rplPrintTree(List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS]);
uint8_t probOptimalNeighbor(Node_t *txNode, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq);
float getEndToEndETX(Node_t *node, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS]);
RPL_Neighbor_t *rplGetPreferedParent(Node_t *node);

uint32_t rpl_rank_interval  = RPL_RANK_INTERVAL;
uint8_t rpl_default_link_cost = DEFAULTLINKCOST;

int run_rpl(uint8_t rpl_alg, List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t channel, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka, uint32_t asn_per_data, uint32_t n_timeslots_per_log, uint8_t log_type)
{
    uint32_t rpl_rank_round = 0;
    uint32_t rpl_data_tx_round = 0;
    uint32_t log_round = 0;
    bool first_general_log = true;

    /* This list has all nodes that have a DIO to transmit */
    List dio_to_transmit;
    memset(&dio_to_transmit, 0, sizeof(List)); ListInit(&dio_to_transmit);

    /* This list has all nodes that have a Keep Alive to transmit */
    List ka_to_transmit;
    memset(&ka_to_transmit, 0, sizeof(List)); ListInit(&ka_to_transmit);

    /* This list has all nodes that have a Data to transmit */
    List data_to_transmit;
    memset(&data_to_transmit, 0, sizeof(List)); ListInit(&data_to_transmit);

    /* This list has all nodes that have a Data to transmit */
    List data_received_at_sink;
    memset(&data_received_at_sink, 0, sizeof(List)); ListInit(&data_received_at_sink);

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
            /* Check if we have to update the prefered parent */
            if ((asn / rpl_rank_interval) > rpl_rank_round)
            {
                //rplPrintTree(nodesList, prrMatrix);
                if (rpl_alg == RPL_TAMU_MULTIHOP_RANK)
                {
                    if (tamuUpdateParents(nodesList, rpl_alg))
                    {
                        rplPrintTree(nodesList, prrMatrix);
                    }
                }
                else if (rpl_alg == RPL_MRHOF)
                {
                    if (mrhofUpdateParents(nodesList, rpl_alg))
                    {
                        rplPrintTree(nodesList, prrMatrix);
                    }
                }
                else if (rpl_alg == RPL_WITH_DIJKSTRA)
                {
                    dijkstraCalculateTree(nodesList, prrMatrix);
                    rplPrintTree(nodesList, prrMatrix);
                }
                rpl_rank_round = asn / rpl_rank_interval;
            }

            /* Check if we need to log the execution */
            if ((asn / n_timeslots_per_log) >= log_round)
            {
                if (log_type & 0b1)
                {
                    rplOutputDAGRankFile(nodesList, rpl_alg, first_general_log);
                }
                if (log_type & 0b10)
                {
                    rplOutputETXFile(nodesList, rpl_alg, prrMatrix, first_general_log);
                }
                if (log_type & 0b100)
                {
                    rplOutputLoopFile(nodesList, rpl_alg, first_general_log);
                }
                if (log_type & 0b1000)
                {
                    rplOutputParentFile(nodesList, rpl_alg, first_general_log);
                }
                if (log_type & 0b10000)
                {
                    rplOutputDataPacketsFile(nodesList, rpl_alg, &data_to_transmit, &data_received_at_sink, first_general_log);
                }
                if (log_type & 0b100000)
                {
                    rplOutputDataPacketsStatsFile(nodesList, rpl_alg, &data_to_transmit, &data_received_at_sink, first_general_log);
                }

                log_round++;
                first_general_log = false;

                /* For Dijkstra we dont need to run RPL */
                if (rpl_alg == RPL_WITH_DIJKSTRA)
                {
                    continue;
                }
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

            /* Find what is the next packet to TX */
            ListElem *data_elem = ListFirst(&data_to_transmit);
            Packet_t *dataPacket = NULL;
            uint64_t asn_data = LONG_MAX;
            if (data_elem != NULL)
            {
                dataPacket = (Packet_t *)data_elem->obj;

                if (!dataPacket->sinkReceived)
                {
                    asn_data = dataPacket->nextAsnToTxData;
                }
            }

            if ((asn_dio <= asn_ka) && (asn_dio <= asn_data) && (asn_dio != LONG_MAX))
            {
                asn = asn_dio;

                /* Calculate the current channel */
                uint8_t freq = fhssOpenwsnChan(channel, asn);

                /* Lets transmit a DIO message */
                ListUnlink(&dio_to_transmit, dio_elem);
                rplTXDIO(rpl_alg, dioNode, nodesList, prrMatrix, freq, asn, &dio_to_transmit, &ka_to_transmit, min_asn_per_dio, min_asn_per_ka);
            }
            else if ((asn_ka <= asn_dio) && (asn_ka <= asn_data) && (asn_ka != LONG_MAX))
            {
                asn = asn_ka;

                /* Calculate the current channel */
                uint8_t freq = fhssOpenwsnChan(channel, asn);

                /* Lets transmit a KA message */
                ListUnlink(&ka_to_transmit, ka_elem);
                rplTXKA(rpl_alg, kaNode, nodesList, prrMatrix, freq, asn, &ka_to_transmit, min_asn_per_ka);
            }
            else if ((asn_data <= asn_ka) && (asn_data <= asn_dio) && (asn_data != LONG_MAX))
            {
                asn = asn_data;

                /* Calculate the current channel */
                uint8_t freq = fhssOpenwsnChan(channel, asn);

                /* Lets transmit a Data message */
                rplTXData(rpl_alg, dataPacket, nodesList, prrMatrix, freq, asn, &data_to_transmit, &data_received_at_sink);
            }

            /* Find if there are more Data packets to be transmitted */
            if ((asn / asn_per_data) > rpl_data_tx_round)
            {
                /* For all non-sink synchronized nodes */
                for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
                {
                    Node_t *node = (Node_t *)elem->obj;

                    if (node->type != SINK && node->synced == true)
                    {
                        uint32_t asn_to_tx = asn + (rand() % asn_per_data) / 10;
                        rplScheduleData(&data_to_transmit, node, asn_to_tx);  /* Schedule a pkt to asn + a random time */
                    }
                }
                rpl_data_tx_round = asn / asn_per_data;
            }

            asn++;
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
            node->dagRank = MINHOPRANKINCREASE;
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
    //uint64_t nextDIO = min_asn_per_dio;

    return (nextDIO);
}

uint64_t rplGetNextKAASN(Node_t *node, uint32_t min_asn_per_ka)
{
    /* Lets set the next DIO interval to be average_asn_per_dio + randomness */

    uint64_t nextKA = min_asn_per_ka + (rand() % min_asn_per_ka) / 10;
    //uint64_t nextKA = min_asn_per_ka;

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

void rplScheduleData(List *data_to_transmit, Node_t *txNode, uint64_t asn)
{
    /* Generate a new Data packet */
    Packet_t *pkt = newPacket(txNode->cur_dsn, txNode->id, asn, 0);
    pkt->nextAsnToTxData = asn;                                     /* Time slot to tx the packet */

    txNode->cur_dsn++;

    /* Check where to insert the new Data packet in the list of transmissions */
    for (ListElem *elem = ListFirst(data_to_transmit); elem != NULL; elem = ListNext(data_to_transmit, elem))
    {
        /* Get the current node */
        Packet_t *pkt_list = (Packet_t *)elem->obj;

        if (pkt->nextAsnToTxData >= asn)
        {
            ListInsertBefore(data_to_transmit, (void *)pkt, elem);

            return;
        }
    }

    ListAppend(data_to_transmit, (void *)pkt);

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
            //uint8_t probRx = 50;

            if (prrMatrix[txNode->id][rxNode->id][freq] > probRx)
            {
                /* Packet was succesfully received */
                rplRxDIO(rpl_alg, txNode, rxNode, rplAveragPRR(txNode->id, rxNode->id, prrMatrix));

                /* Check if DIO was received from a new neighbor */
                bool updateDag;
                if (rpl_alg == RPL_MRHOF)
                {
                    updateDag = mrhofRxDio(rxNode, nodesList);
                }
                else if (rpl_alg == RPL_TAMU_MULTIHOP_RANK)
                {
                    updateDag = tamuRxDio(rxNode, nodesList);
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
    //uint8_t probRx = 50;

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

    //if (rpl_alg == RPL_MRHOF)
    //{
        /* Update all DAG rank calculations and return if there was a change in the tree */
        //return (mrhofUpdateDAGRanks(txNode));
    //}
    //else
    //{
        return (false);
    //}
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

    /* If neighbor->rx_success OR neighbor->rx_failed > 256, divide both by two to avoid overhead when generating beta */
    /* We just need the ratio of them */
    if (neighbor->rx_success > 256 || neighbor->rx_failed > 256)
    {
        neighbor->rx_success /= 2;
        neighbor->rx_failed /= 2;
    }
}

void rplRxData(Node_t *txNode, Node_t *rxNode, Packet_t *pkt, List *data_to_transmit, List *data_received_at_sink, bool succes, uint32_t cur_asn)
{
    RPL_Neighbor_t *neighbor = findNeighbor(txNode, rxNode->id);

    if (succes)
    {
        neighbor->rx_success++;
        txNode->pkt_tx_success++;
        rxNode->pkt_rx_success++;

        if (rxNode->type == SINK)
        {
            pkt->sinkReceived = true;

            /* Remove from data_to_transmit */
            ListElem *elem = ListFind(data_to_transmit, (void *)pkt);
            ListUnlink(data_to_transmit, elem);

            /* Insert into data_received_at_sink */
            ListAppend(data_received_at_sink, (void *)pkt);

        }
        pkt->relay_id = rxNode->id;
        pkt->n_retries = 0;
        pkt->n_hops++;
        pkt->nextAsnToTxData = cur_asn + rand() % 10;
    }
    else
    {
        neighbor->rx_failed++;
        txNode->pkt_tx_failed++;
        rxNode->pkt_rx_failed++;

        if (pkt->n_retries == 3)
        {
            ListElem *elem = ListFind(data_to_transmit, (void *)pkt);
            ListUnlink(data_to_transmit, elem);
        }
        else
        {
            pkt->n_retries++;
            pkt->nextAsnToTxData = cur_asn + rand() % 10;
        }
    }

    /* ETX = 1/PRR */
    neighbor->estimated_etx = (float)(neighbor->rx_failed + neighbor->rx_success) / (float)neighbor->rx_success;

    /* If neighbor->rx_success OR neighbor->rx_failed > 256, divide both by two to avoid overhead when generating beta */
    /* We just need the ratio of them */
    if (neighbor->rx_success > 256 || neighbor->rx_failed > 256)
    {
        neighbor->rx_success /= 2;
        neighbor->rx_failed /= 2;
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

void rplTXDIO(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka)
{
    /* Process the transmission of an DIO */
    if (rplProcessTXDIO(rpl_alg, txNode, nodesList, prrMatrix, freq, dio_to_transmit, ka_to_transmit, min_asn_per_dio, min_asn_per_ka))
    {
        /* Print the new tree */
//        rplPrintTree(nodesList, prrMatrix);
    }

    /* Re-schedule the next DIO and KA for all nodes that are synced and are not on the list of scheduled DIOs */
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
//        rplPrintTree(nodesList, prrMatrix);
    }

    /* Schedule the next KA message for that node */
    if (txNode->synced && !ListFind(ka_to_transmit, (void *)txNode))
    {
        rplScheduleKA(ka_to_transmit, txNode, cur_asn + rplGetNextKAASN(txNode, min_asn_per_ka));
    }
}

void rplTXData(uint8_t rpl_alg, Packet_t *dataPacket, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *data_to_transmit, List *data_received_at_sink)
{
    /* Probability of packet reception */
    uint8_t probRx = rand() % 100;

    Node_t *txNode = getNode(dataPacket->relay_id, nodesList);
    Node_t *parentNode = rplPreferedParent(txNode, nodesList);

    if (parentNode == NULL)
    {
        /* Maybe the neighbor just became unstable */
        return (false);
    }

    if (prrMatrix[txNode->id][parentNode->id][freq] > probRx)
    {
        /* Data succesfully received */
        rplRxData(txNode, parentNode, dataPacket, data_to_transmit, data_received_at_sink, true, cur_asn);
    }
    else
    {
        /* Data failed */
        rplRxData(txNode, parentNode, dataPacket, data_to_transmit, data_received_at_sink, false, cur_asn);
    }

    dataPacket->n_transmissions++;
}

void rplPrintTree(List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS])
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
                PRINTF("%d <- %d (%d)\n", neighbor->id, node->id, rplAveragPRR(node->id, neighbor->id, prrMatrix));
            }
        }
    }
    PRINTF("\n");
    fflush(stdout);
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
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "regret_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "regret_rpl_dijkstra.csv");
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
        if (!openFile(&fp_regret_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

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
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "arms_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "arms_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_arms_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

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
        if (!openFile(&fp_arms_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

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
        else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
        {
            snprintf(file_name, 100, "full_rpl_tamu_multihop_rank_%d.csv", node->id);
        }
        else if (rpl_algo == RPL_WITH_DIJKSTRA)
        {
            snprintf(file_name, 100, "full_rpl_dijkstra_%d.csv", node->id);
        }

        if (first_time)
        {
            if (!openFile(&fp_full_output, file_name, "w"))
            {
                EXIT("Unable to open file %s.\n", file_name);
            }
        }
        else
        {
            if (!openFile(&fp_full_output, file_name, "a"))
            {
                EXIT("Unable to open file %s.\n", file_name);
            }
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
            if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
            {
                fprintf(fp_full_output, "(id=%d,dr==%.0f,bs=%.2f,ns=%d,r_pdr=%.2f);", neighbor->id, neighbor->dagRank, neighbor->beta_sample, neighbor->n_sampled, (float)neighbor->average_prr/100.0);
            }
            else if (rpl_algo == RPL_MRHOF)
            {
                fprintf(fp_full_output, "(id=%d,dr=%.0f,e_pdr=%.2f,r_pdr=%.2f);", neighbor->id, neighbor->dagRank, 1.0/neighbor->estimated_etx, (float)neighbor->average_prr/100.0);
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
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "throughput_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "throughput_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_throughput_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

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
        if (!openFile(&fp_throughput_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_throughput_output, "%d, ", node->pkt_tx_success);//%d, %d, %d, %d, ", node->pkt_rx_success, node->pkt_tx_success, node->pkt_rx_failed, node->pkt_tx_failed);
        }

        fprintf(fp_throughput_output, "\n");
    }

    fclose(fp_throughput_output);
}

void rplOutputDAGRankFile(List *nodesList, uint8_t rpl_algo, bool first_time)
{
    /* Opening file */
    FILE *fp_dagrank_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "dagrank_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "dagrank_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "dagrank_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_dagrank_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_dagrank_output, "dagrank_%d, ", node->id);
        }

        fprintf(fp_dagrank_output, "\n");
    }
    else
    {
        if (!openFile(&fp_dagrank_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }
    }

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        fprintf(fp_dagrank_output, "%d, ", node->dagRank);
    }

    fprintf(fp_dagrank_output, "\n");

    fclose(fp_dagrank_output);
}

void rplOutputETXFile(List *nodesList, uint8_t rpl_algo, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], bool first_time)
{
    /* Opening file */
    FILE *fp_etx_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "etx_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "etx_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "etx_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_etx_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_etx_output, "etx_%d, ", node->id);
        }

        fprintf(fp_etx_output, "\n");
    }
    else
    {
        if (!openFile(&fp_etx_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }
    }

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        fprintf(fp_etx_output, "%f, ", getEndToEndETX(node, nodesList, prrMatrix));
    }

    fprintf(fp_etx_output, "\n");

    fclose(fp_etx_output);
}

void rplOutputLoopFile(List *nodesList, uint8_t rpl_algo, bool first_time)
{
    /* Opening file */
    FILE *fp_loop_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "loop_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "loop_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "loop_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_loop_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_loop_output, "loops_%d, ", node->id);
        }

        fprintf(fp_loop_output, "\n");
    }
    else
    {
        if (!openFile(&fp_loop_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }
    }

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        fprintf(fp_loop_output, "%d, ", node->loops_detected);
    }

    fprintf(fp_loop_output, "\n");

    fclose(fp_loop_output);
}

void rplOutputParentFile(List *nodesList, uint8_t rpl_algo, bool first_time)
{
    /* Opening file */
    FILE *fp_parent_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "parent_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "parent_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "parent_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_parent_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_parent_output, "parent_%d, ", node->id);
        }

        fprintf(fp_parent_output, "\n");
    }
    else
    {
        if (!openFile(&fp_parent_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }
    }

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        bool foundParent = false;
        for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
        {
            RPL_Neighbor_t *neighbor = (RPL_Neighbor_t *)elem->obj;

            if (neighbor->prefered_parent)
            {
                fprintf(fp_parent_output, "%d, ", neighbor->id);
                foundParent = true;
                break;
            }
        }

        if (!foundParent)
        {
            fprintf(fp_parent_output, "%d, ", -1);
        }
    }

    fprintf(fp_parent_output, "\n");

    fclose(fp_parent_output);
}

void rplOutputDataPacketsFile(List *nodesList, uint8_t rpl_algo, List *data_to_transmit, List *data_received_at_sink, bool first_time)
{
    /* Opening file */
    FILE *fp_packets_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "packets_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "packets_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "packets_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_packets_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

        /* Header */
        for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
        {
            Node_t *node = (Node_t *)elem1->obj;

            fprintf(fp_packets_output, "packets_%d, ", node->id);
        }

        fprintf(fp_packets_output, "\n");
    }
    else
    {
        if (!openFile(&fp_packets_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }
    }

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        if (node->type != SINK)
        {
            uint32_t pkt_counter = 0;
            for (ListElem *elem = ListFirst(data_to_transmit); elem != NULL; elem = ListNext(data_to_transmit, elem))
            {
                Packet_t *pkt = (Packet_t *)elem->obj;

                if (pkt->relay_id == node->id)
                {
                    pkt_counter++;
                }
            }
            fprintf(fp_packets_output, "%d, ", pkt_counter);
        }
        else
        {
            fprintf(fp_packets_output, "%d, ", ListLength(data_received_at_sink));
        }
    }
    fprintf(fp_packets_output, "\n");

    fclose(fp_packets_output);
}

void rplOutputDataPacketsStatsFile(List *nodesList, uint8_t rpl_algo, List *data_to_transmit, List *data_received_at_sink, bool first_time)
{
    /* Opening file */
    FILE *fp_packets_output = NULL;
    char file_name[100];

    if (rpl_algo == RPL_MRHOF)
    {
        snprintf(file_name, 100, "packets_stats_rpl_mrhof.csv");
    }
    else if (rpl_algo == RPL_TAMU_MULTIHOP_RANK)
    {
        snprintf(file_name, 100, "packets_stats_rpl_tamu_multihop_rank.csv");
    }
    else if (rpl_algo == RPL_WITH_DIJKSTRA)
    {
        snprintf(file_name, 100, "packets_stats_rpl_dijkstra.csv");
    }

    if (first_time)
    {
        if (!openFile(&fp_packets_output, file_name, "w"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }

        /* Header */
        fprintf(fp_packets_output, "n_tx_average, n_tx_std_dev, n_hops_average, n_hops_std_dev, n_ts_average, n_ts_std_dev\n");
    }
    else
    {
        if (!openFile(&fp_packets_output, file_name, "a"))
        {
            EXIT("Unable to open file %s.\n", file_name);
        }
    }

    float tx_sum, hops_sum, ts_sum, n;
    float tx_average, hops_average, ts_average;
    float tx_std_dev, hops_std_dev, ts_std_dev;
    tx_sum = hops_sum = ts_sum = 0.0;
    tx_average = hops_average = ts_average = 0.0;
    tx_std_dev = hops_std_dev = ts_std_dev = 0.0;

    if (ListLength(data_received_at_sink) == 0)
    {
        n = 1.0;
    }
    else
    {
        n = 0.0;
    }

    for (ListElem *elem = ListFirst(data_received_at_sink); elem != NULL; elem = ListNext(data_received_at_sink, elem))
    {
        Packet_t *pkt = (Packet_t *)elem->obj;

        tx_sum += pkt->n_transmissions;
        hops_sum += pkt->n_hops;
        ts_sum += pkt->nextAsnToTxData - pkt->ts_generated;
        n++;
    }

    tx_average = tx_sum/n;
    hops_average = hops_sum/n;
    ts_average = ts_sum/n;

    for (ListElem *elem = ListFirst(data_received_at_sink); elem != NULL; elem = ListNext(data_received_at_sink, elem))
    {
        Packet_t *pkt = (Packet_t *)elem->obj;

        tx_sum += (tx_average - pkt->n_transmissions) * (tx_average - pkt->n_transmissions);
        hops_sum += (hops_average - pkt->n_hops) * (hops_average - pkt->n_hops);
        ts_sum += (ts_average - (pkt->nextAsnToTxData - pkt->ts_generated)) * (ts_average - (pkt->nextAsnToTxData - pkt->ts_generated));
    }

    tx_std_dev = sqrt(tx_sum/n);
    hops_std_dev = sqrt(hops_sum/n);
    ts_std_dev = sqrt(ts_sum/n);

    fprintf(fp_packets_output, "%f, %f, %f, %f, %f, %f\n", tx_average, tx_std_dev, hops_average, hops_std_dev, ts_average, ts_std_dev);
    fclose(fp_packets_output);
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

RPL_Neighbor_t *getNeighbor(uint16_t node_id, List *neighborsList)
{
    for (ListElem *elem = ListFirst(neighborsList); elem != NULL; elem = ListNext(neighborsList, elem))
    {
        /* Get the current Node */
        RPL_Neighbor_t *n = (RPL_Neighbor_t *)elem->obj;
        if (n->id == node_id)
        {
            return n;
        }
    }
    return (NULL);
}

void rplSetRankInterval(uint32_t new_rpl_rank_interval)
{
    rpl_rank_interval = new_rpl_rank_interval;
}

void rplSetDefaultLinkCost(uint8_t new_rpl_default_link_cost)
{
    rpl_default_link_cost = new_rpl_default_link_cost;
}

float getEndToEndETX(Node_t *node, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS])
{
    if (node->type == SINK)
    {
        return (0);
    }
    else
    {
        RPL_Neighbor_t *prefered_parent = rplGetPreferedParent(node);

        float etx;
        if (prefered_parent != NULL)
        {
            etx = 100.0/(float)rplAveragPRR(node->id, prefered_parent->id, prrMatrix);
        }
        else
        {
            return (1000.0);
        }

        return (etx + getEndToEndETX(getNode(prefered_parent->id, nodesList), nodesList, prrMatrix));
    }
}

bool rplDetectLoop(Node_t* node, RPL_Neighbor_t *neighbor, List *nodesList)
{
    if (neighbor == NULL)
    {
        return (false);
    }

    Node_t *neighborNode = getNode(neighbor->id, nodesList);

    while (neighborNode->type != SINK)
    {
        RPL_Neighbor_t *parent = rplGetPreferedParent(neighborNode);
        if (parent->id == node->id)
        {
            return (true);
        }
        neighborNode = getNode(parent->id, nodesList);
    }

    return (false);
}

RPL_Neighbor_t *rplGetPreferedParent(Node_t *node)
{
    RPL_Neighbor_t *prefered_parent = NULL;
    for (ListElem *elem = ListFirst(&node->candidate_parents); elem != NULL; elem = ListNext(&node->candidate_parents, elem))
    {
        prefered_parent = (RPL_Neighbor_t *)elem->obj;
        if (prefered_parent->prefered_parent == true)
        {
            break;
        }
    }

    return (prefered_parent);
}

uint8_t rplGetDefaultLinkCost(void)
{
    return (rpl_default_link_cost);
}
