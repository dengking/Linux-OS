# [IP(7)](http://man7.org/linux/man-pages/man7/ip.7.html)

## NAME
ip - Linux IPv4 protocol implementation

## SYNOPSIS

```C
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <netinet/ip.h> /* superset of previous */

   tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
   udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
   raw_socket = socket(AF_INET, SOCK_RAW, protocol);
```
## DESCRIPTION

Linux implements the [Internet Protocol](https://en.wikipedia.org/wiki/Internet_Protocol), version 4, described in RFC 791 and RFC 1122.  **ip** contains a level 2 multicasting implementation conforming to RFC 1112.  It also contains an IP router including a packet filter.

The programming interface is BSD-sockets compatible.  For more information on sockets, see socket(7).

