#ifndef _RPL_H_
#define _RPL_H_

#include <stdint.h>
#include <stdbool.h>

#include "../util/list.h"
#include "../util/defs.h"
#include "../graphs/graphs.h"

// From OpenWSN
#define MAXDAGRANK                0xffff
#define DEFAULTDAGRANK            MAXDAGRANK
#define MINHOPRANKINCREASE        256  //default value in RPL and Minimal 6TiSCH draft
#define DEFAULTLINKCOST           15

#define DIO_PERIOD_MS             30000 // 30 seconds
#define KA_PERIOD_MS              10000 // 10 seconds

#define N_TIMESLOTS_PER_DIO       DIO_PERIOD_MS / 10    // timeslots of 10 ms
#define N_TIMESLOTS_PER_KA        KA_PERIOD_MS / 10     // timeslots of 10 ms

typedef enum {
    MRHOF_ETX,
    TAMU,
} RPL_OF;

typedef struct rpl_neighbor_t {
	uint16_t     id;                 /* Node ID */

    uint16_t    rx_success;
    uint16_t    rx_failed;

    float       estimated_etx;

    uint16_t    dagRank;
    bool        prefered_parent;

} RPL_Neighbor_t;

int execute_rpl(List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t channel, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka);
void init_rpl(List *nodesList, uint8_t sink_id);

void rplTXDIO(Node_t *dioNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka);
bool rplRxDIO(Node_t *rxNode, Node_t *txNode, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka);

void rplTXKA(Node_t *kaNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *ka_to_transmit, uint32_t min_asn_per_ka);

void rplScheduleDIO(List *dio_to_transmit, Node_t *node, uint64_t asn);
void rplScheduleKA(List *ka_to_transmit, Node_t *node, uint64_t asn);

uint64_t rplGetNextDIOASN(Node_t *node, uint32_t min_asn_per_dio);
uint64_t rplGetNextKAASN(Node_t *node, uint32_t min_asn_per_ka);

bool rplProcessTXDIO(Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka);
bool rplProcessTXKA(Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq);

Node_t *rplPreferedParent(Node_t *node, List *nodesList);

#endif // _RPL_H_

