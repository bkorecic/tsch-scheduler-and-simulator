#ifndef _MRHOF_RPL_H_
#define _MRHOF_RPL_H_

#include <stdint.h>
#include <stdbool.h>

#include "../graphs/graphs.h"
#include "../util/list.h"
#include "../util/defs.h"

ListElem *dijkstraMinCost(List *nodesQueue);
uint16_t dijkstraGetRank(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS]);

#endif // _MRHOF_RPL_H_

