# `SO_REUSEADDR`



## stackoverflow [What are the use cases of SO_REUSEADDR?](https://stackoverflow.com/questions/577885/what-are-the-use-cases-of-so-reuseaddr)

I have used `SO_REUSEADDR` to have my server which got terminated to restart with out complaining that the socket is already is in use. I was wondering if there are other uses of `SO_REUSEADDR`? Have anyone used the **socket option** for other than the said purpose?



### [A](https://stackoverflow.com/a/577905)

For **TCP**, the primary purpose is to restart a closed/killed process on the same address.

The flag is needed because the port goes into a `TIME_WAIT` state to ensure all data is transferred.

If two sockets are bound to the same interface and port, and they are members of the same **multicast group**, data will be delivered to both sockets.

> NOTE: 
>
> 这段话的意思是从client发送过来的data将multicast到所有bind到这个port的socket

I guess an alternative use would be a security attack to try to intercept data.

([Source](http://www.developerweb.net/forum/showthread.php?t=2941))

------

For **UDP**, `SO_REUSEADDR` is used for multicast.

> More than one process may bind to the same `SOCK_DGRAM` UDP port if the `bind()` is preceded by:
>
> ```c
> int one = 1;
> setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
> ```
>
> In this case, every incoming multicast or broadcast UDP datagram destined to the shared port is delivered to all sockets bound to the port.

([Source](http://www.kohala.com/start/mcast.api.txt))



## stackoverflow [What is the purpose of SO_REUSEADDR? [duplicate]](https://stackoverflow.com/questions/40576517/what-is-the-purpose-of-so-reuseaddr)



### [A](https://stackoverflow.com/a/40577134)

For UDP sockets, setting the `SO_REUSEADDR` option allows multiple sockets to be open on the same port.

If those sockets are also joined to a multicast group, any multicast packet coming in to that group and port will be delivered to all sockets open on that port.


