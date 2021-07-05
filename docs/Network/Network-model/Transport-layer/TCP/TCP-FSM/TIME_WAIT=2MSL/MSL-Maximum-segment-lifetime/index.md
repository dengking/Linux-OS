# Maximum segment lifetime

一、2 `*` MSL 正好是一个来回

## wikipedia [Maximum segment lifetime](https://en.wikipedia.org/wiki/Maximum_segment_lifetime)

**Maximum segment lifetime** is the time a [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) [segment](https://en.wikipedia.org/wiki/Protocol_data_unit) can exist in the [internetwork](https://en.wikipedia.org/wiki/Internetworking) system. It is arbitrarily defined to be 2 minutes long.[[1\]](https://en.wikipedia.org/wiki/Maximum_segment_lifetime#cite_note-1)

The Maximum Segment Lifetime value is used to determine the TIME_WAIT interval (2*MSL)

The command that can be used on many Unix systems to determine the TIME_WAIT interval is:

```shell
   ndd -get /dev/tcp tcp_time_wait_interval
```

60000 (60 seconds) is a common value.

On [FreeBSD](https://en.wanweibaike.com/wiki-FreeBSD) systems this description and value can be checked by the command [sysctl](https://en.wanweibaike.com/wiki-Sysctl):[[2\]](https://en.wanweibaike.com/wiki-Maximum segment lifetime#cite_note-2)

```shell
   sysctl -d net.inet.tcp.msl
   sysctl net.inet.tcp.msl
```

which gets the result:

```shell
   net.inet.tcp.msl: Maximum segment lifetime
   net.inet.tcp.msl: 30000
```

On some Linux systems, this value can be checked by either of the commands below:

```shell
   sysctl net.ipv4.tcp_fin_timeout
   cat /proc/sys/net/ipv4/tcp_fin_timeout
```



## stackoverflow [What is Maximum Segment Lifetime (MSL) in TCP? [closed]](https://stackoverflow.com/questions/289194/what-is-maximum-segment-lifetime-msl-in-tcp)



A

The MSL (Maximum Segment Lifetime) is the longest time (in seconds) that a TCP segment is expected to exist in the network. It most notably comes into play during the closing of a TCP connection -- between the CLOSE_WAIT and CLOSED state, the machine waits 2 MSL's (conceptually a round trip to the end of the internet and back) for any late packets. During this time, the machine is holding resources for the mostly-closed connection. If a server is busy, then the resources held this way can become an issue. One "fix" is to lower the MSL so that they are released sooner. Generally this works OK, but occasionally it can cause confusing failure scenarios.

On Linux *(RHEL anyway, which is what I am familiar with)*, the "variable" `/proc/sys/net/ipv4/tcp_fin_timeout` is the 2*MSL value. It is normally 60 (seconds). To see it, do:

```
cat /proc/sys/net/ipv4/tcp_fin_timeout
```

To change it, do something like:

```
echo 5 > /proc/sys/net/ipv4/tcp_fin_timeout
```

Here is a TCP STATE DIAGRAM. You can find the wait in question at the bottom.
