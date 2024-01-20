# Development

## Connect to target

The first thing you need to do is to connect to the target from your
host computer. Here are the instructions on how to connect using the
different ways to do it.

### Connect using SSH

```
ssh root@192.168.1.119
```

You can confirm that you are connected correctly using `uname -a` and
you should see the following message.

```
Linux raspberrypi4-64 5.15.34-v8 #1 SMP PREEMPT Wed May 10 06:26:40 UTC 2023 aarch64 aarch64 aarch64 GNU/Linux
```

### Connect using SSH on VSCode

1. Install the `Remote - SSH` extension on VSCode
2. Click on the Status bar item at the far left
3. Select `Remote-SSH: Connect to Host...`
4. Input the user and IP address of the remote target

For detailed instructions read the [official documentation](https://code.visualstudio.com/docs/remote/ssh).

### CAN connection using KVaser adapter

## Remote development

After we get a connection, we can start performing
