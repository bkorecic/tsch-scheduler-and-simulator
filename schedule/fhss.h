#ifndef _FHSS_
#define _FHSS_

#include <stdint.h>

#define THRESHOLD_REWARD_GOOD_ARM           90
#define MAB_FIRST_BEST_ARMS                 8
#define MAB_EPSILON_N                       10      // epsilon initially is 1/MAB_EPSILON_N
#define MAB_EPSILON_TS_INCR_N               100000
#define MAB_REWARD_SUCESS_WEIGHT            0.2
#define MAB_REWARD_SUCESS                   100.0
#define MAB_REWARD_FAILED                   0.0

static const uint8_t chTemplate_default[] = {
   5,6,12,7,15,4,14,11,8,0,1,2,13,3,9,10
};

/**
 * \brief Calculates the channel based on OpenWSN FHSS function
 * \param freq_offset Frequency offset (0 to 15)
 * \param asn Absolute Sequence Number
 * \return channel (o to 15)
 *
 */
uint8_t fhssOpenwsnChan(uint8_t freq_offset, uint64_t asn);

/**
 * \brief Calculates the channel considering the fixed global blacklist
 * \param freq_offset Frequency offset (0 to 15)
 * \param asn Absolute Sequence Number
 * \return channel (o to 15)
 *
 */
uint8_t fhssCentralizedBlacklistChan(Node_t *parent, List *blacklist, uint64_t asn);

/**
 * \brief Calculates the channel considering MAB epsilon-greedy algorithm
 * \param parent Parent node
 * \param child Child node
 * \param prrMatrix PRR matrix
 * \param asn Absolute Sequence Number
 * \return channel (o to 15)
 *
 * In the exploitation phase pulls the best arm
 */
uint8_t fhssDistributedBlacklistMABBestArmChan(Node_t *parent, Node_t *child, uint64_t asn);

uint8_t fhssDistributedBlacklistMABFirstBestArmChan(Node_t *parent, Node_t *child, uint64_t asn);

/**
 * \brief Calculates the channel considering MAB epsilon-greedy algorithm
 * \param parent Parent node
 * \param child Child node
 * \param prrMatrix PRR matrix
 * \param asn Absolute Sequence Number
 * \return channel (o to 15)
 *
 * In the exploitation phase pulls the first good arm (reward above THRESHOLD_REWARD_GOOD_ARM)
 */
uint8_t fhssDistributedBlacklistMABFirstGoodArmChan(Node_t *parent, Node_t *child, uint64_t asn);

/**
 * \brief Calculates the channel considering optimal channel (the best)
 * \param parent Parent node
 * \param child Child node
 * \param prrMatrix PRR matrix
 * \param asn Absolute Sequence Number
 * \return channel (o to 15)
 *
 */
uint8_t fhssDistributedBlacklistOptimalChan(Node_t *parent, Node_t *child, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], uint64_t asn);

uint8_t fhssDistributedBlacklistMABExplore(Node_t *parent, uint64_t asn);
uint16_t createMaskChannels(Node_t *node);

#endif // _SCHEDULE_
