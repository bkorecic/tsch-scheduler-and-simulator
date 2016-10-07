#ifndef _TAMU_RPL_H_
#define _TAMU_RPL_H_

#include <stdint.h>
#include <stdbool.h>
#include "rpl.h"

#define N_TIMESLOTS_TAMU_RPL  (N_TIMESLOTS_PER_KA * 15)   // Number of timeslot for each Thompson Sampling round.
                                                          // It should be much greater than KA interval to receive packets
bool tamuUpdateParents(List *nodesList, uint8_t rpl_algo);

bool tamuSampleNodeMinHop(Node_t *node);
bool tamuSampleNodeMultiHopEtx(Node_t *node);
bool tamuSampleNodeMultiHopRank(Node_t *node);

void tamuSetPreferedParent(Node_t *node, RPL_Neighbor_t *neighbor);

bool tamuRxDio(Node_t *node);

#endif // _TAMU_RPL_H_

