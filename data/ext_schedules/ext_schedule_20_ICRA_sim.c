//#define EXTERNAL_SCHEDULE

#include "opendefs.h"
#include "schedule.h"

#ifdef EXTERNAL_SCHEDULE
#define N_NODES 20
#define N_TIMESLOTS 19

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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 8:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_TX;
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x000b:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x000c:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x000d:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x000e:
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
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x000f:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0010:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0011:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0012:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0013:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0014:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 9:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 10:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 11:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 12:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 18:
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