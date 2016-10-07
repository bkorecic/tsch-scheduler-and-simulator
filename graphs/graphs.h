#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <stdint.h>
#include <stdbool.h>

#include "../util/list.h"
#include "../util/defs.h"

#define MAX_NODES 50
#define MAX_HOP_COUNT MAX_NODES
#define MAX_TIMESLOTS 256
#define MAX_PKT_RETRIES 3
#define NODE_QUEUE_SIZE 10

#define NUM_CHANNELS 16

typedef enum {
	SINK,
	RELAY,
	LEAF,
	CONNECTED,
	DISCONNECTED
} NODE_TYPE;

typedef enum {
	UNIDIRECTIONAL,
	BIDIRECTIONAL,
} LINK_TYPE;

typedef enum {
    TOP_BRANCH,
    BRANCH,
    CMS,
    TASA_TREE,
    MODESA_TREE,
} TREE_TYPE;

typedef enum {
    TS_TX,
    TS_RX,
    TS_IDLE,
    TS_SHARED,
    TS_BEACON,
} TIMESLOT_TYPE;

typedef struct node_t {
	uint16_t 	id;                 /* Node ID */
	uint64_t    eui64;              /* IPv6 address */
	NODE_TYPE	type;               /* Type of node */
	uint8_t     q;                  /* Queue (number of packets) */
	uint16_t    cur_dsn;            /* Current Data Sequence Number */
	List        packets;            /* List of packets */
	List        timeslots;          /* List of timeslots */

/* MCC code */
    List        channels;
    int8_t      hop_count;          /* Hop count to sink */
    List        candidate_parents;  /* List of candidate parents */
    List        candidate_children; /* List of candidate children */
    List        gs;                 /* Growth set */
    uint8_t     degree;
/* MCC code */

/* MODESA code */
    uint16_t    priority;           /* Priority for schedule purpose */
    uint8_t     interfaces;         /* Number of interfaces */
/* MODESA code */

/* MODESA IP code */
    List        links_tx;           /* Links used for TX */
    List        links_rx;           /* Links used for RX */
    List        nodes_int;          /* Interfering nodes */
/* MODESA IP code */

/* Schedule */
    uint32_t    pkt_tx_success;
    uint32_t    pkt_tx_failed;
    uint32_t    pkt_rx_success;
    uint32_t    pkt_rx_failed;
/* Schedule */

/* Blacklist */
    uint8_t     avg_reward[MAX_NODES][NUM_CHANNELS];
    uint32_t    cumulative_regret;
    uint8_t     optimal_freq;
    uint32_t    n_pull;
    uint32_t    n_optimal_pull;
/* Blacklist */

/* RPL */
    uint16_t       dagRank;
    bool        synced;
    uint64_t    nextAsnToTxDIO;     /* Next ASN to transmit a DIO message */
    uint64_t    nextAsnToTxKA;      /* Next ASN to transmit a Keep Alive message */
/* RPL */

} Node_t;

typedef struct link_t {
	Node_t      *n1;
	Node_t      *n2;
	uint16_t	weight;
	float		etx;
	float		lqi;
	float		rssi;
	uint8_t     channel;
/* MODESA IP code */
	uint8_t     id;
/* MODESA IP code */
	LINK_TYPE	type;
} Link_t;

typedef struct tree_t {
    Node_t      *root;
    uint16_t    weight;
    List        children_list;  /* List of children nodes */
    List        subtrees_list;  /* List of Tree_t * to the subtrees */
    TREE_TYPE   type;
/* TASA code */
    bool        valid;
/* TASA code */
} Tree_t;

typedef struct linetree_t {
    uint8_t             hop;
    List                *nodes;
    struct linetree_t   *nextTree;
/* MCC code */
    bool                legal;
    bool                prev_legal;
    uint16_t            pkts_left;
    uint16_t            est_trans_time;
    uint16_t            time_to_be_legal;
/* MCC code */
} LineTree_t;

