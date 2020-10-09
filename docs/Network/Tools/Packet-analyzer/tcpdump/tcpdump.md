# tcpdump



```shell
tcpdump -i any port 11507 or port 11508 or port 11510 -s 0 -w front-arb1.pcap
```

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

## official website: [tcpdump](https://www.tcpdump.org/)



## wikipedia [tcpdump](https://en.wikipedia.org/wiki/Tcpdump)



## [man 1 tcpdump](https://www.tcpdump.org/manpages/tcpdump.1.html)







## Parse pcap file

`tcpdump`是可以直接parse pcap file的，参见下面这些文章：

serverfault [How can I read pcap files in a friendly format?](https://serverfault.com/questions/38626/how-can-i-read-pcap-files-in-a-friendly-format) :

```shell
tcpdump -ttttnnr tcp_dump.pcap
```



```shell
tcpdump -qns 0 -A -r blah.pcap
```



```shell
tcpick -C -yP -r tcp_dump.pcap
```



[A](https://serverfault.com/a/38632)

Wireshark is probably the best, but if you want/need to look at the payload without loading up a GUI you can use the `-X` or `-A` options

```shell
tcpdump -qns 0 -X -r serverfault_request.pcap
```



```shell
tcpdump -qns 0 -A -r serverfault_request.pcap
```

There are many other tools for reading and getting stats, extracting payloads and so on. A quick look on the number of things that depend on libpcap in the debian package repository gives a list of 50+ tools that can be used to slice, dice, view, and manipulate captures in various ways.

For example.

- [tcpick](http://tcpick.sourceforge.net/)
- [tcpxtract](http://tcpxtract.sourceforge.net/)



[A](https://serverfault.com/a/46625)

```shell
tshark -r file.pcap -V
```



[A](https://serverfault.com/a/38633)

You can use **wireshark** which is a gui app or you can use **tshark** which is it's cli counterpart.

Besides, you can visualize the pcap using several visualization tools:

- **[tnv](http://tnv.sourceforge.net/)** - The Network Visualizer or Time-based Network Visualizer
- **[afterglow](http://afterglow.sourceforge.net/)** - A collection of scripts which facilitate the process of generating graphs
- **[INAV](http://inav.scaparra.com/about/abstract/)** - Interactive Network Active-traffic Visualization

If you want to analyze the pcap file you can use the excelent **[nsm-console](http://writequit.org/projects/nsm-console/)**.

Last, but not least, you can upload your pcap to pcapr.net and watch it there. pcapr.net is a kind of social website to analyze and comment to traffic captures.





