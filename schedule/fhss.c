#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../util/list.h"
#include "../graphs/graphs.h"
#include "fhss.h"
#include "schedule.h"

uint8_t openwsn_fhss_calculate_chan(uint8_t freq_offset, uint64_t asn, uint8_t slotframe_size)
{
    return ((freq_offset + asn) % slotframe_size);
}

uint8_t tsch_function0_calculate_chan(uint8_t freq_offset, uint64_t asn, uint8_t slotframe_size)
{
    return (freq_offset);
}

uint8_t blacklist_calculate_chan(List *blacklist, uint8_t freq_offset, uint64_t asn, uint8_t slotframe_size)
{
    uint8_t freq;
    uint8_t i = 0;
    bool flag = true;

    while(flag)
    {
        freq = openwsn_fhss_calculate_chan(freq_offset, asn + i, slotframe_size);
        if (!ListFind(blacklist, (void *)freq))
        {
            flag = false;
        }
        i++;
    }

    return (freq);
}

uint8_t distributed_blacklist_calculate_chan(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint64_t asn, uint8_t slotframe_size)
{
    uint8_t freq = 0;

    for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
    {
        uint8_t freq_off = (uint8_t)elem->obj;

        freq = openwsn_fhss_calculate_chan(freq_off, asn, slotframe_size);
        if (prrMatrix[child->id][parent->id][freq] >= THRESHOLD_BLACKCHANNEL)
        {
            return (freq);
        }
    }

    return (freq);
}

uint16_t create_mask_channels(Node_t *node)
{
    uint16_t mask = 0;

    for (ListElem *elem = ListFirst(&node->channels); elem != NULL; elem = ListNext(&node->channels, elem))
    {
        uint8_t channel = (uint8_t)elem->obj;
        mask |= (1 << channel);
    }

    return (mask);
}
