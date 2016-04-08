#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "util/debug.h"
#include "util/files.h"
#include "util/print.h"
#include "util/defs.h"
#include "mcc/mcc.h"
#include "mcc/cms_tree.h"
#include "tasa/tasa.h"
#include "modesa/modesa.h"
#include "schedule/schedule.h"

#define PROTOCOL                MCC_ICRA
#define SINK_NODE               0
#define CHANNEL                 15      /* Channel to be considered for single-channel algorithms */
#define EXECUTE_SCHEDULE        1       /* This is 1 if we are going to simulate the schedule */
#define EXPORT_MASK_CHANNELS    1       /* This is 1 if we are going to output a mask with all channels that could be used
                                        in the schedule file. This is used for distributed FHSS implementation */
#define ETX_THRESHOLD           0.9

#define DATA_FILE "data/prr_tutornet/experiment_blacklist/real_prr_1.dat"
//#define DATA_FILE "prr_file.dat"
#define LINKS_PREFIX "data/prr_tutornet/experiment_blacklist/real_prr"
#define TREE_FILE "tree.dat"

void readPrrFile(char *file_name, List *nodesList, List linksList[]);
void initializeTree(uint8_t alg, Tree_t **tree, List *nodesList, uint8_t sink_id, bool conMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[], int8_t channel);
void createMatrices(List *nodesList, List linksList[], float prrMatrix[][MAX_NODES][NUM_CHANNELS], bool conMatrix[][MAX_NODES][NUM_CHANNELS], \
                    bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS]);

void printHelp(void)
{
    printf("HELP:\n");
    printf("./Scheduling <alg> <sink_id> <channel> <execute_sch> <export_mask_channels> <ext_threshold> <file_name>:\n");
    printf("<alg>: 0 - MCC_ICRA; 1 - MCC_CQAA; 2 - MCC_CQARA; 3 - TASA; 4 - MODESA\n");
    printf("<sink_id>: 0 to N\n");
    printf("<channel>: 0 to 15\n");
    printf("<execute_sch>: 0 or 1\n");
    printf("<export_mask_channels>: 0 or 1\n");
    printf("<etx_threshold>: 0.0 to 1.0\n");
    printf("<file_name>: file name (including extension)\n");
}

