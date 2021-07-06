# idea.popcoun [Bind before connect](https://idea.popcount.org/2014-04-03-bind-before-connect/)

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

