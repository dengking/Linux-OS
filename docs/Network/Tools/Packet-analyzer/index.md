# Packet analyzer

在开发与网络相关的application的时候，使用包分析工具是一种非常快速的排查方法，尤其是抓包工具。

## wikipedia [Packet analyzer](https://en.wikipedia.org/wiki/Packet_analyzer)

> NOTE: 包分析工具

A **packet analyzer** or **packet sniffer** is a [computer program](https://en.wikipedia.org/wiki/Computer_program), or [computer hardware](https://en.wikipedia.org/wiki/Computer_hardware) such as a [packet capture appliance](https://en.wikipedia.org/wiki/Packet_capture_appliance), that can intercept and log traffic that passes over a [computer network](https://en.wikipedia.org/wiki/Computer_network) or part of a network.

### Notable packet analyzers

*For a more comprehensive list, see* [Comparison of packet analyzers](https://en.wikipedia.org/wiki/Comparison_of_packet_analyzers)*.*

> NOTE: 原文给出了比较好的总结，可以作为后续寻找工具的入口



## Packet capture

Packet capture即抓包，它是最最常见的一种packet analysis方式，本节对它进行描述。

### wikipedia [Packet capture appliance](https://en.wikipedia.org/wiki/Packet_capture_appliance)

> NOTE: appliance的意思是 设备





### wikipedia [pcap](https://en.wikipedia.org/wiki/Pcap)

> NOTE: 非常重要的API，很多的tool都是在它的基础上创建的

In the field of [computer](https://en.wikipedia.org/wiki/Computer) [network administration](https://en.wikipedia.org/wiki/Network_administration), **pcap** is an [application programming interface](https://en.wikipedia.org/wiki/Application_programming_interface) (API) for [capturing network traffic](https://en.wikipedia.org/wiki/Packet_sniffer). 

| OS                                                           | implementation                                               |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems | [*libpcap* library](https://github.com/the-tcpdump-group/libpcap) |
| [Windows](https://en.wikipedia.org/wiki/Microsoft_Windows)   | *Npcap* for [Windows 7](https://en.wikipedia.org/wiki/Windows_7) |





> NOTE: how to parse 



#### Programs that use libpcap

> NOTE: 下面是目前我接触过的工具

- [ngrep](https://en.wikipedia.org/wiki/Ngrep)
- [Wireshark](https://en.wikipedia.org/wiki/Wireshark)
- [tcpdump](https://en.wikipedia.org/wiki/Tcpdump)



### pcap file

pcap file是抓包的产物，如何来分析呢？

正如wikipedia [pcap](https://en.wikipedia.org/wiki/Pcap)中所述: 

> A capture file saved in the format that libpcap, WinPcap, and Npcap use can be read by applications that understand that format, such as [tcpdump](https://en.wikipedia.org/wiki/Tcpdump), [Wireshark](https://en.wikipedia.org/wiki/Wireshark), [CA](https://en.wikipedia.org/wiki/CA,_Inc.) [NetMaster](https://en.wikipedia.org/w/index.php?title=NetMaster&action=edit&redlink=1), or [Microsoft Network Monitor](https://en.wikipedia.org/wiki/Microsoft_Network_Monitor) 3.x.

显然，上面提到的这些工具都可以解析，一般使用[Wireshark](https://en.wikipedia.org/wiki/Wireshark)来进行解析。如何使用[tcpdump](https://en.wikipedia.org/wiki/Tcpdump) 来解析呢？参见`Network\Tools\Packet-analyzer\tcpdump`。

