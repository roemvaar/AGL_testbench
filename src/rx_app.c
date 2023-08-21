#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>


int main(int argc, char *argv[])
{
	int s;
	int i;
	int n_bytes;
	struct sockaddr_can address;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Demo - Receive\n");

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "vcan0");
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&address, 0, sizeof(address));
	address.can_family = AF_CAN;
	address.can_ifindex = ifr.ifr_ifindex;
	if (bind(s, (struct sockaddr *)&address, sizeof(address))) {
		perror("Bind");
		return 1;
	}

	while(1) {
		n_bytes = read(s, &frame, sizeof(struct can_frame));

		if (n_bytes < 0) {
			perror("Read");
			return 1;
		}

        canid_t can_id = frame.can_id;

		switch(can_id) {
			case 0x101:
				printf("Known Command 1\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x102:
				printf("Known Command 2\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x103:
				printf("Known Command 3\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x104:
				printf("Known Command 4\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x106:
				printf("Known Command 5\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x107:
				printf("Known Command 6\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x108:
				printf("Known Command 7\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x109:
				printf("Known Command 8\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x113:
				printf("Known Command 9\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x114:
				printf("Known Command 10\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x125:
				printf("Known Command 11\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x157:
				printf("Known Command 12\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x159:
				printf("Known Command 13\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x167:
				printf("Known Command 14\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x172:
				printf("Known Command 15\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x182:
				printf("Known Command 16\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x183:
				printf("Known Command 17\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x184:
				printf("Known Command 18\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x185:
				printf("Known Command 19\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x187:
				printf("Known Command 20\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x189:
				printf("Known Command 21\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x192:
				printf("Known Command 22\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x195:
				printf("Known Command 23\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x198:
				printf("Known Command 24\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x200:
				printf("Known Command 25\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x201:
				printf("Known Command 26\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x203:
				printf("Known Command 27\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x204:
				printf("Known Command 28\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x209:
				printf("Known Command 29\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x212:
				printf("Known Command 30\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x234:
				printf("Known Command 31\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x237:
				printf("Known Command 32\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x239:
				printf("Known Command 33\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x248:
				printf("Known Command 34\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x249:
				printf("Known Command 35\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x253:
				printf("Known Command 36\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x254:
				printf("Known Command 37\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x255:
				printf("Known Command 38\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x256:
				printf("Known Command 39\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x257:
				printf("Known Command 40\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x258:
				printf("Proxy: 1\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x452:
				printf("Proxy: 2\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x453:
				printf("Proxy: 3\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x554:
				printf("Non-memory operation: 1\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x555:
				printf("Non-memory operation: 5\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x556:
				printf("Non-memory operation: 10\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x557:
				printf("Non-memory operation: 100\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x558:
				printf("Non-memory operation: 1000\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x654:
				printf("Memory operation: 1\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x655:
				printf("Memory operation: 5\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x656:
				printf("Memory operation: 10\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x657:
				printf("Memory operation: 100\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x658:
				printf("Memory operation: 1000\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x754:
				printf("Flash operation: 1\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x755:
				printf("Flash operation: 5\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x756:
				printf("Flash operation: 10\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x757:
				printf("Flash operation: 100\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			case 0x758:
				printf("Flash operation: 1000\n");
				printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);
				printf("\r\n");
				break;
			default:
				break;
		}
	}

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
