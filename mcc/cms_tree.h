#ifndef _CMS_TREE_
#define _CMS_TREE_

#include "../graphs/graphs.h"

#define ALPHA 1
#define ZETA 1
#define BETA 1

/**
 * \brief Construct the Constrained Minimum Spanning Tree for a single channel (channel 0).
 * \param sink Sink node of the tree.
 * \param nodesList List of all nodes in the network.
 * \param conMatrix Connectivity matrix of the network
 * \return The CMS tree
 *
 * This function implements Algorithm 4 of paper "Fast Data Collection in Tree-Based Wireless Sensor Netwoks"
 */
Tree_t *constructCMSTreeSingleChannel(Node_t *sink, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t channel);

/**
 * \brief Construct the Constrained Minimum Spanning Tree for multiple channels.
 * \param sink Sink node of the tree.
 * \param nodesList List of all nodes in the network.
 * \param conMatrix Connectivity matrix of the network
 * \param linksList
 * \return The CMS tree
 *
 * This function implements Algorithm 4 of Ying Chen's PhD thesis
 */
Tree_t *constructCMSTreeMultipleChannel(Node_t *sink, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[]);

/**
 * \brief Calculate the hop count, candidate parents and candidate children of every node
 * \param sink Sink node of the network.
 * \param nodesList List of all nodes in the network.
 * \param conMatrix Connectivity matrix of the network
 *
 * Algorithm calculates the hop count and all candidate parents and candidate children of every node.
 * The information is updated using the nodesList
 */
void constructHopCountParentsAndChildren(Node_t *sink, List *nodesList, bool conMatrix[][MAX_NODES][NUM_CHANNELS], int8_t channel);

/**
 * \brief Construct the initial growth set (GS) for all nodes in the network.
 * \param cmst CMS tree with at least the sink node.
 * \param nodesList List of all nodes in the network.
 * \param conMatrix Connectivity matrix of the network
 *
 * Algorithm calculates the growth set (set of all unconnected neighbors at higher hop counts) for every node
 * in the network. The information (GS) is updated using the nodeList
 */
void constructGS(Tree_t *cmst, List *nodesList, bool conMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS], int8_t channel);

/**
 * \brief Updates the growth set (GS) of a particular node.
 * \param node Node that need to be updated.
 * \param cmst CMS tree with at least the sink node.
 * \param nodesList List of all nodes in the network.
 * \param conMatrix Connectivity matrix of the network
 *
 * Algorithm calculates the growth set (set of all unconnected neighbors at higher hop counts) of a particular node
 * in the network.
 */
void updateGS(Tree_t *cmst, Node_t *node, List *nodesList, bool conMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS], int8_t channel);

/**
 * \brief Looks for all the branches to which a node is connect.
 * \param node Node that need to be connected.
 * \param branches Array of branches that need to be considered.
 * \param size Size of the array of branches.
 * \param avoidNode Node that should be avoid when trying to connect the node.
 * \return The list of all branches.
 *
 * Algorithm returns a list of all branches to which a particular node is connected to.
 */
List *branchesNodeIsConnectTo(Node_t *node, Tree_t *branches[], uint8_t size, Node_t *avoidNode);

/**
 * \brief Created the set of search nodes for a particular node and a particular branch.
 * \param node Node for which we are creating the SS (search set).
 * \param branch Branch to which we are creating the SS.
 * \param nodesList List of nodes in the network.
 * \param branches Array with all branches in the network
 * \param size Size of the branches array
 * \return List of all nodes in the SS
 *
 * Algorithm looks for all nodes that are part of SS(node,branch). A node is part of search set SS(node,branch)
 * if it cannot eventually be connected to another branch if 'node' is connected to 'branch'. This means that,
 * if 'node' is connected to 'branch' all nodes in SS(node,branch) will necessarily be added to that branch.
 */
List *createSS(Node_t *node, Tree_t *branch, List *nodesList, Tree_t *branches[], int size);

/**
 * \brief Sort the list in non increasing order of size of GS (growth set).
 * \param unsorted Unsorted list.
 * \param sorted Sorted list to be changed.
 *
 * Sorts the unsorted list in non-increasing order of |GS|, size of the set GS and outputs the result
 * in the sorted list.
 */
void sortListNonIncreasingByGS(List *unsorted, List *sorted);

/**
 * \brief Created a new tree, with 'root' node and all possible children.
 * \param root The root node in the new tree.
 * \param nodesList List of nodes in the network.
 * \return The new tree.
 *
 * Creates a new tree with 'root' node as root and considering all possible candidate children.
 */
Tree_t *createTree(Node_t *root, List *nodesList);

/**
 * \brief Remove all connections (candidate children and candidate parents) from other nodes in the tree, except for the parent
 * \param node The node to which all connections should be removed
 * \param tree The tree of nodes
 * \param parent The real parent, that should be maintained
 * \return always true
 *
 * Visit all nodes in the tree and remove any parent-child relationship between 'node' and any other node in the network,
 * except for the real 'parent'
 */
int disconnectOtherParents(Node_t *node, Tree_t *tree, Node_t *parent);

/**
 * \brief Connect node to the parent with maximum variety (number of good channels)
 * \param node The node that will be connected
 * \param cmst The tree of nodes
 * \param conMatrix The connectivity matrix
 *
 *
 */
void connectToParentMaxChannelVar(Node_t *node, Tree_t *cmst, bool conMatrix[][MAX_NODES][NUM_CHANNELS]);

/**
 * \brief Calculate the channel variety between node and parent
 * \param node The node to be considered
 * \param parent The parent to be considered
 * \param conMatrix The connectivity matrix
 * \return The channel variety (number of good channels)
 *
 */
uint8_t calculateChannelVar(Node_t *node, Node_t *parent, bool conMatrix[][MAX_NODES][NUM_CHANNELS]);


void checkAllNodesHaveParents(List *nodesList);

#endif // _CMS_TREE_
