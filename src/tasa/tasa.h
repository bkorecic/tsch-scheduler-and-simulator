#ifndef _TASA_
#define _TASA_

#include <stdint.h>
#include "../graphs/graphs.h"

/**
 * \brief Forms the schedule considering TASA algorithm.
 * \param nodesList List of nodes in the network.
 * \param linksList List of links in the network.
 * \param tree Distribution tree.
 * \param sink_id ID of the sink node.
 * \param intMatrix Interference matrix.
 * \param confMatrix Conflicting matrix.
 * \return Always true.
 *
 * Forms the schedule considering TASA algorithm, from paper "On Optimal Scheduling in Duty-Cycled
 * Industrial IoT Applications Using IEEE 802.15.4e TSCH".
 */
bool main_tasa(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id,
               bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel);

/**
 * \brief Calculate the global Q under 'node' at time slot k.
 * \param node Pointer to the node under which we want to calculate the Q.
 * \param k The current time slot.
 * \param q Matrix with q values (local queue).
 * \param tree Pointer to the network tree
 * \return The Q value of 'node' at time slot k.
 *
 * Calculate the value of global queue (sum of all local queues 'q' under a node) for 'node' at time slot k.
 */
uint16_t calculateQ(Node_t *node, uint16_t k, uint16_t q[][MAX_TIMESLOTS], Tree_t *tree);

#endif // _TASA_