typedef struct timeslot_t {
    uint16_t        time;
    uint8_t         freq;
    bool            relay;
    Node_t          *neighbor;
    TIMESLOT_TYPE   type;
} TimeSlot_t;

typedef struct packet_t {
    uint16_t        dsn;
    uint16_t        src_id;
    uint8_t         n_retries;          /* Current number of transmission retries */
    uint8_t         n_transmissions;    /* Number of times the packet was transmitted (or re-transmitted) */
    uint8_t         n_hops;             /* Number of hops the packet passed thru */
} Packet_t;

/**
 * \brief Creates a new link.
 * \param n1 Node 1 on the link.
 * \param n2 Node 2 on the link
 * \param etx ETX of the link.
 * \param ch Channel of the links
 * \param type Type of the link.
 * \param link_id Unique ID (optional)
 * \return Pointer to the new link created.
 *
 * Allocates memory and creates a new object of Link_t type.
 */
Link_t *newLink(Node_t *n1, Node_t *n2, float etx, uint8_t ch, LINK_TYPE type, uint8_t link_id);

/**
 * \brief Creates a new node.
 * \param id Node ID.
 * \param type Type of the link.
 * \return Pointer to the new node created.
 *
 * Allocates memory and creates a new object of Node_t type.
 */
Node_t *newNode(uint16_t id, NODE_TYPE type);

/**
 * \brief Creates a new tree.
 * \param root Root node of the tree.
 * \param type Type of the tree.
 * \return Pointer to the new tree created.
 *
 * Allocates memory and creates a new object of Tree_t type
 */
Tree_t *newTree(Node_t *root, TREE_TYPE type);

/**
 * \brief Creates a new line tree.
 * \param hop_count The hop count of the current root.
 * \return Pointer to the new line tree created.
 *
 * Allocates memory and creates a new object of LineTree_t type
 */
LineTree_t *newLineTree(uint8_t hop_count);

/**
 * \brief Creates a new time slot.
 * \param time Time.
 * \param freq Frequency (channel)
 * \param type Type.
 * \param relay Flag saying if this timeslot is for a packet relaying
 * \return Pointer to the new time slot created.
 *
 * Allocates memory and creates a new object of TimeSlot_t type
 */
TimeSlot_t *newTimeSlot(uint16_t time, uint8_t freq, TIMESLOT_TYPE type, Node_t *neighbor, bool relay);

Packet_t *newPacket(uint16_t dsn, uint16_t src_id);

/**
 * \brief Checks if the node is in a particular tree, avoiding a specific root node.
 * \param node Node to be found in the tree.
 * \param tree Tree to be traversed.
 * \param avoidRoot This root shoul be avoided. If it is found the search downsward should quit.
 * \return true if found; false otherwise
 *
 * The search starts from the tree's root and goes recursively scanning for the the node.
 * If a tree root equals to avoidRoot is found the search stops on that branch. If this 'avoid' functionality
 * is not needed, you can input avoidRoot as NULL
 */
bool isNodeInTree(Node_t *node, Tree_t *tree, Node_t *avoidRoot);

/**
 * \brief Connects the node to the tree under a specific parent.
 * \param new_node New node to the connected to the tree.
 * \param parent Parent that should be used for connecting the node.
 * \param tree Tree that should be used.
 * \return true if successful; false otherwise.
 *
 * The algorithms looks for the parent in the tree and connects the new_node under the parent. It adjusts the weight
 * of the nodes in the tree.
 */
bool connectToTree(Node_t *new_node, Node_t *parent, Tree_t *tree);

/**
 * \brief Connects the node to the tree under any one of node's candidates parents.
 * \param new_node New node to the connected to the tree.
 * \param tree Tree that should be used.
 * \return The parent that the node was connected to; NULL if no parent was found.
 *
 * The algorithms looks for any one of the node's candidates parents in the tree. If any candidate parent is found, the node
 * gets connected and the considered parent is returned.
 */
Node_t *connectToTreeAnyParent(Node_t *new_node, Tree_t *tree);

/**
 * \brief Prints a tree.
 * \param tree Tree to the printed.
 *
 * Prints the tree in human-readable format
 */
