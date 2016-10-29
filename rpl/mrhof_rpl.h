#ifndef _MRHOF_RPL_H_
#define _MRHOF_RPL_H_

#include <stdint.h>
#include <stdbool.h>

#include "../graphs/graphs.h"
#include "../util/list.h"
#include "../util/defs.h"

bool mrhofUpdateDAGRanks(Node_t *node, List *nodesList);
bool mrhofUpdateParents(List *nodesList, uint8_t rpl_algo);
bool mrhofRxDio(Node_t *node, List *nodesList);

#endif // _MRHOF_RPL_H_

