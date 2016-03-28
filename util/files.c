#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "debug.h"
#include "defs.h"
#include "../graphs/graphs.h"
#include "../schedule/fhss.h"

#define MAX_LINE_SIZE 1024

bool openFile(FILE **fp, char *fileName, char *mode)
{
    /* Open the desired file in Read-Only mode*/
    *fp = fopen(fileName, mode);

    if (*fp != NULL)
    {
        /* Success! */
        return (true);
    }
    else
    {
        /* Failure! */
        return (false);
    }
}

bool readFileLinks(FILE *fp, List *nodesList, List linksList[], uint8_t maxPrr)
{
    uint16_t n_nodes = ListLength(nodesList);
    char line[MAX_LINE_SIZE];
    uint8_t id_node;
    char *token = NULL;
    Node_t *node;

    uint16_t i = 0, j = 0;
    while(fgets(line, sizeof(line),fp) != NULL)
    {
        i++;
        switch (line[0])
        {
            /* This part is executed if we are reading information of link quality */
            case 'l':

                /* Get the initial token */
                token = strtok(line, ",");
                token++;

                /* Get the node ID */
                id_node = atoi(token);
                node = getNode(id_node, nodesList);

                /* Get the channel */
                token = strtok(NULL, "=");
                uint8_t ch = atoi(token);

                /* Get all link information */
                token = strtok(NULL, ",");
                j = 0;
                while(token != NULL)
                {
                    float prr, etx;

                    /* Scan the floating number corresponding to the PRR and calculate the ETX */
                    prr = strtof(token,NULL);
                    prr /= (float)maxPrr; /* Calculating the PRR in percentage */
                    etx = 1.0/prr;

                    PRINTF("Link %d->%d Ch %d PRR %f ETX %f\n", node->id, j, ch, prr, etx);

                    /* Create a new Link object */
                    if (prr != 0.0)
                    {
                        Link_t *link = newLink(node, getNode(j,nodesList), 1.0/prr, ch, UNIDIRECTIONAL, 0);
                        ListAppend(&linksList[ch], (void*)link);
                    }

                    j++;
                    token = strtok(NULL, ",");
                }
                if (j < n_nodes) ERROR_RET("Line %d has less fields than expected", i);

                break;
            default:
                break;
        }
    }

    return (true);
}

bool readFile(FILE *fp, List *nodesList, List *linksList, Tree_t *tree, uint8_t maxPrr)
{
    char line[MAX_LINE_SIZE];
    uint16_t n_nodes = 0;
    char *token = NULL;
    int id_node, id_parent;
    Node_t *node, *parent;

    uint16_t i = 0, j = 0;
    while(fgets(line, sizeof(line),fp) != NULL)
    {
        i++;
        switch (line[0])
        {
            /* This part is executed if we are reading information of parents (for tree formation) */
            case 'p':

                /* Get the initial token */
                token = strtok(line, "=");
                token++;

                /* Get the node ID */
                id_node = atoi(token);
                node = getNode(id_node, nodesList);

                /* Get the parents ID */
                token = strtok(NULL, "=");
                id_parent = atoi(token);

                if (id_parent >= 0)
                {
                    parent = getNode(id_parent, nodesList);

                    /* Connect the node to its parent */
                    if (!connectToTree(node, parent, tree))
                    {
                        ERROR_RET("Error while creating tree.\n");
                    }
                    else
                    {
                        node->type = parent->type = CONNECTED;
                    }
                }
                break;

            /* This part is executed if we are reading information about number of nodes */
            case 'n':

                /* Get the initial token */
                token = strtok(line, "=");

                /* Get the number of nodes */
                token = strtok(NULL, "=");
                n_nodes = atoi(token);

                /* Create the list of nodes */
                for(uint8_t k=0; k<n_nodes; k++)
                {
                    Node_t *n = newNode(k, DISCONNECTED);
                    ListAppend(nodesList, (void *)n);
                }
                break;

            /* This part is executed if we are reading the queue information */
            case 'q':

                /* Get the initial token */
                token = strtok(line, "=");
                token++;

                /* Get the node ID */
                id_node = atoi(token);
                node = getNode(id_node, nodesList);

                /* Get queue information */
                token = strtok(NULL, "=");
                int q = atoi(token);

                /* Set the value on q variable */
                node->q = q;

                break;

            /* This part is executed if we are reading information of link quality */
            case 'l':

                /* Get the initial token */
                token = strtok(line, ",");
                token++;

                /* Get the node ID */
                id_node = atoi(token);
                node = getNode(id_node, nodesList);

                /* Get the channel */
                token = strtok(NULL, "=");
                uint8_t ch = atoi(token);

                /* Get all link information */
                token = strtok(NULL, ",");
                j = 0;
                while(token != NULL)
                {
                    float prr, etx;

                    /* Scan the floating number corresponding to the PRR and calculate the ETX */
                    prr = strtof(token,NULL);
                    prr /= (float)maxPrr; /* Calculating the PRR in percentage */
                    etx = 1.0/prr;

                    PRINTF("Link %d->%d Ch %d PRR %f ETX %f\n", node->id, j, ch, prr, etx);

                    /* Create a new Link object */
                    if (prr != 0.0)
                    {
                        Link_t *link = newLink(node, getNode(j,nodesList), 1.0/prr, ch, UNIDIRECTIONAL, 0);
                        ListAppend(&linksList[ch], (void*)link);
                    }

                    j++;
                    token = strtok(NULL, ",");
                }
                if (j < n_nodes) ERROR_RET("Line %d has less fields than expected", i);

                break;

            /* This part is executed if we are reading information of address */
            case 'a':

                /* Get the initial token */
                token = strtok(line, "=");
                token++;

                /* Get the node ID */
                id_node = atoi(token);
                node = getNode(id_node, nodesList);

                /* Get address */
                token = strtok(NULL, "=");
                uint64_t addr = strtoul(token, NULL, 16);

                /* Set the value on q variable */
                node->eui64 = addr;

                break;

            default:

                break;
        }
    }

    return (true);
}