void printTree(Tree_t *tree);

/**
 * \brief Prints a line tree.
 * \param lineTree Line Tree to the printed.
 *
 * Prints the line tree in human-readable format
 */
void printLineTree(LineTree_t *lineTree);

/**
 * \brief Prints a list of nodes.
 * \param nodesList List of nodes to the printed.
 *
 * Prints the list of nodes in human-readable format
 */
void printListNodes(List *nodesList);

/**
 * \brief Prints a list of links.
 * \param linksList List of links to the printed.
 *
 * Prints the list of links in human-readable format
 */
void printListLinks(List *linksList);

/**
 * \brief Return the tree with root's id 'root_id' in the list 'treesList'
 * \param root_id ID of the tree's root to be returned.
 * \param treesList Pointer to the list of trees
 * \return Tree if found; NULL otherwise.
 *
 * Traverses the list and return the tree if it was found.
 */
Tree_t *getTree(uint16_t root_id, List *treesList);

/**
 * \brief Return the node with id 'node_id' in the list 'nodesList'
 * \param node_id ID of the node to be returned.
 * \param nodesList Pointer to the list of nodes
 * \return Node if found; NULL otherwise.
 *
 * Traverses the list and return the node if it was found.
 */
Node_t *getNode(uint16_t node_id, List *nodesList);

/**
 * \brief Return the timeslot with time 'time' in the list 'timeList'
 * \param time Time of the timeslot to be returned.
 * \param timeList Pointer to the list of timeslots
 * \return Timeslot if found; NULL otherwise.
 *
 * Traverses the list and return the timeslot if it was found.
 */
TimeSlot_t *getTimeSlot(uint16_t time, List *timeList);

/**
 * \brief Return the parent of a node in a tree.
 * \param tree The tree to be searched.
 * \param node The node to be looked for.
 * \return The parent of the node.
 *
 * Searches the node in the tree and returns its parent, if it exists.
 */
Node_t *getParent(Tree_t *tree, Node_t *node);

/**
 * \brief Return the subtree with a particular root node.
 * \param tree The tree to be searched.
 * \param root The root node to be looked for.
 * \return The subtree rooted at 'root'.
 *
 * Searches a subtree in the tree that is rooted at node 'root' and returns it.
 */
Tree_t *getSubTree(Tree_t *tree, Node_t *root);

/**
 * \brief Creates a list with all nodes in a tree.
 * \param tree The tree to be used.
 * \param listResult Pointer to a list to be populated with all nodes present in the tree.
 *
 * Populates the listResult with all nodes found in the tree
 */
void getListNodesInTree(Tree_t *tree, List *listResult);

void setTypeOfNodes(uint8_t sink_id, Tree_t *tree);

bool createPrrMatrix (uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[]);

/**
 * \brief Creates the ETX matrix.
 * \param etxMatrix ETX matrix to be created. It is a 3-D array of floats.
 * \param linksList List of links to be used.
 * \return Always true.
 *
 * This functions received the list of links in the network and creates the ETX matrix.
 */
bool createEtxMatrix (float etxMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[]);

/**
 * \brief Creates the connectivity matrix.
 * \param conMatrix Connectivity matrix to be created. It is a 3-D array of booleans.
 * \param linksList List of links to be used.
 * \param con_thr Connectivity ETX threshold to be used. Links will be considered to be "good" if both directions
 *                  have ETX lesser or equal to con_thr.
 * \return Always true.
 *
 * This functions received the list of links in the network and creates the ETX matrix, which is
 * a 3-D array with all ETX values from the list of links. All links that are not present in the list
 * have ETX equal to FLT_MAX (max float number)
 */
bool createConnectivityMatrix (bool conMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[], float con_thr);