int main(int argc, char *argv[])
{
    uint8_t sink_id, alg, channel;
    bool execute_sch, export_mask_channels;
    float etx_threshold;
    char file_name[50];

    /* Checking if we have user defined parameters */
    if (argc > 1)
    {
        if (strcmp(argv[1],"-h") == 0)
        {
            printHelp();
            return 0;
        }

        alg = atoi(argv[1]);
        sink_id = atoi(argv[2]);
        channel = atoi(argv[3]);
        execute_sch = atoi(argv[4]);
        export_mask_channels = atoi(argv[5]);
        etx_threshold = atoi(argv[6]);
        strcpy(file_name,argv[7]);
    }
    /* Use hard-coded parameters */
    else
    {
        alg = PROTOCOL;
        sink_id = SINK_NODE;
        channel = CHANNEL;
        execute_sch = EXECUTE_SCHEDULE;
        export_mask_channels = EXPORT_MASK_CHANNELS;
        etx_threshold = ETX_THRESHOLD;
        strcpy(file_name, DATA_FILE);
    }

    /* Initializing the RGN */
    time_t t;
    srand((unsigned) time(&t));

    /* List of nodes */
    List nodesList; memset(&nodesList, 0, sizeof(List)); ListInit(&nodesList);

    /* List of links */
    List linksList[NUM_CHANNELS];
    for (uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        memset(&linksList[i], 0, sizeof(List)); ListInit(&linksList[i]);
    }

    /* Read input from file with PRR values*/
    readPrrFile(file_name, &nodesList, linksList);

    /* Create the ETX matrix */
    float etxMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];
    memset(etxMatrix, 0, MAX_NODES * MAX_NODES * NUM_CHANNELS * sizeof(float));
    createEtxMatrix(etxMatrix, linksList);

    /* Create the connectivity matrix considering any PPR */
    bool conMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];
    memset(conMatrix, false, MAX_NODES * MAX_NODES * NUM_CHANNELS * sizeof(bool));
    createConnectivityMatrix(conMatrix, linksList, 1.0/etx_threshold);

    /* Create the interference matrix considering any interference threshold */
    bool intMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];
    memset(intMatrix, false, MAX_NODES * MAX_NODES * NUM_CHANNELS * sizeof(bool));
    createInterferenceMatrix(intMatrix, linksList, 1.0);

    /* Create the conflict matrix considering the connectivity, interference and cmsTree */
    bool confMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];
    memset(confMatrix, false, MAX_NODES * MAX_NODES * NUM_CHANNELS * sizeof(bool));
    createConflictMatrix(intMatrix, &nodesList, confMatrix, false);

    /* Create the distribution tree */
    Tree_t *tree; initializeTree(alg, &tree, &nodesList, sink_id, conMatrix, linksList, channel);

    /* Print network parameters */
    printNetworkParameters(tree, linksList, &nodesList, conMatrix, intMatrix, confMatrix, etxMatrix);

    /* Lets choose which protocol we want to work with */
    if (alg == MCC_ICRA)
    {
        main_mcc(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, NULL, false, false, channel, etx_threshold);
    }
    else if (alg == MCC_CQAA)
    {
        main_mcc(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, etxMatrix, false, true, -1, etx_threshold);
    }
    else if (alg == MCC_CQARA)
    {
        main_mcc(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, etxMatrix, true, true, -1, etx_threshold);
    }
    else if (alg == TASA)
    {
        main_tasa(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, channel);
    }
    else if (alg == MODESA)
    {
        main_modesa(&nodesList, &linksList[channel], tree, sink_id, 1, intMatrix, confMatrix, channel);
    }
    else if (alg == MODESA_IP)
    {
        main_modesa_ip(&nodesList, tree, sink_id, 1, confMatrix, channel);
    }

    /* Execute the schedule */
    if (execute_sch)
    {
        execute_schedule(&nodesList, linksList, tree, sink_id, LINKS_PREFIX, 900000, 60000, 60000);
        printPacketTxRxperNode(&nodesList);
    }

    /* Write output to files */
    output(alg, &nodesList, tree, TREE_FILE, export_mask_channels, false);

    return (0);
}

void readPrrFile(char *file_name, List *nodesList, List linksList[])
{
    /* Input file */
    FILE *fp = NULL;

    /* Opening file */
    int res = openFile(&fp, file_name, "r");

    if (res != true)
    {
        EXIT("Error while reading file %s", file_name);
    }

    /* Read the input file and insert links into the list */
    PRINTF("Reading the file with number of nodes and links!\n");
    readFile(fp, nodesList, linksList, NULL, 100);

    fclose(fp);
}

void initializeTree(uint8_t alg, Tree_t **tree, List *nodesList, uint8_t sink_id, bool conMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[], int8_t channel)
{
    uint8_t res = 0;

    /* Input file */
    FILE *fp = NULL;

    if ((alg == TASA) || (alg == MODESA) || (alg == MODESA_IP))
    {
        /* Opening file */
        res = openFile(&fp, TREE_FILE, "r");
        if (res != true) EXIT("Error while reading file %s", TREE_FILE);

        /* Create the connected tree */
        if (alg == TASA)
        {
            *tree = newTree(getNode(sink_id, nodesList), TASA_TREE);
        }
        else if ((alg == MODESA) || (alg == MODESA_IP))
        {
            *tree = newTree(getNode(sink_id, nodesList), MODESA_TREE);
        }

        if (!readFile(fp, nodesList, NULL, *tree, 100))
        {
            EXIT("It is impossible to create the tree from the given file.\n");
        }
        fclose(fp);
    }
    else if (alg == MCC_ICRA || alg == MCC_CQAA)
    {
        /* Create the Capacitated Minimum Spanning Tree */
        Node_t *sink = getNode(sink_id, nodesList);
        sink->type = SINK;
        *tree = constructCMSTreeSingleChannel(sink, nodesList, conMatrix, channel);
    }
    else if (alg == MCC_CQARA)
    {
        /* Create the Capacitated Minimum Spanning Tree with multiple channels */
        Node_t *sink = getNode(sink_id, nodesList);
        sink->type = SINK;
        *tree = constructCMSTreeMultipleChannel(sink, nodesList, conMatrix, linksList);
    }

    /* Set the type of each node properly */
    setTypeOfNodes(sink_id, *tree);
}