bool readLinksFile(FILE *fp, List *nodesList, List *linksList, uint8_t maxPrr)
{
    char line[MAX_LINE_SIZE];
    uint16_t n_nodes = 0;
    char *token = NULL;
    int id_node;
    Node_t *node;

    uint16_t i = 0, j = 0;
    while(fgets(line, sizeof(line),fp) != NULL)
    {
        i++;
        switch (line[0])
        {
            /* This part is executed if we are reading information of link quality */
            case 'l':

                /* Get the initial token */
                token = strtok(line, ",");
                token++;

                /* Get the node ID */
                id_node = atoi(token);
                node = getNode(id_node, nodesList);

                /* Get the channel */
                token = strtok(NULL, "=");
                uint8_t ch = atoi(token);

                /* Get all link information */
                token = strtok(NULL, ",");
                j = 0;
                while(token != NULL)
                {
                    float prr, etx;

                    /* Scan the floating number corresponding to the PRR and calculate the ETX */
                    prr = strtof(token,NULL);
                    prr /= (float)maxPrr; /* Calculating the PRR in percentage */
                    etx = 1.0/prr;

                    PRINTF("Link %d->%d Ch %d PRR %f ETX %f\n", node->id, j, ch, prr, etx);

                    /* Create a new Link object */
                    if (prr != 0.0)
                    {
                        Link_t *link = newLink(node, getNode(j,nodesList), 1.0/prr, ch, UNIDIRECTIONAL, 0);
                        ListAppend(&linksList[ch], (void*)link);
                    }

                    j++;
                    token = strtok(NULL, ",");
                }
                if (j < n_nodes) ERROR_RET("Line %d has less fields than expected", i);

                break;

            default:

                break;
        }
    }

    return (true);
}