/**
 * \brief Creates the interference matrix.
 * \param intMatrix Interference matrix to be created. It is a 3-D array of booleans.
 * \param linksList List of links to be used.
 * \param int_thr Interference ETX threshold to be used. Links will be considered to be interferers if any direction
 *                  has ETX lesser or equal to int_thr.
 * \return Always true.
 *
 * This functions received the list of links in the network and creates the interference matrix
 * This matrix will be a square MAX_NODES x MAX_NODES. In this matrix the cell (i,j) will have a NULL pointer if
 * is there is no link between i and j or if that link has ETX greater than 'int_thr'. If link (i,j) has ETX smaller
 * than 'int_thr' we are going to have a link in cell (i,j). Observe that interference is independent for each direction
 */
bool createInterferenceMatrix (bool intMatrix[][MAX_NODES][NUM_CHANNELS], List linksList[], float int_thr);

/**
 * \brief Creates the conflict matrix.
 * \param intMatrix Interference matrix to be created. It is a 3-D array of booleans.
 * \param nodeList List of nodes in the network.
 * \param confMatrix Conflict matrix to be created. It consists of all 2-hop interference cases.
 * \param withSchedule If it is true the conflict matrix will consider the current time schedule and remove conflicting
 *        nodes that do not share any time slot. This way the conflict matrix will be smaller
 * \return Always true.
 *
 * This functions received the interference matrix and creates the 2-hop conflict matrix. The conflict matrix
 * considers all 2-hop interferences. If withSchedule is set the time schedule is considered and a few conflicts may
 * be removed, since nodes may not share any concurrent time slots
 */
bool createConflictMatrix(Tree_t *tree, bool intMatrix[][MAX_NODES][NUM_CHANNELS], List nodesList[], bool confMatrix[][MAX_NODES][NUM_CHANNELS], bool withSchedule);

/**
 * \brief Returns a list with all conflicting nodes within n hops.
 * \param node_id ID of the node to which we are looking for the conflicts.
 * \param last_node_id If used in recursion, this variable avoid looking back into the last node subtree.
 * \param nodeList List of the nodes in the network.
 * \param intMatrix Interference matrix
 * \param hops How many hops aways is the conflict.
 * \return List of conflicting nodes.
 *
 * This functions received the interference matrix and creates a list of all conflicting nodes in the network. The execution
 * uses recursion and it can take advantage of variable 'last_node_id' to avoid looping back into last node's subtree.
 */
List *getConflictingNodes(uint8_t node_id, uint8_t last_node_id, List *nodesList, bool intMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t channel, uint8_t hops);

/**
 * \brief Returns the total ammount of traffic in all nodes in the nodesList.
 * \param nodesList List of nodes.
 * \return Summation of traffic from all nodes
 *
 * Sums up all traffic (parameter q) from all nodes in the nodesList
 */
uint16_t totalTraffic(List *nodesList);

/**
 * \brief Validate all subtrees.
 * \param tree Tree to be validated.
 *
 * Validate recursively all the subtrees. Basically set the valid bit for all subtrees.
 */
void validadeAllSubtrees(Tree_t *tree);

/**
 * \brief Update the hop count field of all nodes in the tree.
 * \param tree Tree to be analysed.
 * \param init_count Initial hop count to be considered (for the root node).
 *
 * Calculate and update the hop count of all nodes in the tree.
 */
void updateTreeHopCount(Tree_t *tree, uint8_t init_count);

/**
 * \brief Populate the linksList with all links of the tree and update the lists of RX links and TX links of all nodes.
 * \param tree Tree to be considered.
 * \param linksList List of links to be populated.
 *
 * Traverse the tree and populate the list linksList with all links. Also populate the lists of RX links and
 * TX links of all nodes in the tree.
 */
void generateLinksList(Tree_t *tree, List *linksList);

/**
 * \brief Populate the list of interfering nodes of each node in the nodesList.
 * \param confMatrix Conflicting matrix.
 * \param nodesList List of nodes in the network.
 *
 * Traverse the list of nodes and populate the list of interfering nodes according to the confMatrix.
 */
void generateNodesInterfering(bool confMatrix[][MAX_NODES][NUM_CHANNELS], List *nodesList, int8_t channel);

Node_t *getSink(List *nodesList);

#endif // _GRAPHS_H_

