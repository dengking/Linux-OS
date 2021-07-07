# TCP keepalive

## wikipedia [Keepalive](https://en.wikipedia.org/wiki/Keepalive)

A **keepalive** (**KA**) is a message sent by one device to another to check that the [link](https://en.wikipedia.org/wiki/Data_link) between the two is operating, or to prevent the link from being broken.

> NOTE: 
>
> 两个目的

### Description

A **keepalive signal** is often sent at predefined intervals, and plays an important role on the [Internet](https://en.wikipedia.org/wiki/Internet). After a signal is sent, if no reply is received the [link](https://en.wikipedia.org/wiki/Data_link) is assumed to be down and future data will be routed via another path until the link is up again. A keepalive signal can also be used to indicate to Internet infrastructure that the connection should be preserved. Without a keepalive signal, intermediate [NAT-enabled routers](https://en.wikipedia.org/wiki/Network_address_translation) can drop the connection after timeout.

> NOTE: 
>
> 保持活动信号通常以预定义的间隔发送，并在因特网上起重要作用。 在发送信号之后，如果没有收到回复，则假定链路断开，并且将来的数据将通过另一路径路由，直到链路再次启动。 keepalive信号还可用于向Internet基础结构指示应保留连接。 如果没有keepalive信号，启用NAT的中间路由器可以在超时后断开连接。

Since the only purpose is to find links that don't work or to indicate connections that should be preserved, keepalive messages tend to be short and not take much [bandwidth](https://en.wikipedia.org/wiki/Bandwidth_(computing)). However, their precise format and usage terms depend on the communication protocol.

### TCP keepalive

[Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) (TCP) keepalives are an optional feature, and if included must default to off.[[1\]](https://en.wikipedia.org/wiki/Keepalive#cite_note-1) The keepalive packet contains no data. In an [Ethernet](https://en.wikipedia.org/wiki/Ethernet) network, this results in frames of minimum size (64 bytes[[2\]](https://en.wikipedia.org/wiki/Keepalive#cite_note-IEEE_802.3_Clause_3.1.1-2)). There are three parameters[[3\]](https://en.wikipedia.org/wiki/Keepalive#cite_note-3) related to keepalive:

1、**Keepalive time** is the duration between two keepalive transmissions in idle condition. TCP keepalive period is required to be configurable and by default is set to no less than 2 hours.

2、**Keepalive interval** is the duration between two successive keepalive retransmissions, if acknowledgement to the previous keepalive transmission is not received.

3、**Keepalive retry** is the number of retransmissions to be carried out before declaring that remote end is not available

When two hosts are connected over a network via TCP/IP, TCP Keepalive Packets can be used to determine if the connection is still valid, and terminate it if needed.

Most hosts that support TCP also support TCP Keepalive. Each host (or peer) periodically sends a TCP packet to its peer which solicits a response. If a certain number of keepalives are sent and no response (ACK) is received then the sending host will terminate the connection from its end. If a connection has been terminated due to a TCP Keepalive time-out and the other host eventually sends a packet for the old connection, the host that terminated the connection will send a packet with the RST flag set to signal the other host that the old connection is no longer active. This will force the other host to terminate its end of the connection so a new connection can be established.

Typically TCP Keepalives are sent every 45 or 60 seconds on an idle TCP connection, and the connection is dropped after 3 sequential ACKs are missed. This varies by host, e.g. by default Windows PCs send the first TCP Keepalive packet after 7200000ms (2 hours), then sends 5 Keepalives at 1000ms intervals, dropping the connection if there is no response to any of the Keepalive packets.

### Keepalive on higher layers

Since TCP keepalive is optional, various protocols (e.g. SMB[[4\]](https://en.wikipedia.org/wiki/Keepalive#cite_note-4) and TLS[[5\]](https://en.wikipedia.org/wiki/Keepalive#cite_note-5)) implement their own keep-alive feature on top of TCP. It is also common for protocols which maintain a session over a connectionless protocol, e.g. OpenVPN over UDP,[[6\]](https://en.wikipedia.org/wiki/Keepalive#cite_note-6) to implement their own keep-alive.

### Other uses

#### HTTP keepalive

Main article: [HTTP persistent connection](https://en.wanweibaike.com/wiki-HTTP_persistent_connection)

The [Hypertext Transfer Protocol](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) uses the keyword "Keep-Alive" in the "Connection" header to signal that the connection should be kept open for further messages (this is the default in HTTP 1.1, but in HTTP 1.0 the default was to use a new connection for each request/reply pair).[[7\]](https://en.wikipedia.org/wiki/Keepalive#cite_note-7) Despite the similar name, this function is entirely unrelated.



## 应用与实践

1、Redis

`anet.c`

```C
/* Set TCP keep alive option to detect dead peers. The interval option
 * is only used for Linux as we are using Linux-specific APIs to set
 * the probe send time, interval, and count. */
int anetKeepAlive(char *err, int fd, int interval)
{
    int val = 1;

    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) == -1)
    {
        anetSetError(err, "setsockopt SO_KEEPALIVE: %s", strerror(errno));
        return ANET_ERR;
    }

#ifdef __linux__
    /* Default settings are more or less garbage, with the keepalive time
     * set to 7200 by default on Linux. Modify settings to make the feature
     * actually useful. */

    /* Send first probe after interval. */
    val = interval;
    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &val, sizeof(val)) < 0) {
        anetSetError(err, "setsockopt TCP_KEEPIDLE: %s\n", strerror(errno));
        return ANET_ERR;
    }

    /* Send next probes after the specified interval. Note that we set the
     * delay as interval / 3, as we send three probes before detecting
     * an error (see the next setsockopt call). */
    val = interval/3;
    if (val == 0) val = 1;
    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &val, sizeof(val)) < 0) {
        anetSetError(err, "setsockopt TCP_KEEPINTVL: %s\n", strerror(errno));
        return ANET_ERR;
    }

    /* Consider the socket in error state after three we send three ACK
     * probes without getting a reply. */
    val = 3;
    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &val, sizeof(val)) < 0) {
        anetSetError(err, "setsockopt TCP_KEEPCNT: %s\n", strerror(errno));
        return ANET_ERR;
    }
#else
    ((void) interval); /* Avoid unused var warning for non Linux systems. */
#endif

    return ANET_OK;
}

```



## TODO

### tldp TCP Keepalive HOWTO

[2. TCP keepalive overview](https://tldp.org/HOWTO/TCP-Keepalive-HOWTO/overview.html)

[3. Using TCP keepalive under Linux](https://tldp.org/HOWTO/TCP-Keepalive-HOWTO/usingkeepalive.html)



ibm [TCP keepalive](https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-tcp-keepalive)
