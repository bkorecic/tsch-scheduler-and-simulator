#ifndef _TAMU_RPL_H_
#define _TAMU_RPL_H_

#include <stdint.h>
#include <stdbool.h>
#include "rpl.h"

#define N_TIMESLOTS_TAMU_RPL  (N_TIMESLOTS_PER_KA * 10)   // Number of timeslot for each Thompson Sampling round.
                                                          // It should be much greater than KA interval to receive packets
void tamuUpdateParents(List *nodesList);
void tamuSetPreferedParent(RPL_Neighbor_t *neighbor);
void tamuSampleNode(Node_t *node);

#endif // _TAMU_RPL_H_

