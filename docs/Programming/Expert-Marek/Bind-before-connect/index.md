# idea.popcoun [Bind before connect](https://idea.popcount.org/2014-04-03-bind-before-connect/)

> NOTE:
>
> 一、"TCP/IP connection four element tuple: {source IP, source port, destination IP, destination port}"决定了我们在使用的时候，需要考虑这四个要素。
>
> 

A TCP/IP connection is identified by a four element tuple: {source IP, source port, destination IP, destination port}. To establish a TCP/IP connection only a destination IP and port number are needed, the operating system automatically selects source IP and port. This article explains how the Linux kernel does the **source port allocation**.

## Ephemeral port range

To establish a connection [BSD API](https://en.wikipedia.org/wiki/Berkeley_sockets) requires two steps: first you need to create a socket, then call `connect()` on it. Here's some code in Python:

```python
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("www.google.com", 80))
```

When a connection is made the operating system needs to select an unused source port number. Linux selects a port from an [ephemeral port range](http://en.wikipedia.org/wiki/Ephemeral_port), which by default is a set to range from 32768 to 61000:

```SHELL
$ cat /proc/sys/net/ipv4/ip_local_port_range
32768   61000
```

On Linux the ephemeral port range is a global resource[1](https://idea.popcount.org/2014-04-03-bind-before-connect/#fn:1), it's not a specific setting local to an IP address.

Let's dig into details on how exactly a source port is selected. The main work is done in the [`__inet_hash_connect` function.](https://github.com/torvalds/linux/blob/1bbdceef1e535add893bf71d7b7ab102e4eb69eb/net/ipv4/inet_hashtables.c#L501) Here's an excerpt (with many lines of code removed for simplicity):

```C
static u32 hint;

inet_get_local_port_range(net, &low, &high);
remaining = (high - low) + 1;

for (i = 1; i <= remaining; i++) {
    port = low + (i + hint) % remaining;
    head = &hinfo->bhash[inet_bhashfn(net, port,
            hinfo->bhash_size)];

    inet_bind_bucket_for_each(tb, &head->chain) {
        if (net_eq(ib_net(tb), net) &&
            tb->port == port) {
            if (tb->fastreuse >= 0 ||
                tb->fastreuseport >= 0)
                goto next_port;
            if (!check_established(death_row, sk,
                        port, &tw))
                goto ok;
            goto next_port;
        }
    }

    tb = inet_bind_bucket_create(hinfo->bind_bucket_cachep,
            net, head, port);
    goto ok;

next_port:
}
[...]
ok:
    hint += i;
```

In translation: we start with a `hint` port number[2](https://idea.popcount.org/2014-04-03-bind-before-connect/#fn:2) and increase it until we find a source port that is either:

1、Completely unused.

2、Used by some connections but it's ok for it to be reused: it passes the `check_established` check.

By default there are 28232 ports in the ephemeral range, so the first condition could be matched at most that number of times. If you have more than 28k connections Linux will need to find a port that passes [`check_established`](https://github.com/torvalds/linux/blob/1bbdceef1e535add893bf71d7b7ab102e4eb69eb/net/ipv4/inet_hashtables.c#L344)check. It's okay to reuse a port if no connection already exists between the same source and destination endpoints.

What if you really want to establish more than 28k connections to a single destination? There are a couple of tweaks you can make:

1、Increase the `ip_local_port_range` pool. Setting it to maximum range will allow 64511 concurrent connections (65535-1024).

2、Set [`tcp_tw_reuse` sysctl](http://stackoverflow.com/a/12719362) to [enable reusing of TIME_WAIT sockets](https://github.com/torvalds/linux/blob/1bbdceef1e535add893bf71d7b7ab102e4eb69eb/net/ipv4/tcp_ipv4.c#L127).

3、Do *not* set `tcp_tw_recycle`. It will cause SYN's to be dropped for users behind a NAT.

> NOTE: 
>
> 这是老生常谈的问题

If you really want to establish even more than 64k connections to a single destination address you'll have to use more than one source IP address.

## Bind before connect

> NOTE: 
>
> 一、其实一般在client side是不需要bind before connect的，那在上面情况下需要client side bind呢？这在 `Network\Programming\man-2-bind` 中进行了介绍。

It is possible to ask the kernel to select a specific source IP and port by calling `bind()` before calling `connect()`:

```c++
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Let the source address be 192.168.1.21:1234
s.bind(("192.168.1.21", 1234))
s.connect(("www.google.com", 80))
```

This trick is often called, wait for it..., "bind before connect". Specifying port number `0` means that the kernel should do a port allocation for us:

```C
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("192.168.1.21", 0))
s.connect(("www.google.com", 80))
```

This method is fairly well known, but there's a catch. 

> NOTE: 
>
> "这种方法相当有名，但是有一个陷阱"

`Bind` is usually called for listening sockets so the kernel needs to make sure that the **source address** is not shared with anyone else. It's a problem. When using this technique in this form it's impossible to establish more than 64k (ephemeral port range) outgoing(外出的) connections in total. After that the attempt to call `bind()` will fail with an `EADDRINUSE` error - all the source ports will be busy.

> NOTE: 
>
> "' Bind '通常用于侦听套接字，因此内核需要确保**源地址**不被其他任何人共享。这是一个问题。当以这种形式使用此技术时，不可能总共建立超过64k(临时端口范围)的输出连接。在此之后，尝试调用' bind() '将失败，并出现' `EADDRINUSE` '错误——所有源端口都将繁忙。"
>
> 理解上面这段话的一个非常关键的点在于理解: "outgoing(外出的) connections"，它指的是本机作为client主动去连接server；后面还会用到这个词语，在 `SO_REUSEADDR` 中对此进行了非常好的说明
>
> 关于上面这段话，没有非常理解，在下面文章中，有比较好的解释:
>
> 1、zhihu [网络编程：SO_REUSEADDR的使用](https://zhuanlan.zhihu.com/p/79999012)
>
> 

To work around this we need to understand two flags that affect the kernel port allocation behaviour: `SO_REUSEADDR` and `SO_REUSEPORT`.

### `SO_REUSEADDR`

`SO_REUSEADDR` is mentioned in only two man pages:

Man `ip(7)`:

> A TCP local socket address that has been bound is unavailable for some time after closing, unless the SO_REUSEADDR flag has been set. Care should be taken when using this flag as it makes TCP less reliable.

Man `socket(7)`:

> SO_REUSEADDR: Indicates that the rules used in validating addresses supplied in a bind(2) call should allow reuse of local addresses. For AF_INET sockets this means that a socket may bind, except when there is an active listening socket bound to the address. When the listening socket is bound to INADDR_ANY with a specific port then it is not possible to bind to this port for any local address. Argument is an integer boolean flag.

Don't worry if it sounds confusing, here's how I understand it:

By setting `SO_REUSEADDR` user informs the kernel of an intention to share the bound port with anyone else, but only if it doesn't cause a conflict on the protocol layer. There are at least three situations when this flag is useful:

1、Normally after binding to a port and stopping a server it's neccesary to wait for a socket to time out before another server can bind to the same port. With `SO_REUSEADDR` set it's possible to rebind immediately, even if the socket is in a `TIME_WAIT` state.

> NOTE: 
>
> 这种是最最常见的

2、When one server binds to `INADDR_ANY`, say `0.0.0.0:1234`, it's impossible to have another server binding to a specific address like `192.168.1.21:1234`. With `SO_REUSEADDR` flag this behaviour is allowed.

3、When using the bind before connect trick only a single connection can use a single outgoing source port. With this flag, it's possible for many connections to reuse the same source port, given that they connect to different destination addresses.

> NOTE: 
>
> 一、这一段对 "outgoing" 的解释是比较好的

### `SO_REUSEPORT`

`SO_REUSEPORT` is poorly documented. It was introduced for UDP multicast sockets. Initially, only a single server was able to use a particular port to listen to a multicast group. This flag allowed different sockets to bind to exactly the same IP and port, and receive datagrams for [selected multicast groups](http://stackoverflow.com/a/2741989).

More generally speaking, setting `SO_REUSEPORT` infroms a kernel of an intention to share a particular bound port between many processes, but only for a single user. 

For multicast datagrams are distributed based on multicast groups, 

For usual `UDP` datagrams are distributed in round-robin way. 

For a long time this flag wasn't available for `TCP` sockets, but recently Google submitted patches that fix it and distribute incoming connections [in round-robin way between listening sockets](https://lwn.net/Articles/542629/).

The best explanation of these flags I found [in this stackoverflow answer](http://stackoverflow.com/a/14388707).

## Port allocation

> NOTE: 
>
> 后续内容未阅读
