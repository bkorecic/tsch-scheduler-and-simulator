#ifndef _MCC_
#define _MCC_

#include "../util/list.h"
#include "../graphs/graphs.h"

/**
 * \brief Forms the schedule considering MCC algorithm.
 * \param nodesList List of nodes in the network.
 * \param linksList List of links in the network.
 * \param tree Distribution tree.
 * \param sink_id ID of the sink node
 * \param intMatrix Interference matrix
 * \param confMatrix Conflicting matrix
 * \param ca_routing Determines if Channel-Aware Routing will be performed
 * \param ca_allocation Determines if Channel-Aware Allocation will be performed
 * \return Always true.
 *
 * Forms the schedule considering MCC algorithm, from paper "Multi-Channel Data Collection for Throughput
 * Maximization in Wireless Sensor Networks".
 */
int main_mcc(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, \
             bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], float prrMatrix[][MAX_NODES][NUM_CHANNELS],\
             bool ca_routing, bool ca_allocation, int8_t channel);

#endif // _MCC_
