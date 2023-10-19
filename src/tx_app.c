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

	strcpy(ifr.ifr_name, "can1");
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&address, 0, sizeof(address));
	address.can_family = AF_CAN;
	address.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Bind");
		return 1;
	}

	// frame.can_id = 0x553;
	frame.can_dlc = 5;
	sprintf(frame.data, "Hello");

	// canid_t known_commands[] = {}

	canid_t unknown_commands[] = {0x451, 0x452, 0x453, 0x554, 0x555, 0x556, 0x557, 0x558,
									0x654, 0x655, 0x656, 0x657, 0x658,
									0x754, 0x755, 0x756, 0x757, 0x758};

	for (int i = 0; i < 18; i++) {
		frame.can_id = unknown_commands[i];

		if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
			perror("Write");
			return 1;
		}

		sleep(3);
	}

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
