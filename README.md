# CAN-examples

CAN Examples repository

## vcan

If you get the following error `Bind: no such device`,
is caused when the CAN device is not setup, in order to solve
this use the following commands.

```
$ sudo modprobe vcan
$ sudo ip link add dev vcan0 type vcan
$ sudo ip link set up vcan0
```

[Reference](https://stackoverflow.com/questions/21022749/how-to-create-virtual-can-port-on-linux-c)

## Build

```
$ gcc can_transmit.c -o can_tx
$ gcc can_receive.c -o can_rx
```

## Run

Terminal 1:

```
$ ./can_rx
```

Terminal 2:

```
$ ./can_tx
```

## CAN Dump

```
$ candump vcan0
```

## CAN / J1939

* https://www.csselectronics.com/pages/dbc-editor-can-bus-database

* Some scripts need a J1939 dbc on the `j1939` directory.
This dbc file can't be hosted on GitHub because of licensing.

## Copy files to and from target

For development, I usually do an ssh connection using VSCode.

Also, `scp` can be used to copy files from the host to the target
and vice versa, instructions [here](https://unix.stackexchange.com/questions/188285/how-to-copy-a-file-from-a-remote-server-to-a-local-machine).
