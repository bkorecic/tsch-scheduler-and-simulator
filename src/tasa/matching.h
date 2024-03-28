#ifndef _TASA_MATCHING_
#define _TASA_MATCHING_

#include <stdbool.h>
#include <stdint.h>
#include "../util/list.h"
#include "../graphs/graphs.h"

/**
 * \brief Performs the matching algorithm that finds out all links that can be scheduled concurrently.
 * \param DCFL List of Duplex Conflict Free links.
 * \param q Matrix with q values (local queue).
 * \param Q Matrix with Q values (global queue).
 * \param tree Network tree
 * \param k Current time slot
 * \param nx Root node
 * \return Always true.
 *
 * Executes the matching algorithm and returns a list of Duplex Conflict Free links, which are links that can be
 * scheduled simultaneously with no duplex confict
 */
bool tasaMatching(List *DCFL, uint16_t q[][MAX_TIMESLOTS], uint16_t Q[][MAX_TIMESLOTS], Tree_t *tree, uint8_t k, Node_t *nx);

/**
 * \brief Returns the first child node that satisfies Equation 1 from TASA paper.
 * \param q Matrix with q values (local queue).
 * \param Q Matrix with Q values (global queue).
 * \param tree Network tree.
 * \param ts Current time slot.
 * \return A child node that satisfies Equation 1; NULL if no such node exists.
 *
 * Returns the child node that has the largest Q value if such node has at least one local packet (q > 0).
 */
Node_t *getChildEq1(uint16_t q[][MAX_TIMESLOTS], uint16_t Q[][MAX_TIMESLOTS], Tree_t *tree, uint8_t ts);

/**
 * \brief Returns the size of children nodes which are valid nodes.
 * \param tree Network tree.
 * \return Number of valid children.
 *
 * Returns the number of valid children in the tree.
 */
uint8_t lengthChildren(Tree_t *tree);

/**
 * \brief Returns the first valid child.
 * \param tree Network tree.
 * \return The first valid child.
 *
 * Returns the first valid child.
 */
Tree_t *getValidChild(Tree_t *tree);

#endif // _TASA_MATCHING_
