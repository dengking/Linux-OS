# TCP SEQ number and ACK number



## packetlife [Understanding TCP Sequence and Acknowledgment Numbers](https://packetlife.net/blog/2010/jun/7/understanding-tcp-sequence-acknowledgment-numbers/)

> NOTE: 这篇文章，结合[Wireshark](http://www.wireshark.org/)、具体案例来讲解，非常值得阅读

This article aims to help you become more comfortable examining TCP sequence and acknowledgement numbers in the [Wireshark](http://www.wireshark.org/) packet analyzer.

Before we start, be sure to open [the example capture](https://packetlife.net/media/blog/attachments/424/TCP_example.cap) in Wireshark and play along.

The example capture contains a single HTTP request to a web server, in which the client web browser requests a single image file, and the server returns an HTTP/1.1 200 (OK) response which includes the file requested. You can right-click on any of the TCP packets within this capture and select **Follow TCP Stream** to open the raw contents of the TCP stream in a separate window for inspection. Traffic from the client is shown in red, and traffic from the server in blue.

### The Three-Way Handshake

TCP utilizes a number of flags, or 1-bit boolean fields, in its header to control the state of a connection. The three we're most interested in here are:

- **SYN** - (Synchronize) Initiates a connection
- **FIN** - (Final) Cleanly terminates a connection
- **ACK** - Acknowledges received data

As we'll see, a packet can have multiple flags set.

> NOTE: 典型的例子就是 SYN-ACK

Select `packet #1` in Wireshark and expand the TCP layer analysis in the middle pane, and further expand the "Flags" field within the TCP header. Here we can see all of the TCP flags broken down. Note that the `SYN` flag is on (set to 1).

![tcp_syn.png](https://packetlife.net/media/blog/attachments/426/tcp_syn.png)

Now do the same for `packet #2`. Notice that it has two flags set: ACK to acknowledge the receipt of the client's SYN packet, and SYN to indicate that the server also wishes to establish a TCP connection.

![tcp_synack.png](https://packetlife.net/media/blog/attachments/427/tcp_synack.png)

Packet #3, from the client, has only the ACK flag set. These three packets complete the initial TCP three-way handshake.



## cnblogs [TCP 中的Sequence Number](https://www.cnblogs.com/JenningsMao/p/9487252.html)



## voidcn [TCP序列号的最大值](http://www.voidcn.com/article/p-gccvxxfz-byo.html)





## See also

stackoverflow [TCP: How are the seq / ack numbers generated?](https://stackoverflow.com/questions/692880/tcp-how-are-the-seq-ack-numbers-generated)

stackoverflow [TCP Sequence Number](https://stackoverflow.com/questions/10452855/tcp-sequence-number)