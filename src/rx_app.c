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
			case 0x451:
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
