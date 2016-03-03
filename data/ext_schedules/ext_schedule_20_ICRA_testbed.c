//#define EXTERNAL_SCHEDULE

#include "opendefs.h"
#include "schedule.h"

#ifdef EXTERNAL_SCHEDULE
#define N_NODES 20
#define N_TIMESLOTS 19

void getExtSchedule(uint16_t addr, uint8_t timeslot_offset, extScheduleEntry_t *extScheduleEntry)
{
	switch (addr) {
		case 0x6ce6:
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
		case 0xedbc:
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
		case 0x50f4:
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
		case 0x629b:
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
		case 0x6658:
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
		case 0x5890:
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
		case 0x4ffa:
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
		case 0x619e:
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
		case 0xcf11:
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
		case 0xf361:
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
		case 0x6300:
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
		case 0x209c:
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
		case 0x79b6:
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
		case 0x62b9:
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
		case 0xf078:
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
		case 0x5517:
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
		case 0x52c3:
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
		case 0x4baa:
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
		case 0x76e7:
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
		case 0xcdeb:
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