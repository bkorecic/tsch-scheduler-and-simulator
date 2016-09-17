#ifndef _NO_SCHEDULE_
#define _NO_SCHEDULE_

/**
 * \brief Forms a schedule with shared timeslots
 * \param nodesList List of nodes in the network.
 * \param linksList List of links in the network.
 * \param tree Distribution tree.
 * \param sink_id ID of the sink node.
 * \return Always true.
 *
 * Forms the schedule with N shared timeslots, where N is equal to the number of sensor nodes (exclude the sink).
 */
bool main_no_schedule(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, int8_t channel);

#endif // _NO_SCHEDULE_
