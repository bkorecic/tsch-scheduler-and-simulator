#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "files.h"
#include "debug.h"
#include "defs.h"
#include "../util/print.h"

#define MAX_LINE_SIZE 1024

void printNetworkParameters(Tree_t *tree, List *linksList, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], \
                            bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], float etxMatrix[][MAX_NODES][NUM_CHANNELS])
{
    uint8_t n_nodes = ListLength(nodesList);

    PRINTF("Printing all links:\n");
    for (ListElem *elem = ListFirst(linksList); elem != NULL; elem = ListNext(linksList, elem))
    {
        /* Get the current Link */
        Link_t *link = (Link_t *)elem->obj;
        PRINTF("Link %d->%d etx %f\n", link->n1->id, link->n2->id, link->etx);
    }

    PRINTF("\nConnectivity matrices\n");
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        PRINTF("Channel %d:\n", c);
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            for (uint8_t j = 0; j < n_nodes; j++)
            {
                if (conMatrix[i][j][c]) PRINTF("1, ");
                else PRINTF("0, ");
            }
            PRINTF("\n");
        }
        PRINTF("\n");
    }

    PRINTF("\nIntereference matrices\n");
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        PRINTF("Channel %d:\n", c);
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            for (uint8_t j = 0; j < n_nodes; j++)
            {
                if (intMatrix[i][j][c]) PRINTF("1, ");
                else PRINTF("0, ");
            }
            PRINTF("\n");
        }
        PRINTF("\n");
    }

    PRINTF("\nConflict matrices\n");
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        PRINTF("Channel %d:\n", c);
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            for (uint8_t j = 0; j < n_nodes; j++)
            {
                if (confMatrix[i][j][c]) PRINTF("1, ");
                else PRINTF("0, ");
            }
            PRINTF("\n");
        }
        PRINTF("\n");
    }

    PRINTF("\nETX matrices\n");
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        PRINTF("Channel %d:\n", c);
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            for (uint8_t j = 0; j < n_nodes; j++)
            {
                if (etxMatrix[i][j][c] == FLT_MAX) PRINTF("Inf, ");
                else PRINTF("%f, ", etxMatrix[i][j][c]);
            }
            PRINTF("\n");
        }
        PRINTF("\n");
    }

    PRINTF("\nList of nodes:\n");
    printListNodes(nodesList);

    PRINTF("\nFinal Tree:\n");
    printTree(tree);

    fflush(stdout);

}

void printPrrMatrix(uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t n_nodes)
{
    PRINTF("PRR matrices\n");
    for (uint8_t c = 0; c < NUM_CHANNELS; c++)
    {
        PRINTF("Channel %d:\n", c);
        for (uint8_t i = 0; i < n_nodes; i++)
        {
            for (uint8_t j = 0; j < n_nodes; j++)
            {
                PRINTF("%d, ", prrMatrix[i][j][c]);
            }
            PRINTF("\n");
        }
        PRINTF("\n");
    }
    fflush(stdout);
}

void output(uint8_t alg, List *nodesList, Tree_t *tree, char *tree_filename, bool export_mask_channels, bool use_eui64)
{
    /* Output file */
    FILE *fp = NULL;
    uint8_t res;

    if (alg == MCC_ICRA || alg == MCC_CQARA || alg == MCC_CQAA)
    {
        /* Output the formed tree in a file */
        res = openFile(&fp, tree_filename, "w");
        if (!res)
        {
            EXIT("Error while writing file %s\n", tree_filename);
        }

        /* Generate the file with the tree */
        generateTreeFile(fp, tree, tree);
        fclose(fp);
    }

    /* Outputing the formed schedule */
    res = openFile(&fp, "ext_schedule.c", "w");
    if (!res)
    {
        EXIT("Error while writing file %s\n", "ext_schedule.h");
    }

    /* Generate the file with the schedule */
    generateScheduleFileOpenWSN(fp, nodesList, tree, export_mask_channels, use_eui64);
    fclose(fp);

    /* Outputing the topology */
    res = openFile(&fp, "topology.c", "w");
    if (!res)
    {
        EXIT("Error while writing file %s\n", "topology.c");
    }

    /* Generate the file with the topology */
    generateTreeFileOpenWSN(fp, nodesList, tree);
    fclose(fp);
}

void printPacketTxRxperNode(List *nodesList)
{
    FILE *fp = NULL;
    uint8_t res = openFile(&fp, "data/results.dat", "w");
    if (!res)
    {
        EXIT("Error while writing file data/results.dat\n");
    }

    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        PRINTF("Node %d, RX suc %d, TX suc %d, RX failed %d, TX failed %d.\n", \
                    node->id, node->pkt_rx_success, node->pkt_tx_success, node->pkt_rx_failed, node->pkt_tx_failed);
        fprintf(fp, "Node %d, RX suc %d, TX suc %d, RX failed %d, TX failed %d.\n", \
                    node->id, node->pkt_rx_success, node->pkt_tx_success, node->pkt_rx_failed, node->pkt_tx_failed);
    }
    fclose(fp);
}

void printFile(char *filename, char *line)
{
    FILE *fp = NULL;
    uint8_t res = openFile(&fp, filename, "a");
    if (!res)
    {
        EXIT("Error while writing file in printFile\n");
    }

    fprintf(fp, line);

    fclose(fp);
}

