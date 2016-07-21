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
#include "schedule/fhss.h"

#define PROTOCOL                MCC_ICRA
#define SINK_NODE               0
#define CHANNEL                 0          /* Channel to be considered for single-channel algorithms */
#define EXECUTE_SCHEDULE        0           /* This is 1 if we are going to simulate the schedule */
#define EXPORT_MASK_CHANNELS    0           /* This is 1 if we are going to output a mask with all channels that could be used */
#define FHSS                    FHSS_ALL /* FHSS_OPENWSN, FHSS_DISTRIBUTED_BLACKLIST_OPTIMAL FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM */
#define PKT_PROB                1
#define ETX_THRESHOLD           0.5

#define DATA_FILE "data/orc/01/prr40_1.dat"
#define LINKS_PREFIX "data/prr_tutornet/mabo-tsch/prr40"
#define TREE_FILE "tree.dat"

#define N_TIMESLOTS_PER_FILE    23400       // 15 minutes per file and 39 time slots per 1.5 second (900 s x 39 ts / 1.5 s = 23400 ts per file)
#define N_TIMESLOTS_LOG         1560        // log every 1 minute (60 s x 39 ts / 1.5 s = 1560 ts per minute)
#define MAX_N_FILES             100

void readPrrFile(char *file_name, List *nodesList, List linksList[]);
void initializeTree(uint8_t alg, Tree_t **tree, List *nodesList, uint8_t sink_id, bool conMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[], int8_t channel);
void createMatrices(List *nodesList, List linksList[], float prrMatrix[][MAX_NODES][NUM_CHANNELS], bool conMatrix[][MAX_NODES][NUM_CHANNELS], \
                    bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS]);

void printHelp(void)
{
    printf("HELP:\n");
    printf("./Scheduling <alg> <sink_id> <channel> <export_mask_channels> <ext_threshold> <file_name> <execute_sch> <links_prefix> <fhss>:\n");
    printf("<alg>: 0 - MCC_ICRA; 1 - MCC_CQAA; 2 - MCC_CQARA; 3 - TASA; 4 - MODESA\n");
    printf("<sink_id>: 0 to N-1\n");
    printf("<channel>: 0 to 15\n");
    printf("<export_mask_channels>: 0 or 1\n");
    printf("<etx_threshold>: 0.0 to 1.0\n");
    printf("<file_name>: file name (including extension)\n");
    printf("<execute_sch>: 0 or 1\n");
    printf("<links_prefix>: prefix of file names with link information\n");
    printf("<fhss>: 0 - 10 (if execute_sch == 1)\n");
    printf("<pkt_prob>: 0 - 100 (if execute_sch == 1)\n");
}

