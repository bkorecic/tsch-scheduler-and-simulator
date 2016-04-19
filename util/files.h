#ifndef _FILES_H_
#define _FILES_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "../graphs/graphs.h"

/**
 * \brief Opens the file and checks for errors.
 * \param fp File pointer.
 * \param fileName File name.
 * \return true if successful; false otherwise
 *
 * Tries to open the file and checks for errors. If successful, the fp is set accordingly
 */
bool openFile(FILE **fp, char *fileName, char *mode);

/**
 * \brief Read the file with links description.
 * \param fp File pointer.
 * \param nodesList List of nodes
 * \param linksList List of links
 * \param maxPrr Maximum PRR value to be used for setting the correct ETX of each link
 * \return true if successful; false otherwise
 *
 * Opens a file with description of links. The file must have the number of nodes in the first line.
 * Followed by a square matrix in CSV format with all PRR for each link.
 */
bool readLinksFile(FILE *fp, List *nodesList, List *linksList, uint8_t maxPrr);

/**
 * \brief Read the file with network information.
 * \param fp File pointer.
 * \param nodesList List of nodes.
 * \param tree Pointer to the tree to be built.
 * \return true if successful; false otherwise
 *
 * Opens a file with description of the tree. The file must have the number of nodes in the first line.
 * Followed by the parent ID of each node per line.
 */
bool readFile(FILE *fp, List *nodesList, List linksList[], Tree_t *tree, uint8_t maxPrr);

/**
 * \brief Write the header file with the formed schedule.
 * \param fp File pointer.
 * \param nodesList List of nodes.
 * \param tree Pointer to the formed tree.
 * \param export_mask_channels Export a list of channel for FHSS instead of a single channel offset
 * \param use_eui64 Use the full 64-bit address in the line where neighbor is specified
 *
 * Writes the header with the formed schedule.
 */
void generateScheduleFileOpenWSN(FILE *fp, List *nodesList, Tree_t *tree, bool export_mask_channels, bool use_eui64);

void printBinary(FILE *fp, uint16_t number);

/**
 * \brief Write the c file with the formed topology.
 * \param fp File pointer.
 * \param nodesList List of nodes.
 * \param tree Pointer to the formed tree.
 *
 * Writes the c file with the topology. It is compatible with topology.c file used by OpenWSN.
 */
void generateTreeFileOpenWSN(FILE *fp, List *nodesList, Tree_t *tree);

/**
 * \brief Write the c file with the formed topology.
 * \param fp File pointer.
 * \param subtree Pointer to the subtree current being considered.
 * \param tree Pointer to the tree.
 *
 * Writes the c file with the topology to be used by any algorithm that do not calculate the distribution tree.
 * Initially both subtree and tree should point to the root of the tree to be considered.
 */
void generateTreeFile(FILE *fp, Tree_t *subtree, Tree_t *tree);

void printFile(char *filename, char *line);

#endif // _FILES_H_
