#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printNetworkParameters(Tree_t *tree, List linksList[], List *nodeList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], \
                            bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], \
                            float etxMatrix[][MAX_NODES][NUM_CHANNELS]);
void printPrrMatrix(uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t n_nodes);
void output(uint8_t alg, List *nodesList, Tree_t *tree, char *tree_filename, bool export_mask_channels, bool use_eui64);

#endif // _PRINT_H_
