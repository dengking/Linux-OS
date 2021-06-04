# Mark socket





## stackoverflow [How to filter packets marked by 'so_mark' using TC](https://stackoverflow.com/questions/26527426/how-to-filter-packets-marked-by-so-mark-using-tc)

I use `so_mark` to mark packets sent from a specific socket. Now I want to filter these packets from a class in my TC (from HTB mechanism actually). What is the filter to be used (and syntax example will be helpful as well)

### A

If anyone wondered :

```shell
tc filter add dev eth0 parent 1:0 prio 1 u32 match mark 0x123 0xFFF flowid 1:1
```





## stackexchange [-m option does not work in ping command](https://unix.stackexchange.com/questions/281015/m-option-does-not-work-in-ping-command)

I was learning the Linux `ping` command and its options, and read about the `-m` option which is used to mark the outgoing packet. When receiving, we can filter that marked packet result first.

I am trying to set the mark for the packet, but I got a warning message:

```
$ ping -m 10 server
PING server (192.168.2.2) 56(84) bytes of data.
Warning: Failed to set mark 10
64 bytes from server (192.168.2.2): icmp_req=1 ttl=64 time=0.182 ms
64 bytes from server (192.168.2.2): icmp_req=2 ttl=64 time=0.201 ms
```

So, why does it fail to mark? How can I mark a packet using the `-m` option?



### A

**Short answer:** You can't do with a normal user.

**Long answer:** To be able to mark packets, you need to be a root user, or at least a user with the `SO_MARK` capability(needs to be set as root):

SO_MARK at [socket(7)](http://man7.org/linux/man-pages/man7/socket.7.html):

> ```
>    SO_MARK (since Linux 2.6.25)
>           Set the mark for each packet sent through this socket (similar
>           to the netfilter MARK target but socket-based).  Changing the
>           mark can be used for mark-based routing without netfilter or
>           for packet filtering.  Setting this option requires the
>           CAP_NET_ADMIN capability.
> ```

The [piece of code](https://github.com/iputils/iputils/blob/master/ping_common.c) at `ping_common.c` from iputils that confirms this theory:

```C
#ifdef SO_MARK
if (options & F_MARK) {
    int ret;

    enable_capability_admin();
    ret = setsockopt(sock->fd, SOL_SOCKET, SO_MARK, &mark, sizeof(mark));
    disable_capability_admin();

    if (ret == -1) {
        /* we probably dont wanna exit since old kernels
         * dont support mark ..
        */
        fprintf(stderr, "Warning: Failed to set mark %d\n", mark);
    }
}
#endif
```

To learn more about capabilities: man [capabilities(7)](http://man7.org/linux/man-pages/man7/capabilities.7.html) and capabilities(7) [overview](http://linux.die.net/man/7/capabilities).

If you want to go further on capabilities with all other binaries of the system, [this is](http://www.friedhoff.org/posixfilecaps.html#HowTo - Detection ofneeded capabilities - strace) a good way to probe them. Involves kernel compilation so, it could not be suitable for production environment.

**ICMP marking usefulness:**

As it is described on [manpages](http://www.computerhope.com/unix/uping.htm):

```
-m mark     
    use mark to tag the packets going out. This is useful for variety of reasons
    within the kernel such as using policy routing to select specific outbound processing.
```

And as explained on a [superuser](https://superuser.com/q/609125/210242) question, this feature could be useful when probing multilink/multiroute network environment, where you need to force that an ICMP packet goes through one specific "flow".

Practical example. Host 1:

```shell
$ ping -m 10 <host>
```

Host 2. Alter the default policy of `INPUT` to `DROP` and accept packets only from the source ip of the specific route that has the mark 10 on host 1:

```shell
# iptables -P INPUT DROP
# iptables -A INPUT -s <IP_SOURCE_MARK_10> -p icmp -j ACCEPT
```

This was already explained [here](https://stackoverflow.com/q/36856897/2231796). Again, it will be better used for routing decisions debugging(if you have more than one path between 2 hosts), since a `tcpdump -nevvv -i <interface> src host <source_host>` will be more than enough to just probe "icmp packet arrival".