#include "opendefs.h"
#include "topology.h"
#include "idmanager.h"

bool topology_isAcceptablePacket(ieee802154_header_iht* ieee802514_header) {
#ifdef FORCETOPOLOGY
	bool returnVal;
	returnVal=FALSE;
	uint16_t my_addr = idmanager_getMyID(ADDR_64B)->addr_64b[7] | (idmanager_getMyID(ADDR_64B)->addr_64b[6] << 8);
	uint16_t src_addr = ieee802514_header->src.addr_64b[7] | (ieee802514_header->src.addr_64b[6] << 8);
	switch (my_addr) {
		case 0x6ce6:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0xedbc:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0x50f4:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0x629b:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0x6658:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0x5890:
			if (
				src_addr==0x6ce6||
				src_addr==0xedbc||
				src_addr==0x50f4||
				src_addr==0x629b||
				src_addr==0x6658||
				src_addr==0x4ffa||
				src_addr==0x619e||
				src_addr==0xcf11||
				src_addr==0xf361
			) {
			returnVal=TRUE;
		}
		break;
		case 0x4ffa:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0x619e:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0xcf11:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0xf361:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
	}
	return returnVal;
#else
	return TRUE;
#endif
}
