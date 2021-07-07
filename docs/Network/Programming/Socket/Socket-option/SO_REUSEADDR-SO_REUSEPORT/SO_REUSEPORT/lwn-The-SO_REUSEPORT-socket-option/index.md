# lwn [The SO_REUSEPORT socket option](https://lwn.net/Articles/542629/) 

> NOTE: 
>
> 一、在 stackoverflow [Can two applications listen to the same port?](https://stackoverflow.com/questions/1694144/can-two-applications-listen-to-the-same-port) # [A](https://stackoverflow.com/a/1694148) 中，发现的这篇文章
>
> 二、这篇文章梳理了 `SO_REUSEPORT` 对 `SO_REUSEADDR` 的改进
>
> 三、关于这个option的发展史，参见: 
>
> 1、idea.popcoun [Bind before connect](https://idea.popcount.org/2014-04-03-bind-before-connect/)
>
> 其中对`SO_REUSEPORT`的发展史进行了非常好的说明

One of the features merged in the 3.9 development cycle was TCP and UDP support for the `SO_REUSEPORT` socket option; that support was implemented in a series of patches by Tom Herbert. The new socket option allows multiple sockets on the same host to bind to the same port, and is intended to improve the performance of multithreaded network server applications running on top of multicore systems.

The basic concept of `SO_REUSEPORT` is simple enough. Multiple servers (processes or threads) can bind to the same port if they each set the option as follows:

```c
    int sfd = socket(domain, socktype, 0);

    int optval = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    bind(sfd, (struct sockaddr *) &addr, addrlen);
```

So long as the *first* server sets this option before binding its socket, then any number of other servers can also bind to the same port if they also set the option beforehand. The requirement that the first server must specify this option prevents port hijacking(劫持)—the possibility that a rogue(流氓) application binds to a port already used by an existing server in order to capture (some of) its incoming connections or datagrams. To prevent unwanted processes from hijacking a port that has already been bound by a server using `SO_REUSEPORT`, all of the servers that later bind to that port must have an effective user ID that matches the effective user ID used to perform the first bind on the socket.

`SO_REUSEPORT` can be used with both TCP and UDP sockets. With TCP sockets, it allows multiple listening sockets—normally each in a different thread—to be bound to the same port. Each thread can then accept incoming connections on the port by calling `accept()`. This presents an alternative to the traditional approaches used by multithreaded servers that accept incoming connections on a single socket.

## First of the traditional approaches

The first of the traditional approaches is to have a single listener thread that accepts all incoming connections and then passes these off to other threads for processing. The problem with this approach is that the listening thread can become a bottleneck in extreme cases. In [early discussions](http://thread.gmane.org/gmane.linux.network/102140/focus=102150) on `SO_REUSEPORT`, Tom noted that he was dealing with applications that accepted 40,000 connections per second. Given that sort of number, it's unsurprising to learn that Tom works at Google.



## Second of the traditional approaches

The second of the traditional approaches used by multithreaded servers operating on a single port is to have all of the threads (or processes) perform an `accept()` call on a single listening socket in a simple event loop of the form:

```C
    while (1) {
        new_fd = accept(...);
        process_connection(new_fd);
    }
```

The problem with this technique, as Tom [pointed out](https://lwn.net/Articles/542718/), is that when multiple threads are waiting in the `accept()` call, wake-ups are not fair, so that, under high load, incoming connections may be distributed across threads in a very unbalanced fashion. At Google, they have seen a factor-of-three difference between the thread accepting the most connections and the thread accepting the fewest connections; that sort of imbalance can lead to underutilization of CPU cores. By contrast, the `SO_REUSEPORT` implementation distributes connections evenly across all of the threads (or processes) that are blocked in `accept()` on the same port.



## `SO_REUSEPORT` UDP sockets 

As with TCP, `SO_REUSEPORT` allows multiple UDP sockets to be bound to the same port. This facility could, for example, be useful in a DNS server operating over UDP. With `SO_REUSEPORT`, each thread could use `recv()` on its own socket to accept datagrams arriving on the port. The traditional approach is that all threads would compete to perform `recv()` calls on a single shared socket. As with the second of the traditional TCP scenarios described above, this can lead to unbalanced loads across the threads. By contrast, `SO_REUSEPORT` distributes datagrams evenly across all of the receiving threads.



## `SO_REUSEADDR` 

Tom [noted](https://lwn.net/Articles/542728/) that the traditional `SO_REUSEADDR` socket option already allows multiple UDP sockets to be bound to, and accept datagrams on, the same UDP port. However, by contrast with `SO_REUSEPORT`, `SO_REUSEADDR` does not prevent port hijacking and does not distribute datagrams evenly across the receiving threads.



## Implementation

There are two other noteworthy points about Tom's patches. The first of these is a useful aspect of the implementation. Incoming connections and datagrams are distributed to the server sockets using a hash based on the 4-tuple of the connection—that is, the peer IP address and port plus the local IP address and port. This means, for example, that if a client uses the same socket to send a series of datagrams to the server port, then those datagrams will all be directed to the same receiving server (as long as it continues to exist). This eases the task of conducting stateful conversations between the client and server.

The other noteworthy point is that there is a [defect](https://lwn.net/Articles/542738/) in the current implementation of TCP `SO_REUSEPORT`. If the number of listening sockets bound to a port changes because new servers are started or existing servers terminate, it is possible that incoming connections can be dropped during the three-way handshake. The problem is that connection requests are tied to a specific listening socket when the initial SYN packet is received during the handshake. If the number of servers bound to the port changes, then the `SO_REUSEPORT` logic might not route the final ACK of the handshake to the correct listening socket. In this case, the client connection will be reset, and the server is left with an orphaned request structure. A solution to the problem is still being worked on, and may consist of implementing a connection request table that can be shared among multiple listening sockets.

The `SO_REUSEPORT` option is non-standard, but available in a similar form on a number of other UNIX systems (notably, the BSDs, where the idea originated). It seems to offer a useful alternative for squeezing the maximum performance out of network applications running on multicore systems, and thus is likely to be a welcome addition for some application developers.