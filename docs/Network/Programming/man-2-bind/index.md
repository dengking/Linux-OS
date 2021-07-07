# [bind(2) - Linux man page](https://linux.die.net/man/2/bind)

> NOTE: 
>
> 一、bind(2) 用于绑定IP、port

## Synopsis

```C
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr,
         socklen_t addrlen);
```

## Description

When a socket is created with **socket**(2), it exists in a **name space** (address family) but has no address assigned to it. **bind**() assigns the **address** specified by *addr* to the **socket** referred to by the file descriptor *sockfd*. *addrlen* specifies the size, in bytes, of the address structure pointed to by *addr*. Traditionally, this operation is called "assigning a name to a socket".

It is normally necessary to assign a local address using **bind**() before a **SOCK_STREAM** socket may receive connections (see **accept**(2)).

The rules used in name binding vary between **address families**. Consult the manual entries in Section 7 for detailed information. For **AF_INET** see [**ip**(7)](https://linux.die.net/man/7/ip), for **AF_INET6** see [**ipv6**(7)](https://linux.die.net/man/7/ipv6), for **AF_UNIX** see [**unix**(7)](https://linux.die.net/man/7/unix), for **AF_APPLETALK** see **ddp**(7), for **AF_PACKET** see **packet**(7), for **AF_X25** see **x25**(7) and for **AF_NETLINK** see **netlink**(7).

> NOTE:  : 在Unix中，address family是domain的同义词，参见APUE的chapter 16.2 Socket Descriptors。

> NOTE:  : 当address family是**AF_INET**的时候，在调用`bind`之前往往是需要先调用`getaddrinfo`来获得`struct sockaddr *addr`，而当address family是**AF_UNIX**的时候，则不是调用`getaddrinfo`，具体的用法参见下面的例子；

The actual structure passed for the *addr* argument will depend on the **address family**. The *sockaddr* structure is defined as something like:

```c
struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
}
```

The only purpose of this structure is to cast the structure pointer passed in *addr* in order to avoid compiler warnings. See EXAMPLE below.



## Example

An example of the use of **bind**() with Internet domain sockets can be found in [**getaddrinfo**(3)](https://linux.die.net/man/3/getaddrinfo).

The following example shows how to bind a stream socket in the UNIX (**AF_UNIX**) domain, and accept connections:

```c
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MY_SOCK_PATH "/somepath"
#define LISTEN_BACKLOG 50

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int
main(int argc, char *argv[])
{
    int sfd, cfd;
    struct sockaddr_un my_addr, peer_addr;
    socklen_t peer_addr_size;

   sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        handle_error("socket");

   memset(&my_addr, 0, sizeof(struct sockaddr_un));
                        /* Clear structure */
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, MY_SOCK_PATH,
            sizeof(my_addr.sun_path) - 1);

   if (bind(sfd, (struct sockaddr *) &my_addr,
            sizeof(struct sockaddr_un)) == -1)
        handle_error("bind");

   if (listen(sfd, LISTEN_BACKLOG) == -1)
        handle_error("listen");

   /* Now we can accept incoming connections one
       at a time using accept(2) */

   peer_addr_size = sizeof(struct sockaddr_un);
    cfd = accept(sfd, (struct sockaddr *) &peer_addr,
                 &peer_addr_size);
    if (cfd == -1)
        handle_error("accept");

   /* Code to deal with incoming connection(s)... */

   /* When no longer required, the socket pathname, MY_SOCK_PATH
       should be deleted using unlink(2) or remove(3) */
}
```



## stackoverflow [Why is bind() used in TCP? Why is it used only on server side and not in client side?](https://stackoverflow.com/questions/12763268/why-is-bind-used-in-tcp-why-is-it-used-only-on-server-side-and-not-in-client)



### [A](https://stackoverflow.com/a/12763313)

It assigns the "local" end's port number.

For a server socket, this is the ultimate way to go - it is exactly what is needed: have your socket be bound to port 80 for a web server, for example.

For a client socket, however, the local address and port is normally not of importance. So you don't `bind()`. If the server restricts its clients to maybe have a certain port number, or a port number out of a given range, you can use `bind()` on client side as well.

> NOTE: 

On the other hand, you might as well be able to `listen()` on a socket where you haven't called `bind()` (actually I'm not sure about that, but it would make sense). In this scenario, your server port would be random, and the server process would communicate its port via a different means to the client. Imagine a "double-connection" protocol such as FTP, where you have a control connection and a data connection. The port the data connection listens on is completely arbitrary, but must be communicated to the other side. So the "automatically determined port" is used and communicated.

One example in Python:

```python
import socket
s = socket.socket() # create your socket
s.listen(10) # call listen without bind
s.getsockname() Which random port number did we get?
# here results in ('0.0.0.0', 61372)

s2 = socket.socket() # create client socket
s2.connect(('localhost', 61372)) # connect to the one above
s3, x = s.accept() # Python specific use; s3 is our connected socket on the server side
s2.getpeername()
# gives ('127.0.0.1', 61372)
s2.getsockname()
# gives ('127.0.0.1', 54663)
s3.getsockname()
# gives ('127.0.0.1', 61372), the same as s2.getpeername(), for symmetry
s3.getpeername()
#gives ('127.0.0.1', 54663), the same as s2.getsockname(), for symmetry
#test the connection
s2.send('hello')
print s3.recv(10)
```



## stackoverflow [What client-side situations need bind()?](https://stackoverflow.com/questions/4118241/what-client-side-situations-need-bind)



### [A](https://stackoverflow.com/a/4118325)

On the client side, you would only use bind if you want to use a specific client-side port, which is rare. Usually on the client, you specify the IP address and port of the server machine, and the OS will pick which port you will use. Generally you don't care, but in some cases, there may be a firewall on the client that only allows outgoing connections on certain port. In that case, you will need to bind to a specific port before the connection attempt will work.

