#ifndef _TASA_COLORING_
#define _TASA_COLORING_

#include <stdint.h>
#include <stdbool.h>
#include "../util/list.h"
#include "../graphs/graphs.h"

/**
 * \brief Performs the coloring algorithm that finds out the channel allocation for the transmitting nodes.
 * \param nodesScheduled The nodes that were scheduled to transmit at the same time.
 * \param confMatrix The conflict matrix of the network.
 * \param Q Matrix with Q values (global queue).
 * \param ts Current time slot
 * \return Tre number of channels used in the coloring algorithm.
 *
 * Executes the coloring algorithm and finds the channel allocation of the nodes that were scheduled to
 * transmit simultaneously
 */
uint8_t tasaColoring(List *nodesScheduled, bool confMatrix[][MAX_NODES][NUM_CHANNELS], uint16_t Q[][MAX_TIMESLOTS], uint16_t ts, int8_t channel);

#endif // _TASA_COLORING_
