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
				src_addr==0x000b||
				src_addr==0x000c||
				src_addr==0x000d||
				src_addr==0x000e||
				src_addr==0x000f||
				src_addr==0x0011||
				src_addr==0x0013||
				src_addr==0x001d||
				src_addr==0x001f||
				src_addr==0x0020
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0002:
			if (
				src_addr==0x0001
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
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0008:
			if (
				src_addr==0x0001||
				src_addr==0x0016||
				src_addr==0x001a
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0009:
			if (
				src_addr==0x0001||
				src_addr==0x001b||
				src_addr==0x001c
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000a:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000b:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000c:
			if (
				src_addr==0x0001
			) {
			returnVal=TRUE;
		}
		break;
		case 0x000d:
			if (
				src_addr==0x0001||
				src_addr==0x0017
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
				src_addr==0x0001||
				src_addr==0x0015||
				src_addr==0x002b||
				src_addr==0x002d||
				src_addr==0x0031
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0010:
			if (
				src_addr==0x0020
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0011:
			if (
				src_addr==0x0001||
				src_addr==0x0018
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0012:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0013:
			if (
				src_addr==0x0001||
				src_addr==0x002f||
				src_addr==0x0014||
				src_addr==0x0019||
				src_addr==0x002e
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0014:
			if (
				src_addr==0x0013
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0015:
			if (
				src_addr==0x000f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0016:
			if (
				src_addr==0x0008
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0017:
			if (
				src_addr==0x000d
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0018:
			if (
				src_addr==0x0011
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0019:
			if (
				src_addr==0x0013
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
				src_addr==0x0009
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001c:
			if (
				src_addr==0x0009||
				src_addr==0x0032
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001d:
			if (
				src_addr==0x0001||
				src_addr==0x002a
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001e:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x001f:
			if (
				src_addr==0x0001||
				src_addr==0x0012||
				src_addr==0x001e||
				src_addr==0x0023||
				src_addr==0x0024||
				src_addr==0x0025||
				src_addr==0x0026||
				src_addr==0x0027||
				src_addr==0x0028||
				src_addr==0x0029
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0020:
			if (
				src_addr==0x0001||
				src_addr==0x0010||
				src_addr==0x0021||
				src_addr==0x0022
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0021:
			if (
				src_addr==0x0020
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0022:
			if (
				src_addr==0x0020
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0023:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0024:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0025:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0026:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0027:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0028:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0029:
			if (
				src_addr==0x001f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x002a:
			if (
				src_addr==0x001d
			) {
			returnVal=TRUE;
		}
		break;
		case 0x002b:
			if (
				src_addr==0x000f||
				src_addr==0x002c
			) {
			returnVal=TRUE;
		}
		break;
		case 0x002c:
			if (
				src_addr==0x002b
			) {
			returnVal=TRUE;
		}
		break;
		case 0x002d:
			if (
				src_addr==0x000f
			) {
			returnVal=TRUE;
		}
		break;
		case 0x002e:
			if (
				src_addr==0x0013
			) {
			returnVal=TRUE;
		}
		break;
		case 0x002f:
			if (
				src_addr==0x0013
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0030:
			if (
				src_addr==0x0031
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0031:
			if (
				src_addr==0x000f||
				src_addr==0x0030
			) {
			returnVal=TRUE;
		}
		break;
		case 0x0032:
			if (
				src_addr==0x001c
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
