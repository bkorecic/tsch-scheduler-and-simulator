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
				src_addr==0xf361||
				src_addr==0x6300||
				src_addr==0x209c||
				src_addr==0x79b6||
				src_addr==0x62b9
			) {
			returnVal=TRUE;
		}
		break;
		case 0x4ffa:
			if (
				src_addr==0x5890||
				src_addr==0x81fc
			) {
			returnVal=TRUE;
		}
		break;
		case 0x619e:
			if (
				src_addr==0x5890||
				src_addr==0x4527||
				src_addr==0xcdeb||
				src_addr==0x53b8
			) {
			returnVal=TRUE;
		}
		break;
		case 0xcf11:
			if (
				src_addr==0x5890||
				src_addr==0xfcaf
			) {
			returnVal=TRUE;
		}
		break;
		case 0xf361:
			if (
				src_addr==0x5890||
				src_addr==0xf078
			) {
			returnVal=TRUE;
		}
		break;
		case 0x6300:
			if (
				src_addr==0x5890||
				src_addr==0x4da3
			) {
			returnVal=TRUE;
		}
		break;
		case 0x209c:
			if (
				src_addr==0x5890||
				src_addr==0x52c3
			) {
			returnVal=TRUE;
		}
		break;
		case 0x79b6:
			if (
				src_addr==0x5890||
				src_addr==0x76e7
			) {
			returnVal=TRUE;
		}
		break;
		case 0x62b9:
			if (
				src_addr==0x5890
			) {
			returnVal=TRUE;
		}
		break;
		case 0xf078:
			if (
				src_addr==0xf361||
				src_addr==0x4baa||
				src_addr==0xc006
			) {
			returnVal=TRUE;
		}
		break;
		case 0x5517:
			if (
				src_addr==0x81fc
			) {
			returnVal=TRUE;
		}
		break;
		case 0x52c3:
			if (
				src_addr==0x209c
			) {
			returnVal=TRUE;
		}
		break;
		case 0x4baa:
			if (
				src_addr==0xf078
			) {
			returnVal=TRUE;
		}
		break;
		case 0x76e7:
			if (
				src_addr==0x79b6||
				src_addr==0x41c9
			) {
			returnVal=TRUE;
		}
		break;
		case 0xcdeb:
			if (
				src_addr==0x619e||
				src_addr==0x1d33
			) {
			returnVal=TRUE;
		}
		break;
		case 0x81fc:
			if (
				src_addr==0x4ffa||
				src_addr==0x5517||
				src_addr==0x4d6a||
				src_addr==0x7233||
				src_addr==0x46a3
			) {
			returnVal=TRUE;
		}
		break;
		case 0x53b8:
			if (
				src_addr==0x619e||
				src_addr==0xe886
			) {
			returnVal=TRUE;
		}
		break;
		case 0x1d33:
			if (
				src_addr==0xcdeb
			) {
			returnVal=TRUE;
		}
		break;
		case 0x4d6a:
			if (
				src_addr==0x81fc||
				src_addr==0xe61f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x7233:
			if (
				src_addr==0x81fc
			) {
			returnVal=TRUE;
		}
		break;
		case 0x4527:
			if (
				src_addr==0x619e
			) {
			returnVal=TRUE;
		}
		break;
		case 0x46a3:
			if (
				src_addr==0x81fc
			) {
			returnVal=TRUE;
		}
		break;
		case 0xfcaf:
			if (
				src_addr==0xcf11||
				src_addr==0x823d||
				src_addr==0xb6c8||
				src_addr==0x4d05||
				src_addr==0x667e
			) {
			returnVal=TRUE;
		}
		break;
		case 0x4da3:
			if (
				src_addr==0x6300||
				src_addr==0x44ea
			) {
			returnVal=TRUE;
		}
		break;
		case 0x41c9:
			if (
				src_addr==0x76e7
			) {
			returnVal=TRUE;
		}
		break;
		case 0xc006:
			if (
				src_addr==0xf078||
				src_addr==0x7f43
			) {
			returnVal=TRUE;
		}
		break;
		case 0x44ea:
			if (
				src_addr==0x4da3
			) {
			returnVal=TRUE;
		}
		break;
		case 0xe886:
			if (
				src_addr==0x53b8||
				src_addr==0x510e
			) {
			returnVal=TRUE;
		}
		break;
		case 0x823d:
			if (
				src_addr==0xfcaf
			) {
			returnVal=TRUE;
		}
		break;
		case 0x510e:
			if (
				src_addr==0xe886
			) {
			returnVal=TRUE;
		}
		break;
		case 0xb6c8:
			if (
				src_addr==0xfcaf
			) {
			returnVal=TRUE;
		}
		break;
		case 0x4d05:
			if (
				src_addr==0xfcaf
			) {
			returnVal=TRUE;
		}
		break;
		case 0xe61f:
			if (
				src_addr==0x4d6a
			) {
			returnVal=TRUE;
		}
		break;
		case 0x667e:
			if (
				src_addr==0xfcaf
			) {
			returnVal=TRUE;
		}
		break;
		case 0x7f43:
			if (
				src_addr==0xc006
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
