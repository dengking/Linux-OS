

# [IPV6(7)](http://man7.org/linux/man-pages/man7/ipv6.7.html)

## NAME

ipv6 - Linux IPv6 protocol implementation

## SYNOPSIS

```C
       #include <sys/socket.h>
       #include <netinet/in.h>

       tcp6_socket = socket(AF_INET6, SOCK_STREAM, 0);
       raw6_socket = socket(AF_INET6, SOCK_RAW, protocol);
       udp6_socket = socket(AF_INET6, SOCK_DGRAM, protocol);
```

