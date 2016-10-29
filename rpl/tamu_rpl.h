#ifndef _TAMU_RPL_H_
#define _TAMU_RPL_H_

#include <stdint.h>
#include <stdbool.h>
#include "rpl.h"

bool tamuUpdateParents(List *nodesList, uint8_t rpl_algo);
bool tamuSampleNodeMultiHopRank(Node_t *node, List *nodesList);
void tamuSetPreferedParent(Node_t *node, RPL_Neighbor_t *neighbor);
bool tamuRxDio(Node_t *node, List *nodesList);

#endif // _TAMU_RPL_H_

