#ifndef _MODESA_
#define _MODESA_

#include <stdint.h>
#include "../graphs/graphs.h"

/**
 * \brief Forms the schedule considering modesa algorithm (greedy version).
 * \param nodesList List of nodes in the network.
 * \param linksList List of links in the network.
 * \param tree Distribution tree.
 * \param sink_id ID of the sink node.
 * \param sink_interfaces Number of interfaces of the sink node
 * \param intMatrix Interference matrix
 * \param confMatrix Conflicting matrix
 * \return Always true.
 *
 * Forms the schedule considering MODESA algorithm (greedy version), from paper "MODESA: an Optimal Multichannel
 * Slot Assignment for Raw Data Convergecast in Wireless Sensor Networks".
 */
bool main_modesa(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, uint8_t sink_interfaces, \
                bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel);

/**
 * \brief Forms the schedule considering modesa algorithm (MIP version).
 * \param nodesList List of nodes in the network.
 * \param tree Distribution tree.
 * \param sink_id ID of the sink node.
 * \param sink_interfaces Number of interfaces of the sink node.
 * \param confMatrix Conflicting matrix.
 * \return Always true.
 *
 * Forms the schedule considering MODESA algorithm (MIP version), from paper "MODESA: an Optimal Multichannel
 * Slot Assignment for Raw Data Convergecast in Wireless Sensor Networks".
 */
bool main_modesa_ip(List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t sink_interfaces, bool confMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel);

/**
 * \brief Creates the list N, with nodes having data to transmit and sorted according to their priority.
 * \param nodesList List of nodes in the network.
 * \param N Sorted list of nodes with data to transmit.
 *
 * Creates a list with all nodes that have data to transmit, sorted in non-increasing order of priority.
 */
void createListNodeWithData(List *nodesList, List *N);

/**
 * \brief Calculate the number of packets that need to be received by a given node (total traffic below a node).
 * \param node The node that will receive all packets.
 * \param tree The tree to be considered.
 *
 * Calculates the number of packets (total traffic) below a given node. This is used to calculate the priority of
 * a node in the tree.
 */
uint16_t calculateParentRcv(Node_t *node, Tree_t *tree);

/**
 * \brief Writes the LP file with the description of the MIP problem. The file is in CPLEX-LP format.
 * \param tree The tree to be considered.
 * \param nodesList List of nodes in the network
 * \param Vg List of gateway nodes (sink nodes)
 * \param Vs List of source nodes
 * \param linksList List of all links in the network
 * \param Tmax The maximum possible value for time slot
 *
 * Writes the file with a CPLEX-LP format describing the MIP problem, with the objective function, all constraints
 * and all variables types
 */
void writeLPFile(Tree_t *tree, List *nodesList, List *Vg, List *Vs, List *linksList, uint16_t Tmax);

#endif // _MODESA_
