# tcpdump

## opensource [An introduction to using tcpdump at the Linux command line](https://opensource.com/article/18/10/introduction-tcpdump)

Tcpdump is a command line utility that allows you to capture and analyze **network traffic** going through your system. It is often used to help troubleshoot network issues, as well as a security tool.

> NOTE: network traffic即 “网络通信”

### 2. Capturing packets with tcpdump

To begin, use the command `tcpdump --list-interfaces `(or `-D` for short) to see which interfaces are available for capture:

```shell
$ sudo tcpdump -D
1.eth0
2.virbr0
3.eth1
4.any (Pseudo-device that captures on all interfaces)
5.lo [Loopback]
```

In the example above, you can see all the interfaces available in my machine. The special interface `any` allows capturing in any active interface.

> NOTE: 

Let's use it to start capturing some packets. Capture all packets in any **interface** by running this command:

```shell
tcpdump --interface any
```

> NOTE: 原文给出的command是

## [tcpdump](https://www.tcpdump.org/)

```shell
tcpdump -i any port 11507 or port 11508 or port 11510 -s 0 -w front-arb1.pcap
```







## wikipedia [tcpdump](https://en.wikipedia.org/wiki/Tcpdump)





## wikipedia [pcap](https://en.wikipedia.org/wiki/Pcap)

