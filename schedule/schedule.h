#ifndef _SCHEDULE_
#define _SCHEDULE_

#define THRESHOLD_BLACKCHANNEL  95

/**
 * \brief Execute the schedule and calculate statistics
 * \param nodesList List of nodes in the network.
 * \param linksList List of links in the network.
 * \param tree Distribution tree.
 * \param sink_id ID of the sink node
 * \param prrMatrix PRR matrix
 * \param prr_file PRR filename
 * \param n_timeslots_per_file Number of timeslots (each of 10ms) per Links file
 * \return Always true.
 *
 * Forms the schedule considering MCC algorithm, from paper "Multi-Channel Data Collection for Throughput
 * Maximization in Wireless Sensor Networks".
 */
int execute_schedule(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, char *prr_file_prefix, uint64_t n_timeslots_per_file);

void createBlacklist(List *blacklist, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], List *nodesList, Tree_t *tree, uint8_t prrThreshold, uint8_t n_channels);

#endif // _SCHEDULE_
