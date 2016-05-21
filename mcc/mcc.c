#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../graphs/graphs.h"
#include "../util/list.h"
#include "../util/debug.h"
#include "../util/files.h"
#include "../util/defs.h"
#include "../graphs/graphs.h"
#include "cms_tree.h"
#include "graph_coloring.h"
#include "time_schedule.h"

int main_mcc(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, \
             bool intMatrix[][MAX_NODES][NUM_CHANNELS], bool confMatrix[][MAX_NODES][NUM_CHANNELS], float prrMatrix[][MAX_NODES][NUM_CHANNELS], \
             bool ca_routing, bool ca_allocation, bool optimal_sched, int8_t channel, float etx_threshold)
{
    /* Create the time slots */
    createOptimalTimeSlotSchedule(tree, nodesList, optimal_sched);

    /* Create the conflict matrix considering the connectivity, interference and cmsTree */
    createConflictMatrix(tree, intMatrix, nodesList, confMatrix, true);

    /* Assign the receive channels */
    if (ca_allocation)
    {
        assignChannelLinks(nodesList, prrMatrix, confMatrix, tree, etx_threshold);
    }
    else
    {
        assignChannelNodes(nodesList, confMatrix, RX_BASED, tree, channel);
    }

    return (true);
}
