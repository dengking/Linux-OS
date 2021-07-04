# `tcp_max_syn_backlog`  VS `somaxconn`

| queue               |                                                              |                                 |
| ------------------- | ------------------------------------------------------------ | ------------------------------- |
| `SYN_RECV` queue    | [`listen()`](https://www.man7.org/linux/man-pages/man2/listen.2.html)'s `backlog` argument | `tcp_max_syn_backlog` in kernel |
| `ESTABLISHED` queue | [`listen()`](https://www.man7.org/linux/man-pages/man2/listen.2.html)'s `backlog` argument | `somaxconn` in kernel           |



## stackoverflow [What is the difference between tcp_max_syn_backlog and somaxconn?](https://stackoverflow.com/questions/62641621/what-is-the-difference-between-tcp-max-syn-backlog-and-somaxconn)



### [A](https://stackoverflow.com/a/62643129)

sysctl is an API. So you can just read the Linux kernel [documentation for appropriate version](https://elixir.bootlin.com/linux/v4.15.18/source/Documentation/networking/ip-sysctl.txt#L372):

```
tcp_max_syn_backlog - INTEGER
    Maximal number of remembered connection requests, which have not
    received an acknowledgment from connecting client.
    The minimal value is 128 for low memory machines, and it will
    increase in proportion to the memory of machine.
    If server suffers from overload, try increasing this number.

somaxconn - INTEGER
    Limit of socket listen() backlog, known in userspace as SOMAXCONN.
    Defaults to 128.  See also tcp_max_syn_backlog for additional tuning
    for TCP sockets.
```

Let's consider a [TCP-handshake](https://www.geeksforgeeks.org/tcp-3-way-handshake-process/).. `tcp_max_syn_backlog` represents the maximal number of connections in `SYN_RECV` queue. I.e. when your server received SYN, sent SYN-ACK and haven't received ACK yet. This is a separate queue of so-called "request sockets" - `reqsk` in code (i.e. not fully-fledged sockets, "request sockets" occupy less memory. In this state we can save some memory and not yet allocate a full socket because the full connection may not be at all in the future if ACK will not arrive). The value of this queue is affected (see [this post](https://stackoverflow.com/questions/58183847/does-listens-backlog-number-include-syn-received-connections-count-in-case-of-t/58185850)) by [`listen()`](https://www.man7.org/linux/man-pages/man2/listen.2.html)'s `backlog` argument and limited by `tcp_max_syn_backlog` in kernel.

`somaxconn` represents the maximal size of `ESTABLISHED` queue. This is another queue.
Recall the previously mentioned `SYN_RECV` queue - your server is waiting for ACK from client. When the ACK arrives the kernel roughly speaking makes the big full-fledged(完整的、羽翼丰满的) socket from "request socket" and moves it to ESTABLISHED queue. Then you can do [`accept()`](https://man7.org/linux/man-pages/man2/accept.2.html) on this socket. This queue is also affected by `listen()`'s `backlog` argument and limited by `somaxconn` in kernel.

Useful links: [1](https://stackoverflow.com/questions/23862410/invalid-argument-setting-key-net-core-somaxconn/25074725#25074725), [2](http://veithen.io/2014/01/01/how-tcp-backlog-works-in-linux.html).

