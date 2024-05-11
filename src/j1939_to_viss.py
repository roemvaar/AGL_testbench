import socket
import struct
import kuksa_viss_client
import can
import cantools


def process_can_message(msg):
    if msg.arbitration_id == 150892286:
        # vehicle_speed = int.from_bytes(msg.data, byteorder='big') # TODO: check byteorder, check the arbitration_id, these are arbitrary
        print(f"CAN ID: Electronic Engine Controller 1")
    elif msg.arbitration_id == 0x102:
        # Handle other CAN IDs and data decoding here
        pass
    else:
        print(f"Unknown CAN ID")


def alter_message(msg):
    msg_new = (msg & 0xFFFFFFFFFFFF00) | 0xFE
    msg_new = msg_new & (0x3FFFFFFF)

    return msg_new


def main():
    print("CAN Sockets Demo - Receive")
    s = socket.socket(socket.AF_CAN, socket.SOCK_RAW, socket.CAN_RAW)
    dbc = cantools.database.load_file('CSS-Electronics-SAE-J1939-2020-03_v1.1.dbc')
    print("Load SAE-J1939 DBC file... done!")

    client = kuksa_viss_client.KuksaClientThread(config={})
    client.start()
    client.authorize("/usr/lib/python3.10/site-packages/kuksa_certificates/jwt/super-admin.json.token")
    print("Kuksa Client init... done!")
    print("Configuration done... ready to handle CAN messages!")

    try:
        s.bind(('vcan0',))
    except OSError as e:
        print(f"Bind error: {e}")
        return 1

    print("-------------------------------------------------------------------")

    while (1):
        try:
            frame = s.recv(64)
        except OSError as e:
            print(f"Read error: {e}")
            return 1

        can_id, can_dlc, data = struct.unpack("<IB3x8s", frame)

        # print(f"0x{can_id:03X} [{can_dlc}] ", end="")

        # Decode the received frame using python-can
        msg = can.Message(
            arbitration_id=can_id,
            data=data,
            dlc=can_dlc,
            is_extended_id=True  # Assuming standard CAN frames
        )

        # Call the message processing function
        # process_can_message(msg)

        # print(f"Arbitration ID received: {msg.arbitration_id}")

        msg_new = alter_message(msg.arbitration_id)
        msg_pgn = (msg.arbitration_id >> 8) & 0x3FFFF #gets 18 bytes

        try:
            if((msg_pgn == 65265) or (msg_pgn == 65248) or (msg_pgn == 0xFEFC)):
                dictionary = dbc.decode_message(msg_new, msg.data)
                for key, value in dictionary.items():
                    print(f"{key}: {value}")
                    if key == "WheelBasedVehicleSpeed":
                        wheelBasedVehicleSpeed = value
                    elif key == "TotalVehicleDistance":
                        odometerDistance = value
                    elif key == "FuelLevel1":
                        fuel_level = value
                        # # print(fuel_level, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
                        # client.setValue("Vehicle.Powertrain.FuelSystem.Level", str(value)) # TODO: Change v_temp for the correct vehicle speed coming on the SPN
                        # print("Received: Vehicle.Powertrain.FuelSystem.Level")

                print("-------------------------------------------------------------------")

        except KeyError:
            print("received error")
            # continue

        # Command handler
        if msg_pgn == 0xFEF1:
            client.setValue("Vehicle.Speed", str(wheelBasedVehicleSpeed))
            print("Received: Vehicle.Speed")
        elif msg_pgn == 0xFEE0:
            client.setValue("Vehicle.TravelledDistance", str(odometerDistance))
            print("Received: Vehicle.TravelledDistance")
        elif msg_pgn == 0xFEFC:
            client.setValue("Vehicle.Powertrain.FuelSystem.Level", str(fuel_level))
            print("Received: Vehicle.Powertrain.FuelSystem.Level")
        elif msg_pgn == 0xFFFE: # TODO: Update PGN to correct value
            client.setValue("Vehicle.Powertrain.FuelSystem.Range", str(v_temp)) # TODO: Change v_temp for the correct vehicle speed coming on the SPN
            print("Received: Vehicle.Powertrain.FuelSystem.Range")
        elif msg_pgn == 0xFFFD: # TODO: Update PGN to correct value
            client.setValue("Vehicle.Powertrain.CombustionEngine.Speed", str(v_temp)) # TODO: Change v_temp for the correct vehicle speed coming on the SPN
            print("Received: Vehicle.Powertrain.CombustionEngine.Speed")    #RPM

    client.stop()


if __name__ == "__main__":
    main()