void generateScheduleFileOpenWSN(FILE *fp, List *nodesList, Tree_t *tree, bool export_mask_channels, bool use_eui64)
{
    uint8_t n_nodes = ListLength(nodesList);
    uint8_t max_freq = 0;

    /* Calculate the slot_frame size */
    uint8_t superframe_length = 0;
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        Node_t *node = (Node_t *)elem->obj;
        if (ListLength(&node->timeslots) > superframe_length)   /* We start the timeslots in zero */
        {
            superframe_length = ListLength(&node->timeslots);
        }
    }

    fprintf(fp, "#include \"opendefs.h\"\n");
    fprintf(fp, "#include \"schedule.h\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "void getExtSchedule(uint16_t addr, uint8_t timeslot_offset, extScheduleEntry_t *extScheduleEntry)\n{");
    fprintf(fp, "\n");
    fprintf(fp, "   switch (addr) {\n");

    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* For each node */
        Node_t *node = (Node_t *)elem->obj;

        fprintf(fp, "      case 0x%04x:\n", (unsigned int)(node->eui64 & 0x000000000000ffff));

        fprintf(fp, "         switch(timeslot_offset) {\n");

        /* Traffic time slots */
        for (uint16_t j = 1; j <= superframe_length; j++)
        {
            fprintf(fp, "            case %d:\n", j-1);
            TimeSlot_t *ts;

            if ((ts = getTimeSlot(j, &node->timeslots)) != NULL)
            {
                if (ts->type == TS_RX)
                {
                    /* Type */
                    fprintf(fp, "               extScheduleEntry->type = CELLTYPE_RX;\n");
                    /* Channel offset */
                    if (export_mask_channels)
                    {
                        Node_t *node_with_channels = node;
                        uint16_t mask_channels = create_mask_channels(node_with_channels);
                        fprintf(fp, "               extScheduleEntry->channelMask = %d;   // 0b", mask_channels);
                        print_binary(fp, mask_channels);
                        fprintf(fp, "\n");
                    }
                    else
                    {
                        fprintf(fp, "               extScheduleEntry->channelMask = %d;\n", ts->freq);
                    }
                    /* Neighbor */
                    if (use_eui64)
                    {
                        fprintf(fp, "               extScheduleEntry->neighbor = 0x%02x%02x%02x%02x%02x%02x%02x%02x;\n", \
                                    (unsigned int)((ts->neighbor->eui64 & 0x00000000000000ff) >> 0), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x000000000000ff00) >> 8), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x0000000000ff0000) >> 16), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x00000000ff000000) >> 24), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x000000ff00000000) >> 32), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x0000ff0000000000) >> 40), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x00ff000000000000) >> 48), \
                                    (unsigned int)((ts->neighbor->eui64 & 0xff00000000000000) >> 56));
                    }
                    else
                    {
                        fprintf(fp, "               extScheduleEntry->neighbor = 0x%04x;\n", (unsigned int)(ts->neighbor->eui64 & 0x000000000000ffff));
                    }
                }
                else if (ts->type == TS_TX)
                {
                    /* Type */
                    fprintf(fp, "               extScheduleEntry->type = CELLTYPE_TX;\n");
                    /* Channel offset */
                    if (export_mask_channels)
                    {
                        Node_t *node_with_channels = getParent(tree, node);
                        uint16_t mask_channels = create_mask_channels(node_with_channels);
                        fprintf(fp, "               extScheduleEntry->channelMask = %d;   // 0b", mask_channels);
                        print_binary(fp, mask_channels);
                        fprintf(fp, "\n");
                    }
                    else
                    {
                        fprintf(fp, "               extScheduleEntry->channelMask = %d;\n", ts->freq);
                    }
                    /* Neighbor */
                    if (use_eui64)
                    {
                        fprintf(fp, "               extScheduleEntry->neighbor = 0x%02x%02x%02x%02x%02x%02x%02x%02x;\n", \
                                    (unsigned int)((ts->neighbor->eui64 & 0x00000000000000ff) >> 0), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x000000000000ff00) >> 8), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x0000000000ff0000) >> 16), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x00000000ff000000) >> 24), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x000000ff00000000) >> 32), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x0000ff0000000000) >> 40), \
                                    (unsigned int)((ts->neighbor->eui64 & 0x00ff000000000000) >> 48), \
                                    (unsigned int)((ts->neighbor->eui64 & 0xff00000000000000) >> 56));
                    }
                    else
                    {
                        fprintf(fp, "               extScheduleEntry->neighbor = 0x%04x;\n", (unsigned int)(ts->neighbor->eui64 & 0x000000000000ffff));
                    }
                }
                else
                {
                    ERROR("Invalid time slot\n");
                }

                if (ts->freq > max_freq)
                {
                    max_freq = ts->freq;
                }
            }
            else
            {
                fprintf(fp, "               extScheduleEntry->type = CELLTYPE_OFF;\n");
                if (export_mask_channels)
                {
                    fprintf(fp, "               extScheduleEntry->channelMask = 0;\n");
                }
                else
                {
                    fprintf(fp, "               extScheduleEntry->channelMask = 0;\n");
                }
                fprintf(fp, "               extScheduleEntry->neighbor = 0;\n");
            }
            fprintf(fp, "               break;\n");
        }

        fprintf(fp, "            default:\n");
        fprintf(fp, "               break;\n");
        fprintf(fp, "         }\n");
        fprintf(fp, "         break;\n");
    }

    fprintf(fp, "      default:\n");
    fprintf(fp, "         break;\n");
    fprintf(fp, "   }\n");
    fprintf(fp, "}\n");
    //fprintf(fp,"#endif");

    fprintf(stdout, "SF = %d\n", superframe_length);
    fprintf(stdout, "CH = %d\n", max_freq);
}

