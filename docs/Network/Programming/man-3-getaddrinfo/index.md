# [getaddrinfo(3)](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);

void freeaddrinfo(struct addrinfo *res);

const char *gai_strerror(int errcode);
```

> NOTE: : redis的`anet.h`模块中使用了该函数，可以作为example来参考，我的[redis-ae](https://github.com/dengking/redis-ae)中提供了注释版本的代码；

## Description

Given *node* and *service*, which identify an Internet host and a service, **getaddrinfo**() returns one or more *addrinfo* structures, each of which contains an Internet address that can be specified in a call to [**bind**(2)](https://linux.die.net/man/2/bind) or [**connect**(2)](https://linux.die.net/man/2/connect) . The **getaddrinfo**() function combines the functionality provided by the [**gethostbyname**(3)](https://linux.die.net/man/3/gethostbyname) and [**getservbyname**(3)](https://linux.die.net/man/3/getservbyname) functions into a single interface, but unlike the latter functions, **getaddrinfo**() is **reentrant** and allows programs to eliminate IPv4-versus-IPv6 dependencies.

> NOTE: : node往往是IP地址，server则是端口；
如果用于connect，则此时是指定server端的地址；
如果用于bind，则此时应该指定的是什么呢？
`getaddrinfo`的返回值是从何而来的？



The *addrinfo* structure used by **getaddrinfo**() contains the following fields:

```c
struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    socklen_t        ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};
```

The *hints* argument points to an *addrinfo* structure that specifies criteria for **selecting** the socket address structures returned in the list pointed to by *res*. If *hints* is not NULL it points to an *addrinfo* structure whose *ai_family*, *ai_socktype*, and *ai_protocol* specify criteria that limit the set of socket addresses returned by **getaddrinfo**(), as follows:

- ###  ai_family

This field specifies the desired **address family** for the returned addresses. Valid values for this field include **AF_INET** and **AF_INET6**. The value **AF_UNSPEC** indicates that **getaddrinfo**() should return socket addresses for any address family (either IPv4 or IPv6, for example) that can be used with *node* and *service*.

> NOTE: : address family从其名字可知与address相关，在目前的`TCP/IP`网络中，我们都是使用`IPv4` 或 `IPv6`网络；**AF_INET**即IPv4，**AF_INET6**即IPv6。



- ### ai_socktype

This field specifies the preferred socket type, for example **SOCK_STREAM** or **SOCK_DGRAM**. Specifying 0 in this field indicates that socket addresses of any type can be returned by **getaddrinfo**().

> NOTE: : *ai_socktype*和*ai_protocol*存在关系，但是和*ai_family*之间并没有关系；

- ### *ai_protocol*

This field specifies the protocol for the returned socket addresses. Specifying 0 in this field indicates that **socket addresses** with any protocol can be returned by **getaddrinfo**().



- ### *ai_flags*

This field specifies additional options, described below. Multiple flags are specified by bitwise OR-ing them together.



All the other fields in the structure pointed to by *hints* must contain either 0 or a NULL pointer, as appropriate. 

Specifying *hints* as NULL is equivalent to setting *`ai_socktype`* and *`ai_protocol`* to 0; *ai_family* to **AF_UNSPEC**; and *ai_flags* to **(AI_V4MAPPED | AI_ADDRCONFIG)**. *node* specifies either a **numerical network address** (for IPv4, numbers-and-dots notation as supported by [**inet_aton**(3)](https://linux.die.net/man/3/inet_aton) ; for IPv6, hexadecimal string format as supported by [**inet_pton**(3)](https://linux.die.net/man/3/inet_pton)  ), or a **network hostname**, whose network addresses are looked up and resolved. If *`hints.ai_flags`* contains the **AI_NUMERICHOST **flag then *node* must be a **numerical network address**. The **AI_NUMERICHOST** flag suppresses any potentially lengthy network host address lookups.

> NOTE: :在Wikipedia的[getaddrinfo](https://en.wikipedia.org/wiki/Getaddrinfo)中，列举了一个例子：给定domain name，获得其IP地址；



If the **AI_PASSIVE** flag is specified in *`hints.ai_flags`*, and *node* is NULL, then the returned socket addresses will be suitable for [**bind**(2)ing](https://linux.die.net/man/2/bind) a socket that will [**accept**(2)](https://linux.die.net/man/2/accept) connections. The returned socket address will contain the "wildcard address" (**INADDR_ANY** for IPv4 addresses, **IN6ADDR_ANY_INIT** for IPv6 address). The wildcard address is used by applications (typically servers) that intend to accept connections on any of the hosts's network addresses. If *node* is not NULL, then the **AI_PASSIVE** flag is ignored.

> NOTE: : 这段话非常重要，[redis 4 network configuration](https://raw.githubusercontent.com/antirez/redis/4.0/redis.conf)中有如下一段话：

> ```
> # By default, if no "bind" configuration directive is specified, Redis listens
> # for connections from all the network interfaces available on the server.
> # It is possible to listen to just one or multiple selected interfaces using
> # the "bind" configuration directive, followed by one or more IP addresses.
> ```

通过阅读redis的源代码，可以发现它所使用的就是上面这段话中所描述的方法，即在`hints.ai_flags`中设置`AI_PASSIVE`，同时将`node`参数node设置为NULL；这种方法就相当于flask中的`flask  run --host=0.0.0.0`，这是一种特殊情况；查看下面的[Server program](#Server program)，其中的`hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */`是非常具有提示意义的，它指出了这种特殊的用法；



> NOTE: : `PASSIVE`的含义是被动的，显然它是符合在client/server模型中，server是被动地，server等待client的请求；



> NOTE: :  不要忽视了上面这段话中的最后一句话： If *node* is not NULL, then the **AI_PASSIVE** flag is ignored.在redis源代码中也有这样的类似说法；对于 *node* is not NULL 的情况，它到底是声明一个server socket还是一个client  socket？

20190529：其实上面我的问题就存在错误`getaddinfo`函数的功能是获取`addrinfo`，而不是生成一个socket，它的返回值将用于socket；所以对于最后一句话中描述的情况，它就是最最平台的将node转换为socket能够接受的`addrinfo`。



If the **AI_PASSIVE** flag is not set in *`hints.ai_flags`*, then the returned socket addresses will be suitable for use with **connect**(2), **sendto**(2), or **sendmsg**(2). If *node* is NULL, then the network address will be set to the loopback interface address (**INADDR_LOOPBACK** for IPv4 addresses, **IN6ADDR_LOOPBACK_INIT**for IPv6 address); this is used by applications that intend to communicate with peers running on the same host.

> NOTE: : 根据上面所总结的，`PASSIVE`的含义是被动的，显然一旦设置了`AI_PASSIVE`就表明这是应用于server端的；对于client，则`AI_PASSIVE`不应被设置，它表明它不是被动的；上面这一段中的第二句话说明的是当**AI_PASSIVE** flag is not set in *`hints.ai_flags`*, 并且 *node* is NULL的情况下，`getaddrinfo`函数的处理逻辑，在这种情况下，它将使用loopback interface address。





The **getaddrinfo**() function allocates and initializes a linked list of *addrinfo* structures, one for each network address that matches *node* and *service*, subject to any restrictions imposed by *hints*, and returns a pointer to the start of the list in *res*. The items in the linked list are linked by the *ai_next* field.

> NOTE: : 这段对该函数的功能的总结比较好



There are several reasons why the linked list may have more than one *addrinfo* structure, including: the network host is [multihomed](https://en.wikipedia.org/wiki/Multihoming), accessible over multiple protocols (e.g., both **AF_INET** and **AF_INET6**); or the same service is available from multiple **socket types** (one **SOCK_STREAM** address and another **SOCK_DGRAM** address, for example). Normally, the application should try using the addresses in the order in which they are returned. The sorting function used within **getaddrinfo**() is defined in RFC 3484; the order can be tweaked for a particular system by editing */etc/gai.conf* (available since glibc 2.5).



If *hints.ai_flags* includes the **AI_CANONNAME** flag, then the *ai_canonname* field of the first of the *addrinfo* structures in the returned list is set to point to the official name of the host.



The remaining fields of each returned *addrinfo* structure are initialized as follows:

*

The *ai_family*, *ai_socktype*, and *ai_protocol* fields return the socket creation parameters (i.e., these fields have the same meaning as the corresponding arguments of **socket**(2)). For example, *ai_family* might return **AF_INET** or **AF_INET6**; *ai_socktype* might return **SOCK_DGRAM** or **SOCK_STREAM**; and *ai_protocol* returns the protocol for the socket.

*

A pointer to the socket address is placed in the *ai_addr* field, and the length of the socket address, in bytes, is placed in the *ai_addrlen* field.





## Example

The following programs demonstrate the use of **getaddrinfo**(), **gai_strerror**(), **freeaddrinfo**(), and **getnameinfo**(3). The programs are an echo server and client for UDP datagrams.

### Server program

```c
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];

   if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(NULL, argv[1], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

   /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket(2) (or bind(2)) fails, we (close the socket
       and) try the next address. */

   for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        if (sfd == -1)
            continue;

       if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

       close(sfd);
    }

   if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

   freeaddrinfo(result);           /* No longer needed */

   /* Read datagrams and echo them back to sender */

   for (;;) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(sfd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (nread == -1)
            continue;               /* Ignore failed request */

       char host[NI_MAXHOST], service[NI_MAXSERV];

       s = getnameinfo((struct sockaddr *) &peer_addr,
                        peer_addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICSERV);
       if (s == 0)
            printf("Received %ld bytes from %s:%s\n",
                    (long) nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

       if (sendto(sfd, buf, nread, 0,
                    (struct sockaddr *) &peer_addr,
                    peer_addr_len) != nread)
            fprintf(stderr, "Error sending response\n");
    }
}
```

> NOTE: : 这段程序终止的时候，只能够由OS来负责清理`sfd`所占用的资源；另外可以通过`atexit`函数来注册一个exit handler负责清理；显然c语言缺乏`finally`机制；

### Client program

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];

   if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   /* Obtain address(es) matching host/port */

   memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

   s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

   /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */

   for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;

       if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

       close(sfd);
    }

   if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

   freeaddrinfo(result);           /* No longer needed */

   /* Send remaining command-line arguments as separate
       datagrams, and read responses from server */

   for (j = 3; j < argc; j++) {
        len = strlen(argv[j]) + 1;
                /* +1 for terminating null byte */

       if (len + 1 > BUF_SIZE) {
            fprintf(stderr,
                    "Ignoring long message in argument %d\n", j);
            continue;
        }

       if (write(sfd, argv[j], len) != len) {
            fprintf(stderr, "partial/failed write\n");
            exit(EXIT_FAILURE);
        }

       nread = read(sfd, buf, BUF_SIZE);
        if (nread == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

       printf("Received %ld bytes: %s\n", (long) nread, buf);
    }

   exit(EXIT_SUCCESS);
}
```

