import can

# bus1 = can.interface.Bus('test', interface='virtual', preserve_timestamps=True)
# bus2 = can.interface.Bus('test', interface='virtual')
bus1 = can.interface.Bus('socketcan', interface='vcan0', preserve_timestamps=True)
bus2 = can.interface.Bus('socketcan', interface='vcan0')

msg1 = can.Message(timestamp=1639740470.051948, arbitration_id=0xabcde, data=[1,2,3])
print(msg1)

# Messages sent on bus1 will have their timestamps preserved when received
# on bus2
bus1.send(msg1)
msg2 = bus2.recv()
print(msg2)

assert msg1.arbitration_id == msg2.arbitration_id
assert msg1.data == msg2.data
assert msg1.timestamp == msg2.timestamp

# Messages sent on bus2 will not have their timestamps preserverd when
# received on bus1
bus2.send(msg1)
msg3 = bus1.recv()
print(msg3)

assert msg1.arbitration_id == msg3.arbitration_id
assert msg1.data == msg3.data
assert msg1.timestamp != msg3.timestamp
