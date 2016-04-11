#ifndef _SCHEDULE_
#define _SCHEDULE_

#define THRESHOLD_BLACKCHANNEL  95

/**
 * \brief Executes the schedule and calculates statistics
 * \param nodesList List of nodes in the network.
 * \param linksList List of links in the network.
 * \param tree Distribution tree.
 * \param sink_id ID of the sink node
 * \param prrMatrix PRR matrix
 * \param prr_file PRR filename
 * \param n_timeslots_per_file Number of timeslots (each of 10ms) per Links file
 * \param n_timeslots_regret Number of timeslots that we have to account before outputing the regret
 * \return Always true.
 *
 */
int execute_schedule(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, char *prr_file_prefix, uint64_t n_timeslots_per_file, uint16_t n_timeslots_log);

/**
 * \brief Creates a blacklist with channels where there is at least of link with PRR is below prrThreshold.
 * \param prrMatrix PRR matrix
 * \param nodesList List of nodes in the network.
 * \param tree Distribution tree.
 * \param prrThreshold PRR threshold. A channel will be in the blacklist if at least one link in the tree has PRR below prrThreshold at that channel
 * \param n_channels Number of channels to be blacked
 * \return List of channels with bad quality.
 *
 * The list will have n_channels channels with at least of link with PRR below prrThreshold. The list has the wors channels,
 * or the channel with more links with bad quality (below prrThreshold)
 */
void createBlacklist(List *blacklist, uint8_t prrMatrix[][MAX_NODES][NUM_CHANNELS], List *nodesList, Tree_t *tree, uint8_t prrThreshold, uint8_t n_channels);

void outputRegretFile(List *nodesList, uint8_t fhss);
void outputThroughputFile(List *nodesList, uint8_t fhss);

#endif // _SCHEDULE_
