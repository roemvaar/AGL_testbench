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
	struct sockaddr_can address;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Demo - Transmit\r\n");

	// Create a socket
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "vcan0");
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&address, 0, sizeof(address));
	address.can_family = AF_CAN;
	address.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Bind");
		return 1;
	}

	frame.can_id = 0x553;
	frame.can_dlc = 5;
	sprintf(frame.data, "Hello");

	for (int i = 0; i < 10; i++) {
		if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
			perror("Write");
			return 1;
		}

		frame.can_id += 1;

		sleep(1);
	}

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
