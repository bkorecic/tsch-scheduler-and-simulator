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

bool main_no_schedule(List *nodesList, uint8_t slotframe_size, uint8_t n_beacon_timeslot, float duty_cycle)
{
    TimeSlot_t *ts = NULL;

    /* Create the list of timeslots for all nodes */
    for (ListElem *elem = ListFirst(nodesList); elem != NULL; elem = ListNext(nodesList, elem))
    {
        uint8_t cur_time = 1;

        /* Get the current node */
        Node_t *node = (Node_t *)elem->obj;

        /* Create the timeslots with type Beacon */
        for (; cur_time <= n_beacon_timeslot; cur_time++)
        {
            ts = newTimeSlot(cur_time, 0, TS_BEACON, NULL, false);
            ListAppend(&node->timeslots, (void *)ts);
        }

        /* Create the timeslots with type Shared */
        uint8_t n_shared_timeslot = (uint8_t)((float)slotframe_size * duty_cycle);
        for (; cur_time <= n_shared_timeslot; cur_time++)
        {
            ts = newTimeSlot(cur_time, 0, TS_SHARED, NULL, false);
            ListAppend(&node->timeslots, (void *)ts);
        }

        /* Create the timeslots with type Idle */
        for (; cur_time < slotframe_size; cur_time++)
        {
            ts = newTimeSlot(cur_time, 0, TS_IDLE, NULL, false);
            ListAppend(&node->timeslots, (void *)ts);
        }
    }

    return (true);
}