void print_binary(FILE *fp, uint16_t number)
{
    for (int8_t i = 15; i >= 0; i--)
    {
        fprintf(fp, "%c", number & (1 << i) ? '1' : '0');
    }
}

void generateTreeFileOpenWSN(FILE *fp, List *nodesList, Tree_t *tree)
{
    fprintf(fp, "#include \"opendefs.h\"\n");
    fprintf(fp, "#include \"topology.h\"\n");
    fprintf(fp, "#include \"idmanager.h\"\n\n");

    fprintf(fp, "bool topology_isAcceptablePacket(uint16_t shortID) {\n");
    fprintf(fp, "#ifdef FORCETOPOLOGY\n");
    fprintf(fp, "   bool returnVal;\n");
    fprintf(fp, "   \n");
    fprintf(fp, "   returnVal=FALSE;\n");
    fprintf(fp, "   switch (idmanager_getMyShortID()) {\n");

    for (ListElem *elem1 = ListFirst(nodesList); elem1 != NULL; elem1 = ListNext(nodesList, elem1))
    {
        Node_t *node = (Node_t *)elem1->obj;

        fprintf(fp, "      case 0x%04x:\n", (unsigned int)(node->eui64 & 0x000000000000ffff));
        fprintf(fp, "         if (\n");

        /* The parent */
        Node_t *parent = getParent(tree, node);
        bool flag_parent = false;
        if (parent != NULL)
        {
            fprintf(fp, "            shortID==0x%04x", (unsigned int)(parent->eui64 & 0x000000000000ffff));
            flag_parent = true;
        }

        /* All the children */
        Tree_t *subTree = getSubTree(tree, node);
        bool flag_children = false;
        for (ListElem *elem2 = ListFirst(&subTree->subtrees_list); elem2 != NULL; elem2 = ListNext(&subTree->subtrees_list, elem2))
        {
            Tree_t *child_subtree = (Tree_t *)elem2->obj;
            if (flag_parent || flag_children)
            {
                fprintf(fp, "||\n");
                flag_parent = false;
            }
            fprintf(fp, "            shortID==0x%04x", (unsigned int)(child_subtree->root->eui64 & 0x000000000000ffff));

            flag_children = true;
        }

        fprintf(fp, "\n");
        fprintf(fp, "         ) {\n");
        fprintf(fp, "         returnVal=TRUE;\n");
        fprintf(fp, "      }\n");
        fprintf(fp, "      break;\n");
    }

    fprintf(fp, "   }\n");
    fprintf(fp, "   return returnVal;\n");
    fprintf(fp, "#else\n");
    fprintf(fp, "   return TRUE;\n");
    fprintf(fp, "#endif\n");
    fprintf(fp, "}\n");
}

void generateTreeFile(FILE *fp, Tree_t *subtree, Tree_t *tree)
{
    Node_t *node = subtree->root;
    Node_t *parent = getParent(tree, node);

    /* Printing the number of nodes */
    fprintf(fp, "p%d=%d", node->id, (parent != NULL)?parent->id:-1);
    if (node->worst_prr > 0)
    {
        fprintf(fp, "=%d", node->worst_prr);
    }
    fprintf(fp, "\n");

    for (ListElem *elem = ListFirst(&subtree->subtrees_list); elem != NULL; elem = ListNext(&subtree->subtrees_list, elem))
    {
        Tree_t *t = (Tree_t *)elem->obj;
        generateTreeFile(fp, t, tree);
    }
}
