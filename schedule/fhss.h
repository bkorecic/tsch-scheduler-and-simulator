#ifndef _FHSS_
#define _FHSS_

#include <stdint.h>

uint8_t openwsn_fhss_calculate_chan(uint8_t freq_offset, uint64_t asn, uint8_t slotframe_size);
uint8_t tsch_function0_calculate_chan(uint8_t freq_offset, uint64_t asn, uint8_t slotframe_size);
uint8_t blacklist_calculate_chan(List *blacklist, uint8_t freq_offset, uint64_t asn, uint8_t slotframe_size);
uint8_t distributed_blacklist_calculate_chan(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint64_t asn, uint8_t slotframe_size);
uint16_t create_mask_channels(Node_t *node);

#endif // _SCHEDULE_
