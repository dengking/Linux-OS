# [socket(2)](https://www.man7.org/linux/man-pages/man2/socket.2.html)

`socket` - create an endpoint for communication

```C
       #include <sys/socket.h>

       int socket(int domain, int type, int protocol);
```



## `domain`(protocol family)

The `domain` argument specifies a communication domain; this selects the protocol family which will be used for communication.  These families are defined in `<sys/socket.h>`.  The formats currently understood by the Linux kernel include:

|            |                         |                                                              |
| ---------- | ----------------------- | ------------------------------------------------------------ |
| `AF_UNIX`  | Local communication     | [unix(7)](https://www.man7.org/linux/man-pages/man7/unix.7.html) |
| `AF_INET`  | IPv4 Internet protocols | [ip(7)](https://www.man7.org/linux/man-pages/man7/ip.7.html) |
| `AF_INET6` | IPv6 Internet protocols | [ipv6(7)](https://www.man7.org/linux/man-pages/man7/ipv6.7.html) |

Further details of the above address families, as well as information on several other address families, can be found in [address_families(7)](https://www.man7.org/linux/man-pages/man7/address_families.7.html).

> NOTE: 
>
> `AF***` 中的`AF` 是**address family**的缩写。
>
> 思考: **address family**的含义是什么？
>
> 看了 `AF_INET`      [ip(7)](https://www.man7.org/linux/man-pages/man7/ip.7.html)、`AF_INET6`     [ipv6(7)](https://www.man7.org/linux/man-pages/man7/ipv6.7.html)，我的想法是: 地址。

## `type`

The socket has the indicated type, which specifies the communication semantics.  Currently defined types are:

### `SOCK_STREAM`

> TCP

### `SOCK_DGRAM`

> UDP

### `SOCK_SEQPACKET`



### `SOCK_RAW`



## `protocol` 

The `protocol` specifies a particular protocol to be used with the socket.  

Normally only a single protocol exists to support a particular socket type within a given protocol family, in which case protocol can be specified as 0.  

> NOTE: 
>
> 一一对应关系

However, it is possible that many protocols may exist, in which case a particular protocol must be specified in this manner.  The **protocol number** to use is specific to the “communication domain” in which communication is to take place; see [protocols(5)](https://www.man7.org/linux/man-pages/man5/protocols.5.html).  See [getprotoent(3](https://www.man7.org/linux/man-pages/man3/getprotoent.3.html)) on how to map protocol name strings to protocol numbers.





## Sockets of type `SOCK_STREAM`

[connect(2)](https://www.man7.org/linux/man-pages/man2/connect.2.html)

[read(2)](https://www.man7.org/linux/man-pages/man2/read.2.html)  [recv(2)](https://www.man7.org/linux/man-pages/man2/recv.2.html) 

[write(2)](https://www.man7.org/linux/man-pages/man2/write.2.html) [send(2)](https://www.man7.org/linux/man-pages/man2/send.2.html) 

### Out-of-band data

Out-of-band data may also be transmitted as described in send(2) and received as described in recv(2).



### `SO_KEEPALIVE` 

When `SO_KEEPALIVE` is enabled on the socket the protocol checks in a protocol-specific manner if the other end is still alive.

### `SIGPIPE` signal

A `SIGPIPE` signal is raised if a process sends or receives on a broken stream; this causes naive processes, which do not handle the signal, to exit.

> NOTE: 
>
> 一般，对于这个signal，都是 ，比如`SIG_IGN`
>
> tag-Redis Signal Handle-signal disposition-`signal(SIGPIPE, SIG_IGN)`

## Sockets of type `SOCK_SEQPACKET` 

`SOCK_SEQPACKET` sockets employ the same system calls as `SOCK_STREAM` sockets.  The only difference is that read(2) calls will return only the amount of data requested, and any data remaining in the arriving packet will be discarded.  Also all message boundaries in incoming datagrams are preserved.

## Sockets of type `SOCK_DGRAM` and `SOCK_RAW` 

[sendto(2)](https://www.man7.org/linux/man-pages/man2/sendto.2.html) 

[recvfrom(2)](https://www.man7.org/linux/man-pages/man2/recvfrom.2.html)



## Socket signals

An `fcntl(2)` `F_SETOWN` operation can be used to specify a process or process group to receive a `SIGURG` signal when the out-of-band data arrives or `SIGPIPE` signal when a `SOCK_STREAM` connection breaks unexpectedly.  This operation may also be used to set the process or process group that receives the I/O and asynchronous notification of I/O events via `SIGIO`.  Using `F_SETOWN` is equivalent to an ioctl(2) call with the `FIOSETOWN` or `SIOCSPGRP` argument.

## Operation of sockets 

The operation of sockets is controlled by socket level options. These options are defined in <sys/socket.h>.  The functions `setsockopt(2)` and `getsockopt(2)` are used to set and get options.