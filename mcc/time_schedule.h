#ifndef _TIME_SCHEDULE_
#define _TIME_SCHEDULE_

#include "../util/list.h"
#include "../graphs/graphs.h"

typedef struct action_t {
	uint8_t	branch;
	uint8_t	hop;
} Action_t;

/**
 * \brief Creates a action.
 * \param branch The index of the branch in the list of subtrees in cmst.
 * \param hop The hop count of the transmission
 * \return Pointer to the new action created.
 *
 * It creates a new action, which represents the distribution of a packet from the sink to a specific node.
 * The branch and the hop of this node are specified.
 */
Action_t *newAction(uint8_t branch, uint8_t hop);

/**
 * \brief Finds the list of nodes at a certain hop distance in a particular tree.
 * \param nodesList List of nodes in the network.
 * \param tree The tree that node should belong to.
 * \return hopCount The hop count distance.
 *
 * It searches for all the nodes and check which ones are at the correct hop distance and belong to the correct
 * tree
 */
List *nodesWithHopCount (List *nodesList, Tree_t *tree, uint8_t hopCount);

/**
 * \brief Creates a line tree from a regular tree.
 * \param nodesList List of the nodes in the network.
 * \param tree Tree that should be converted to a line tree
 * \return Pointer to the new newl created line tree.
 *
 * The algorithm creates a line tree from a regular tree. A line tree consists of a lines of nodes. At each hop
 * distance in the line of nodes we have a list of nodes that are located at that distance in the original regular tree
 */
LineTree_t *createLineTree (List *nodesList, Tree_t *tree);

/**
 * \brief Creates the time schedule for collection problem.
 * \param cmst The CMS tree to be considered
 * \param nodesList List of the nodes in the network.
 * \return Always true
 *
 * Creates the collection time schedule from the CMS tree provided. The schedule will be stored in each node in the
 * nodesList.
 */
bool createOptimalTimeSlotSchedule(Tree_t *cmst, List *nodesList, bool optimal_sched);

bool changeScheduleToNonOptimal(Tree_t *cmst, List *nodesList);

/**
 * \brief Convert the actions created by the distribution algorithm into real time slots.
 * \param actionsList List of actions.
 * \param multiLineNetwork Line network to be considered.
 * \param cmst The CMS tree to be considered.
 * \return Always true
 *
 * Convert the time slot of the distribution problem to the time slots of the collection problem.
 */
bool actionsToTimeSlots(List *actionsList, LineTree_t *multiLineNetwork[], Tree_t *cmst);

/**
 * \brief Convert the time slot of the distribution problem to the time slots of the collection problem.
 * \param nodesList List of the nodes in the network.
 * \param max_time Maximum time slot of all nodes
 * \return Always true
 *
 * Convert the time slot of the distribution problem to the time slots of the collection problem.
 */
bool distributionToCollection(List *nodesList, uint16_t max_time);

/**
 * \brief Maximum time slot of all nodes
 * \param nodesList List of the nodes in the network.
 *
 * Returns the maximum time slot of all nodes
 */
uint16_t maxTimeSlot (List *nodesList);

/**
 * \brief Prints all time slots of nodes in the list
 * \param nodesList List of the nodes in the network.
 *
 * Prints all time slots
 */
void printTimeSlots(List *nodesList);

/**
 * \brief Check if both nodes share any time slot.
 * \param node_i Node 1
 * \param node_j Node 2
 * \return true if both nodes share at least one time slot; false otherwise
 *
 * Check if the nodes share at least one time slot and return the result.
 */
bool shareTimeSlots(Tree_t *tree, Node_t *node_i, Node_t *node_j);

#endif // _TIME_SCHEDULE_
