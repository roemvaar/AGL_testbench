import socket
import struct
import array
import kuksa_viss_client
import can
import cantools


def main():
    print("CAN Sockets Demo - Receive")
    s = socket.socket(socket.AF_CAN, socket.SOCK_RAW, socket.CAN_RAW)
    client = kuksa_viss_client.KuksaClientThread(config={})
    client.start()
    auth = False
    print("Kuksa Client init... done!")

    try:
        s.bind(('vcan0',))
    except OSError as e:
        print(f"Bind error: {e}")
        return 1
    print("Connected to vcan0 bus... done!")

    while True:
        try:
            frame = s.recv(16)
        except OSError as e:
            print(f"Read error: {e}")
            return 1

        can_id, can_dlc, data = struct.unpack("<IB3x8s", frame)
        
        print(f"0x{can_id:03X} [{can_dlc}] ", end="")

        # Decode the received frame using python-can
        msg = can.Message(
            arbitration_id=can_id,
            data=data,
            dlc=can_dlc,
            is_extended_id=False  # Assuming standard CAN frames
        )

        # Get the initial value from the Kuksa server
        # print(client.getValue("Vehicle.Speed"))

        if can_id == 0x101:
            print("Known Command 1")
        elif can_id == 0x102:
            print("Known Command 2")
        elif can_id == 0x103:
            print("Known Command 3")
        elif can_id == 0x104:
            print("Known Command 4")
        elif can_id == 0x106:
            print("Known Command 5")
        elif can_id == 0x107:
            print("Known Command 6")
        elif can_id == 0x108:
            print("Known Command 7")
        elif can_id == 0x109:
            print("Known Command 8")
        elif can_id == 0x113:
            print("Known Command 9")
        elif can_id == 0x114:
            print("Known Command 10")
        elif can_id == 0x125:
            print("Known Command 11")
        elif can_id == 0x157:
            print("Known Command 12")
        elif can_id == 0x159:
            print("Known Command 13")
        elif can_id == 0x167:
            print("Known Command 14")
        elif can_id == 0x172:
            print("Known Command 15")
        elif can_id == 0x182:
            print("Known Command 16")
        elif can_id == 0x183:
            print("Known Command 17")
        elif can_id == 0x184:
            print("Known Command 18")
        elif can_id == 0x185:
            print("Known Command 19")
        elif can_id == 0x187:
            print("Known Command 20")
        elif can_id == 0x189:
            print("Known Command 21")
        elif can_id == 0x192:
            print("Known Command 22")
        elif can_id == 0x195:
            print("Known Command 23")
        elif can_id == 0x198:
            print("Known Command 24")
        elif can_id == 0x200:
            print("Known Command 25")
        elif can_id == 0x201:
            print("Known Command 26")
        elif can_id == 0x203:
            print("Known Command 27")
        elif can_id == 0x204:
            print("Known Command 28")
        elif can_id == 0x209:
            print("Known Command 29")
        elif can_id == 0x212:
            print("Known Command 30")
        elif can_id == 0x234:
            print("Known Command 31")
        elif can_id == 0x237:
            print("Known Command 32")
        elif can_id == 0x239:
            print("Known Command 33")
        elif can_id == 0x248:
            print("Known Command 34")
        elif can_id == 0x249:
            print("Known Command 35")
        elif can_id == 0x253:
            print("Known Command 36")
        elif can_id == 0x254:
            print("Known Command 37")
        elif can_id == 0x255:
            print("Known Command 38")
        elif can_id == 0x256:
            print("Known Command 39")
        elif can_id == 0x257:
            print("Known Command 40")
        elif can_id == 0x258:
            print("Proxy: 1")
        elif can_id == 0x452:
            print("Proxy: 2")
        elif can_id == 0x453:
            print("Proxy: 3")
        elif can_id == 0x554:
            print("Non-memory operation: 1")
        elif can_id == 0x555:
            print("Non-memory operation: 5")
        elif can_id == 0x556:
            print("Non-memory operation: 10")
        elif can_id == 0x557:
            print("Non-memory operation: 100")
        elif can_id == 0x558:
            print("Non-memory operation: 1000")
        elif can_id == 0x654:
            print("Memory operation: 1")
        elif can_id == 0x655:
            print("Memory operation: 5")
        elif can_id == 0x656:
            print("Memory operation: 10")
        elif can_id == 0x657:
            print("Memory operation: 100")
        elif can_id == 0x658:
            print("Memory operation: 1000")
        elif can_id == 0x754:
            print("Flash operation: 1")
        elif can_id == 0x755:
            print("Flash operation: 5")
        elif can_id == 0x756:
            print("Flash operation: 10")
        elif can_id == 0x757:
            print("Flash operation: 100")
        elif can_id == 0x758:
            print("Flash operation: 1000")
        elif can_id == 0x763:
            print("Update vehicle speed... ", end='')

            if auth:
                client.setValue("Vehicle.Speed", "36")
                print("success")
            else:
                print("failed. Unauthorized!")

        elif can_id == 0x821:
            print("Knock 1...")
        elif can_id == 0x825:
            print("Knock 2...")
        elif can_id == 0x833:
            print("Knock 3... Root (write) permissions granted!")
            client.authorize("/usr/lib/python3.10/site-packages/kuksa_certificates/jwt/super-admin.json.token")
            auth = True
            # print(client.getValue("Vehicle.Speed"))
        else:
            print("Unknown Command")

    # Stop the client's thread when done
    client.stop()


if __name__ == "__main__":
    main()