int main(int argc, char *argv[])
{
    uint8_t sink_id, alg, channel, fhss, pkt_prob;
    bool execute_sch, export_mask_channels;
    float etx_threshold;
    char file_name[50];
    char links_prefix[50];

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
        export_mask_channels = atoi(argv[4]);
        etx_threshold = atof(argv[5]);
        strcpy(file_name,argv[6]);
        execute_sch = atoi(argv[7]);
        if (execute_sch)
        {
            strcpy(links_prefix,argv[8]);
            fhss = atoi(argv[9]);
            pkt_prob = atoi(argv[10]);

            if (fhss == FHSS_CENTRALIZED_BLACKLIST)
            {
                schedulSetBlacklistSize(atoi(argv[11]));
            }
            else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM || \
                     fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM || \
                     fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_BEST_ARM)
            {
                fhssSetEpsilonN(atoi(argv[11]));
                fhssSetEpsilonInitN(atoi(argv[11]));
                fhssSetEpsilonTSIncrN(atoi(argv[12]));
                fhssSetEpsilonMaxN(atoi(argv[13]));

                if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_BEST_ARM)
                {
                    fhssSetMABFirstBestArms(atoi(argv[13]));
                }
                else if (fhss == FHSS_DISTRIBUTED_BLACKLIST_MAB_FIRST_GOOD_ARM)
                {
                    fhssSetMABThreshooldGoodArm(atoi(argv[13]));
                }
            }
        }
    }
    /* Use hard-coded parameters */
    else
    {
        alg = PROTOCOL;
        sink_id = SINK_NODE;
        channel = CHANNEL;
        export_mask_channels = EXPORT_MASK_CHANNELS;
        etx_threshold = ETX_THRESHOLD;
        strcpy(file_name, DATA_FILE);
        execute_sch = EXECUTE_SCHEDULE;
        if (execute_sch)
        {
            strcpy(links_prefix, LINKS_PREFIX);
            fhss = FHSS;
            pkt_prob = PKT_PROB;
        }
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
    createConflictMatrix(NULL, intMatrix, &nodesList, confMatrix, false);

    /* Create the distribution tree */
    Tree_t *tree; initializeTree(alg, &tree, &nodesList, sink_id, conMatrix, linksList, channel);

    /* Print network parameters */
    printNetworkParameters(tree, linksList, &nodesList, conMatrix, intMatrix, confMatrix, etxMatrix);

    /* Lets choose which protocol we want to work with */
    if (alg == MCC_ICRA)
    {
        main_mcc(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, NULL, false, false, true, channel, etx_threshold);
    }
    else if (alg == MCC_ICRA_NONOPTIMAL)
    {
        main_mcc(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, NULL, false, false, false, channel, etx_threshold);
    }
    else if (alg == MCC_CQAA)
    {
        main_mcc(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, etxMatrix, false, true, false, -1, etx_threshold);
    }
    else if (alg == MCC_CQARA)
    {
        main_mcc(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, etxMatrix, true, true, false, -1, etx_threshold);
    }
    else if (alg == TASA)
    {
        main_tasa(&nodesList, &linksList[channel], tree, sink_id, intMatrix, confMatrix, channel);
    }
    else if (alg == MODESA)
    {
        main_modesa(&nodesList, &linksList[channel], tree, sink_id, 1, intMatrix, confMatrix, channel);
    }

    /* Execute the schedule */
    if (execute_sch)
    {
        /* Initializing the RGN */
        time_t t;
        srand((unsigned) time(&t));

        /* Generate 'n_timeslots_per_file' random numbers to be used in the recpetion decision */
        List draws; memset(&draws, 0, sizeof(List)); ListInit(&draws);
        for (uint64_t i = 0; i < N_TIMESLOTS_PER_FILE*MAX_N_FILES; i++)
        {
            uint8_t sample = rand() % 100;
            ListAppend(&draws, (void *)sample);
        }

        /* Run each type of FHSS algorithm */
        if (fhss != FHSS_ALL)
        {
            execute_schedule(fhss, &draws, &nodesList, tree, sink_id, links_prefix, N_TIMESLOTS_PER_FILE, N_TIMESLOTS_LOG, pkt_prob);
        }
        else
        {
            for (uint8_t i = 0; i < FHSS_ALL; i++)
            {
                execute_schedule(i, &draws, &nodesList, tree, sink_id, links_prefix, N_TIMESLOTS_PER_FILE, N_TIMESLOTS_LOG, pkt_prob);
            }
        }
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

    if ((alg == TASA) || (alg == MODESA))
    {
        /* Opening file */
        res = openFile(&fp, TREE_FILE, "r");
        if (res != true) EXIT("Error while reading file %s", TREE_FILE);

        /* Create the connected tree */
        if (alg == TASA)
        {
            *tree = newTree(getNode(sink_id, nodesList), TASA_TREE);
        }
        else if (alg == MODESA)
        {
            *tree = newTree(getNode(sink_id, nodesList), MODESA_TREE);
        }

        if (!readFile(fp, nodesList, NULL, *tree, 100))
        {
            EXIT("It is impossible to create the tree from the given file.\n");
        }
        fclose(fp);
    }
    else if (alg == MCC_ICRA || alg == MCC_ICRA_NONOPTIMAL || alg == MCC_CQAA)
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




