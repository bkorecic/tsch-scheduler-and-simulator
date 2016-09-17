#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/list.h"
#include "../util/files.h"
#include "../util/print.h"
#include "../util/debug.h"
#include "../graphs/graphs.h"
#include "fhss.h"
#include "no-schedule.h"

bool main_no_schedule(List *nodesList, List *linksList, Tree_t *tree, uint8_t sink_id, int8_t channel)
{
    uint8_t n_nodes = ListLength(nodesList);

    /* Create the list of timeslots for all nodes */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        // Create n_nodes - 1 shared timeslots
        for (uint8_t t = 1; t < n_nodes - 1; t++)
        {
            TimeSlot_t *ts = newTimeSlot(t, channel, TS_SHARED, NULL, false);
            ListAppend(&node->timeslots, (void *)ts);
        }
    }

    return (true);
}
