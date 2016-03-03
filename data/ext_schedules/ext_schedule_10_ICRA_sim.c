//#define EXTERNAL_SCHEDULE

#include "opendefs.h"
#include "schedule.h"

#ifdef EXTERNAL_SCHEDULE
#define N_NODES 10
#define N_TIMESLOTS 9

void getExtSchedule(uint16_t addr, uint8_t timeslot_offset, extScheduleEntry_t *extScheduleEntry)
{
	switch (addr) {
		case 0x0001:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0002:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0003:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0004:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0005:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0006:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0007:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0008:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0009:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x000a:
			switch(timeslot_offset) {
				 case 0:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 1:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 2:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 3:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 4:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 5:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 6:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 7:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
#endif