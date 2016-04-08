#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../util/list.h"
#include "../graphs/graphs.h"
#include "fhss.h"
#include "schedule.h"

uint8_t fhssOpenwsnChan(uint8_t freq_offset, uint64_t asn)
{
    uint8_t ch_idx = (freq_offset + asn) % NUM_CHANNELS;

    return chTemplate_default[ch_idx];
}

uint8_t fhssCentralizedBlacklistChan(List *blacklist, uint8_t freq_offset, uint64_t asn)
{
    uint8_t freq;
    uint8_t i = 0;
    bool flag = true;

    while(flag == true && i < NUM_CHANNELS)
    {
        freq = fhssOpenwsnChan(freq_offset, asn + i);
        if (!ListFind(blacklist, (void *)freq))
        {
            flag = false;
        }
        i++;
    }

    return (freq);
}

uint8_t fhssDistributedBlacklistMABBestArmChan(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint64_t asn)
{
    uint8_t freq = 0;

    float draw = (float)(rand() % 100)/100.0;

    if (draw < MAB_EPSILON)
    {
        /* We will explore all channels randomly */

        return fhssDistributedBlacklistMABExplore(parent, asn);
    }
    else
    {
        /* We will exploit the best arm */

        uint8_t best_freq = 0, best_reward = 0;
        for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
        {
            uint8_t freq_off = (uint8_t)elem->obj;

            freq = fhssOpenwsnChan(freq_off, asn);
            if (parent->avg_reward[freq] > best_reward)
            {
                best_freq = freq;
                best_reward = parent->avg_reward[freq];
            }
        }

        return (freq);
    }
}

uint8_t fhssDistributedBlacklistMABFirstGoodArmChan(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint64_t asn)
{
    uint8_t freq = 0;

    float draw = (float)(rand() % 100)/100.0;

    if (draw < MAB_EPSILON)
    {
        /* We will explore all channels randomly */

        return fhssDistributedBlacklistMABExplore(parent, asn);
    }
    else
    {
        /* We will exploit the first good arm */

        for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
        {
            uint8_t freq_off = (uint8_t)elem->obj;

            freq = fhssOpenwsnChan(freq_off, asn);
            if (parent->avg_reward[freq] > THRESHOLD_REWARD_GOOD_ARM)
            {
                return (freq);
            }
        }

        return (freq);
    }
    return 0;
}

uint8_t fhssDistributedBlacklistOptimalChan(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint64_t asn)
{
    uint8_t best_freq = 0, best_prr = 0;

    for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
    {
        uint8_t freq_off = (uint8_t)elem->obj;

        uint8_t freq = fhssOpenwsnChan(freq_off, asn);
        if (prrMatrix[child->id][parent->id][freq] > best_prr)
        {
            best_freq = freq;
            best_prr = prrMatrix[child->id][parent->id][freq];
        }
    }

    return (best_freq);
}

uint8_t fhssDistributedBlacklistMABExplore(Node_t *parent, uint64_t asn)
{
    uint8_t offset_to_explore = rand() % ListLength(&parent->channels);

    uint8_t i = 0;
    for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
    {
        if (i++ == offset_to_explore)
        {
            uint8_t freq_off = (uint8_t)elem->obj;

            return (fhssOpenwsnChan(freq_off, asn));
        }
    }
}

uint16_t createMaskChannels(Node_t *node)
{
    uint16_t mask = 0;

    for (ListElem *elem = ListFirst(&node->channels); elem != NULL; elem = ListNext(&node->channels, elem))
    {
        uint8_t channel = (uint8_t)elem->obj;
        mask |= (1 << channel);
    }

    return (mask);
}
