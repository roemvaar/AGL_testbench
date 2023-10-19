import can
import kuksa_viss_client

can_bus = can.interface.Bus("can0", bustype='socketcan')


def main():
    config = {}
    kuksa_client = kuksa_viss_client.KuksaClientThread(config)
    # Pass the license files

    # Start the client thread to connect with configuration
    kuksa_client.start()

    # Send commands here
    while True:
        message = can_bus.recv()

        # Switch case with corresponding message
        if (message.can_id == 0x101):
            print("Known Command 1\n")
            # update vehicle speed

        elif (message.can_id == 0x102):
            print("Known Command 2\n")
            # update another dashboard variable

        elif (message.can_id == 0x103):
            print("Known Command 3\n")
 
        elif (message.can_id == 0x104):
            print("Known Command 4\n")
 
        elif (message.can_id == 0x106):
            print("Known Command 5\n")
 
        elif (message.can_id == 0x107):
            print("Known Command 6\n")
 
        elif (message.can_id == 0x108):
            print("Known Command 7\n")
 
        elif (message.can_id == 0x109):
            print("Known Command 8\n")


    # Close the connection and stop the client thread
    kuksa_client.stop()


if __name__ == '__main__':
    main()
