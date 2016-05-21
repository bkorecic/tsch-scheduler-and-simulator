#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../util/list.h"
#include "../util/files.h"
#include "../util/debug.h"
#include "../graphs/graphs.h"
#include "fhss.h"
#include "schedule.h"

uint32_t epsilon_n          = MAB_EPSILON_INIT_N;
uint32_t epsilon_init_n     = MAB_EPSILON_INIT_N;
uint16_t epsilon_ts_incr_n  = MAB_EPSILON_TS_INCR_N;
uint32_t epsilon_max_n      = MAB_EPSILON_MAX_N;

uint8_t mab_first_best_arms     = MAB_FIRST_BEST_ARMS;
uint8_t mab_threshoold_good_arm = MAB_THRESHOLD_GOOD_ARM;

uint8_t fhssOpenwsnChan(uint8_t freq_offset, uint64_t asn)
{
    uint8_t ch_idx = (freq_offset + asn) % NUM_CHANNELS;

    return (chTemplate_default[ch_idx]);
}

uint8_t fhssCentralizedBlacklistChan(Node_t *parent, List *blacklist, uint64_t asn)
{
    uint8_t freq = 0;

    for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
    {
        uint8_t freq_offset = (uint8_t)elem->obj;

        freq = fhssOpenwsnChan(freq_offset, asn);
        if (!ListFind(blacklist, (void *)freq))
        {
            break;
        }
    }

    return (freq);
}

uint8_t fhssDistributedBlacklistMABBestArmChan(Node_t *parent, Node_t *child, uint64_t asn)
{
    uint8_t freq = 0;

    /* Every epsilon_ts_incr_n time slots we divide increment epsilon_n */
    if ((epsilon_ts_incr_n != 0) && ((asn + 1) % epsilon_ts_incr_n) == 0)
    {
        if (++epsilon_n == epsilon_max_n) {
            epsilon_n = epsilon_init_n;
            PRINTF("Reseting Epsilon to %ld at %lld\n", (long)epsilon_init_n, (long long)asn);
        }
    }

    if ((rand() % epsilon_n) == 0)
    {
        /* We will explore all channels randomly */

        return (fhssDistributedBlacklistMABExplore(parent, asn));
    }
    else
    {
        /* We will exploit the best arm */

        uint8_t best_freq = 0, best_reward = 0;
        for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
        {
            uint8_t freq_off = (uint8_t)elem->obj;

            freq = fhssOpenwsnChan(freq_off, asn);
            if (parent->avg_reward[child->id][freq] > best_reward)
            {
                best_freq = freq;
                best_reward = parent->avg_reward[child->id][freq];
            }
        }

        return (best_freq);
    }
}

uint8_t fhssDistributedBlacklistMABFirstBestArmChan(Node_t *parent, Node_t *child, uint64_t asn)
{
    uint8_t freq = 0;

    /* Every epsilon_ts_incr_n time slots we divide increment epsilon_n */
    if ((epsilon_ts_incr_n != 0) && ((asn + 1) % epsilon_ts_incr_n) == 0)
    {
        if (++epsilon_n == epsilon_max_n) {
            epsilon_n = epsilon_init_n;
            PRINTF("Reseting Epsilon to %ld at %lld\n", (long)epsilon_init_n, (long long)asn);
        }
    }

    if ((rand() % epsilon_n) == 0)
    {
        /* We will explore all channels randomly */

        return (fhssDistributedBlacklistMABExplore(parent, asn));
    }
    else
    {
        /* Lets order all channel sorting by average_reward */
        List ordered_channel; memset(&ordered_channel, 0, sizeof(List)); ListInit(&ordered_channel);
        for (uint8_t i = 0; i < NUM_CHANNELS; i++)
        {
            ListElem *elem;
            for (elem = ListFirst(&ordered_channel); elem != NULL; elem = ListNext(&ordered_channel, elem))
            {
                uint8_t channel = (uint8_t)elem->obj;

                if (parent->avg_reward[child->id][i] > parent->avg_reward[child->id][channel])
                {
                    ListInsertBefore(&ordered_channel, (void *)i, elem);
                    break;
                }
            }

            if (elem == NULL)
            {
                ListAppend(&ordered_channel, (void *)i);
            }
        }

        /* Create a blacklist with the first best MAB_FIRST_BEST_ARMS channels */
        uint16_t blacklist = 0;
        uint8_t n_channels = 1;
        for (ListElem *elem = ListFirst(&ordered_channel); elem != NULL; elem = ListNext(&ordered_channel, elem))
        {
            uint8_t channel = (uint8_t)elem->obj;
            blacklist |= (1 << channel);

            /* Check if we already got the MAB_FIRST_BEST_ARMS first best channels */
            if (++n_channels > mab_first_best_arms)
            {
                break;
            }
        }

        for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
        {
            uint8_t freq_off = (uint8_t)elem->obj;

            freq = fhssOpenwsnChan(freq_off, asn);
            if (blacklist & (1 << freq))
            {
                return (freq);
            }
        }

        return (freq);
    }
    return 0;
}

uint8_t fhssDistributedBlacklistMABFirstGoodArmChan(Node_t *parent, Node_t *child, uint64_t asn)
{
    uint8_t freq = 0;

    /* Every epsilon_ts_incr_n time slots we divide increment epsilon_n */
    if ((epsilon_ts_incr_n != 0) && ((asn + 1) % epsilon_ts_incr_n) == 0)
    {
        if (++epsilon_n == epsilon_max_n) {
            epsilon_n = epsilon_init_n;
            PRINTF("Reseting Epsilon to %ld at %lld\n", (long)epsilon_init_n, (long long)asn);
        }
    }

    if ((rand() % epsilon_n) == 0)
    {
        /* We will explore all channels randomly */

        return (fhssDistributedBlacklistMABExplore(parent, asn));
    }
    else
    {
        /* We will exploit the first good arm */

        for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
        {
            uint8_t freq_off = (uint8_t)elem->obj;

            freq = fhssOpenwsnChan(freq_off, asn);
            if (parent->avg_reward[child->id][freq] >= mab_threshoold_good_arm)
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

    //PRINTF("FHSS exploring at %lld\n", (long long)asn);

    uint8_t i = 0;
    for (ListElem *elem = ListFirst(&parent->channels); elem != NULL; elem = ListNext(&parent->channels, elem))
    {
        if (i++ == offset_to_explore)
        {
            uint8_t freq_off = (uint8_t)elem->obj;

            return (fhssOpenwsnChan(freq_off, asn));
        }
    }

    return (0);
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

void fhssSetEpsilonN(uint32_t new_epsilon_n)
{
    epsilon_n = new_epsilon_n;
}

void fhssSetEpsilonInitN(uint32_t new_epsilon_init_n)
{
    epsilon_init_n = new_epsilon_init_n;
}

void fhssSetEpsilonTSIncrN(uint32_t new_epsilon_ts_incr_n)
{
    epsilon_ts_incr_n = new_epsilon_ts_incr_n;
}

void fhssSetEpsilonMaxN(uint32_t new_epsilon_max_n)
{
    epsilon_max_n = new_epsilon_max_n;
}

void fhssSetMABThreshooldGoodArm(uint8_t new_threshold_good_arm)
{
    mab_threshoold_good_arm = new_threshold_good_arm;
}

void fhssSetMABFirstBestArms(uint8_t new_first_best_arms)
{
    mab_first_best_arms = new_first_best_arms;
}
