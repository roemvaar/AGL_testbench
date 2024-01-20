# CAN

## Replay CAN truck data

```
$ canplayer -I <candump>.log
```

If the candump is from another can bus, you can
specify it to be the necessary bus with `can1=can0`, e.g,:

```
$ canplayer -I <candump>.log can1=can0
```
