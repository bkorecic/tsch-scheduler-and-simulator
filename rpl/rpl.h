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

typedef enum {
    MRHOF_ETX,
    TAMU,
} RPL_OF;

int execute_rpl(List *nodesList, Tree_t *tree, uint8_t sink_id, uint8_t fhss, char *prr_file_prefix, uint32_t n_timeslots_per_file, uint32_t average_asn_per_dio);

void init_rpl(List *nodesList, uint8_t sink_id);

uint64_t rplGetNextDIOASN(Node_t *node, uint32_t average_asn_per_dio);

#endif // _RPL_H_

