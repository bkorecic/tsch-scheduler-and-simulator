#ifndef _GRAPH_COLORING_
#define _GRAPH_COLORING_

#include <stdbool.h>
#include "../graphs/graphs.h"

/* Parameters for weighting the tree formation in channel-aware allocation */

/* Parameters for weighting the channel allocation in channel-aware allocation */
#define THETA 1     /* For the subtree size  */
#define KAPPA 1     /* For the number of conflict nodes */
#define PHI 1       /* For the number of good channels */

/* Tree type */
typedef enum {
    RX_BASED,
    TX_BASED,
    LINK_BASED,
} CHANNEL_TYPE;

/**
 * \brief Creates the channel assignment for all the nodes in the nodesList.
 * \param nodesList List of nodes in the network.
 * \param confMatrix Conflict matrix.
 * \param cmst The CMS tree
 * \return Always true
 *
 * It assigns a different channel for all conflicting nodes, using degree-based greedy heuristic. After assigning
 * the channel to nodes, it converts the assignment to the corresponding time slots, according to the type of
 * channel assignment
 */
bool assignChannelNodes(List *nodesList, bool confMatrix[][MAX_NODES][NUM_CHANNELS], CHANNEL_TYPE type, Tree_t *cmst, int8_t channel);

bool assignChannelLinks(List *nodesList, float etxMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], Tree_t *cmst);

bool paintNodes(List *nodesSorted, bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel);

#endif // _GRAPH_COLORING_
