//#define EXTERNAL_SCHEDULE

#include "opendefs.h"
#include "schedule.h"

#ifdef EXTERNAL_SCHEDULE
#define N_NODES 40
#define N_TIMESLOTS 39

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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_TX;
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 16:
					extScheduleEntry->type = CELLTYPE_TX;
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 14:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_TX;
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 13:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 15:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->channelOffset = 4;
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
					extScheduleEntry->channelOffset = 2;
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
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 7;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0015:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0016:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 7;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 7;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0017:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 7;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0018:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0019:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x001a:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 2;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x001b:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x001c:
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
					extScheduleEntry->channelOffset = 4;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x001d:
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
					extScheduleEntry->channelOffset = 1;
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 1;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x001e:
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
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 17:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 18:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x001f:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 4;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0020:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 3;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0021:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 7;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_RX;
					extScheduleEntry->channelOffset = 6;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 7;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0022:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0023:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 6;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0024:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0025:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0026:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0027:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				default:
					break;
			}
			break;
		case 0x0028:
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
				 case 19:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 20:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 21:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 22:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 23:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 24:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 25:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 26:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 27:
					extScheduleEntry->type = CELLTYPE_TX;
					extScheduleEntry->channelOffset = 5;
					break;
				 case 28:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 29:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 30:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 31:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 32:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 33:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 34:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 35:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 36:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 37:
					extScheduleEntry->type = CELLTYPE_OFF;
					extScheduleEntry->channelOffset = 0;
					break;
				 case 38:
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