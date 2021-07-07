# Ephemeral port

一、"ephemeral port" 即 "临时端口"

二、ephemeral port range是一种system resource

三、可以认为: Linux中，每个socket都有一个对应的port:

server会bind到一个指定的port

client会被分配一个临时的port

四、参考文章:

1、wanweibaike [Ephemeral port](https://en.wanweibaike.com/wiki-Ephemeral%20port)

2、idea.popcount [Bind before connect](https://idea.popcount.org/2014-04-03-bind-before-connect/)

3、linuxperf [临时端口号(EPHEMERAL PORT)的动态分配](http://linuxperf.com/?p=178)

这篇文章，描述了kernel如何分配 ephemeral port

## wanweibaike [Ephemeral port](https://en.wanweibaike.com/wiki-Ephemeral%20port)

An **ephemeral port** is a short-lived transport protocol [port](https://en.wanweibaike.com/wiki-Port_number) for [Internet Protocol](https://en.wanweibaike.com/wiki-Internet_Protocol) (IP) communications. Ephemeral ports are allocated automatically from a predefined range by the [IP stack](https://en.wanweibaike.com/wiki-IP_stack) software. An ephemeral port is typically used by the [Transmission Control Protocol](https://en.wanweibaike.com/wiki-Transmission_Control_Protocol) (TCP), [User Datagram Protocol](https://en.wanweibaike.com/wiki-User_Datagram_Protocol) (UDP), or the [Stream Control Transmission Protocol](https://en.wanweibaike.com/wiki-Stream_Control_Transmission_Protocol) (SCTP) as the port assignment for the [client](https://en.wanweibaike.com/wiki-Client_(computing)) end of a [client–server](https://en.wanweibaike.com/wiki-Client–server) communication to a particular port (usually a *[well-known port](https://en.wanweibaike.com/wiki-Well-known_port)*) on a [server](https://en.wanweibaike.com/wiki-Server_(computing)).

On [servers](https://en.wanweibaike.com/wiki-Server_(computing)), ephemeral ports may also be used as the port assignment on the server end of a communication. This is done to continue communications with a client that initially connected to one of the server's well-known service listening ports. [File Transfer Protocol](https://en.wanweibaike.com/wiki-File_Transfer_Protocol) (FTP) and [Remote Procedure Call](https://en.wanweibaike.com/wiki-Remote_Procedure_Call) (RPC) applications are two protocols that can behave in this manner. Note that the term "server" here includes [workstations](https://en.wanweibaike.com/wiki-Workstation) running [network services](https://en.wanweibaike.com/wiki-Network_service) that receive connections initiated from other clients (e.g. [Remote Desktop Protocol](https://en.wanweibaike.com/wiki-Remote_Desktop_Protocol)).

The allocations are temporary and only valid for the duration of the communication session. After completion (or timeout) of the communication session, the ports become available for reuse.[[note 1\]](https://en.wanweibaike.com/wiki-Ephemeral port#cite_note-1) Since the ports are used on a per request basis they are also called **dynamic ports**.





## csdn [linux临时端口（port）以及最大值](https://blog.csdn.net/bdss58/article/details/78546551)

在一个Linux上跑一个服务，需要指定一个监听端口（系统调用listen），当client请求服务时，系统为该请求建立 tcp连接，该连接的port值是一个随机数字。该数字的取值范围配置在`/proc/sys/net/ipv4/ip_local_port_range` 文件中，我的机器上的内容如下：

```
32768   61000
```

**port的最大值其实可以达到65535（2^16 - 1)。**

65535这个数字与操作系统无关，不管Linux系统是32位的还是64位的。

**这个数字是由网络tcp协议决定的**，tcp协议头部中的16位表示端口号，这就决定了其最大值65535，操作系统只能跟着这个限制。
