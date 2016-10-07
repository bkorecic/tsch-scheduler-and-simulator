#ifndef _RPL_H_
#define _RPL_H_

#include <stdint.h>
#include <stdbool.h>

#include "../util/list.h"
#include "../util/defs.h"
#include "../graphs/graphs.h"

#define RPL_MRHOF                 1
//#define RPL_TAMU_GREEDY           2
//#define RPL_TAMU_MULTIHOP_ETX     3
#define RPL_TAMU_MULTIHOP_RANK    4

// From OpenWSN
#define MAXDAGRANK                0xffff
#define DEFAULTDAGRANK            MAXDAGRANK
#define MINHOPRANKINCREASE        256  //default value in RPL and Minimal 6TiSCH draft
#define DEFAULTLINKCOST           15

#define DIO_PERIOD_MS             10000 // 10 seconds
#define KA_PERIOD_MS              2000 // 2 seconds

#define N_TIMESLOTS_PER_DIO       (DIO_PERIOD_MS / 10)    // timeslots of 10 ms
#define N_TIMESLOTS_PER_KA        (KA_PERIOD_MS / 10)     // timeslots of 10 ms

#define STABLE_NEIGHBOR_THRESHOLD 50

typedef enum {
    MRHOF_ETX,
    TAMU,
} RPL_OF;

typedef struct rpl_neighbor_t {
	uint16_t    id;                 /* Node ID */

    uint32_t    rx_success;
    uint32_t    rx_failed;

    float       estimated_etx;
    uint8_t     average_prr;

    float       dagRank;
    uint8_t     hop_count;

    bool        prefered_parent;
    bool        stable;             /* If PRR is above a threshold */

/* TAMU_RPL */
    uint16_t    n_sampled;    /* Number of times the neighbor has been sampled */
    float      beta_sample;

} RPL_Neighbor_t;

int execute_rpl(uint8_t rpl_alg, List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t channel, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka, uint32_t n_timeslots_per_log);
void init_rpl(List *nodesList, uint8_t sink_id, uint8_t rpl_algo);

void rplTXDIO(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka);
void rplRxDIO(uint8_t rpl_alg, Node_t *txNode, Node_t *rxNode, uint8_t prr);
void rplTXKA(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, uint64_t cur_asn, List *ka_to_transmit, uint32_t min_asn_per_ka);
void rplRxKA(Node_t *txNode, Node_t *rxNode, bool succes);

void rplScheduleDIO(List *dio_to_transmit, Node_t *txNode, uint64_t asn);
void rplScheduleKA(List *ka_to_transmit, Node_t *txNode, uint64_t asn);

uint64_t rplGetNextDIOASN(Node_t *node, uint32_t min_asn_per_dio);
uint64_t rplGetNextKAASN(Node_t *node, uint32_t min_asn_per_ka);

bool rplProcessTXDIO(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq, List *dio_to_transmit, List *ka_to_transmit, uint32_t min_asn_per_dio, uint32_t min_asn_per_ka);
bool rplProcessTXKA(uint8_t rpl_alg, Node_t *txNode, List *nodesList, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint8_t freq);

Node_t *rplPreferedParent(Node_t *node, List *nodesList);

void rplOutputPullArms(List *nodesList, uint8_t rpl_algo, bool first_time);
void rplOutputRegretFile(List *nodesList, uint8_t rpl_algo, bool first_time);
void rplOutputFullLog(List *nodesList, uint8_t rpl_algo, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], bool first_time);
void rplOutputThroughputFile(List *nodesList, uint8_t rpl_algo, bool first_time);

uint8_t rplAveragPRR(uint8_t txID, uint8_t rxID, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS]);

#endif // _RPL_H_

