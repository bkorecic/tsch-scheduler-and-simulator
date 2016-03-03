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
		case 0x0001:
			if (
				src_addr==0x0002||
				src_addr==0x0003||
				src_addr==0x0004||
				src_addr==0x0005||
				src_addr==0x0006||
				src_addr==0x0007||
				src_addr==0x0008||
				src_addr==0x0009||
				src_addr==0x000a||
				src_addr==0x000c||
				src_addr==0x000d||
				src_addr==0x000e
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0002:
			if (
				src_addr==0x0001||
				src_addr==0x000b
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0003:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0004:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0005:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0006:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0007:
			if (
				src_addr==0x0001||
				src_addr==0x0015
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0008:
			if (
				src_addr==0x0001||
				src_addr==0x001a||
				src_addr==0x0014
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0009:
			if (
				src_addr==0x0001||
				src_addr==0x001c||
				src_addr==0x0016
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000a:
			if (
				src_addr==0x0001||
				src_addr==0x000f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000b:
			if (
				src_addr==0x0002||
				src_addr==0x001d
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000c:
			if (
				src_addr==0x0001||
				src_addr==0x0011
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000d:
			if (
				src_addr==0x0001||
				src_addr==0x0013
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000e:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000f:
			if (
				src_addr==0x000a||
				src_addr==0x0012
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0010:
			if (
				src_addr==0x0015
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0011:
			if (
				src_addr==0x000c
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0012:
			if (
				src_addr==0x000f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0013:
			if (
				src_addr==0x000d||
				src_addr==0x001e
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0014:
			if (
				src_addr==0x0008||
				src_addr==0x0017
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0015:
			if (
				src_addr==0x0007||
				src_addr==0x0010||
				src_addr==0x0018||
				src_addr==0x001b
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0016:
			if (
				src_addr==0x0009||
				src_addr==0x0019
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0017:
			if (
				src_addr==0x0014
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0018:
			if (
				src_addr==0x0015
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0019:
			if (
				src_addr==0x0016
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001a:
			if (
				src_addr==0x0008
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001b:
			if (
				src_addr==0x0015
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001c:
			if (
				src_addr==0x0009
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001d:
			if (
				src_addr==0x000b
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001e:
			if (
				src_addr==0x0013
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
