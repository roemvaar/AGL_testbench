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

	n_bytes = read(s, &frame, sizeof(struct can_frame));

	if (n_bytes < 0) {
		perror("Read");
		return 1;
	}

	printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);

	printf("\r\n");

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	while (1) {
		sleep(1);
	}

	return 0;
}

