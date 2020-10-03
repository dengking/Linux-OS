# Transmission Control Protocol

## wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)

The **Transmission Control Protocol** (**TCP**) is one of the main [protocols](https://en.wikipedia.org/wiki/Communications_protocol) of the [Internet protocol suite](https://en.wikipedia.org/wiki/Internet_protocol_suite). It originated in the initial network implementation in which it complemented the [Internet Protocol](https://en.wikipedia.org/wiki/Internet_Protocol) (IP). Therefore, the entire suite is commonly referred to as *TCP/IP*. 

TCP provides [reliable](https://en.wikipedia.org/wiki/Reliability_(computer_networking)), ordered, and [error-checked](https://en.wikipedia.org/wiki/Error_detection_and_correction) delivery of a stream of [octets](https://en.wikipedia.org/wiki/Octet_(computing)) (bytes) between applications running on hosts communicating via an IP network. 

TCP is [connection-oriented](https://en.wikipedia.org/wiki/Connection-oriented_communication), and a connection between client and server is established before data can be sent. The server must be listening (passive(被动) open) for connection requests from clients before a connection is established. Three-way handshake (active(主动) open), [retransmission](https://en.wikipedia.org/wiki/Retransmission_(data_networks)), and error-detection adds to reliability but lengthens [latency](https://en.wikipedia.org/wiki/Latency_(engineering)). 

> NOTE: 上面描述了TCP的特性

Major internet applications such as the [World Wide Web](https://en.wikipedia.org/wiki/World_Wide_Web), [email](https://en.wikipedia.org/wiki/Email), [remote administration](https://en.wikipedia.org/wiki/Remote_administration), and [file transfer](https://en.wikipedia.org/wiki/File_transfer) rely on TCP. 



### Network function

**The Transmission Control Protocol** provides a communication service at an intermediate level between an application program and the **Internet Protocol**(即Internet Layer). It provides host-to-host **connectivity** at the [transport layer](https://en.wikipedia.org/wiki/Transport_layer) of the [Internet model](https://en.wikipedia.org/wiki/Internet_model). 

> NOTE: 上面这段话需要结合`Network\Theory\Network-protocol-model.md`中的"Internet protocol suite by layer"章节的内容来进行理解

An application does not need to know the particular mechanisms for sending data via a link to another host, such as the required [IP fragmentation](https://en.wikipedia.org/wiki/IP_fragmentation) to accommodate the [maximum transmission unit](https://en.wikipedia.org/wiki/Maximum_transmission_unit) of the transmission medium. At the transport layer, TCP handles all **handshaking** and **transmission** details and presents an **abstraction** of the **network connection** to the application typically through a [network socket](https://en.wikipedia.org/wiki/Network_socket) interface.

> NOTE: 核心在于“abstraction”，可以认为TCP is an abstraction。



### TCP segment structure

Transmission Control Protocol accepts data from a data stream, divides it into chunks, and adds a TCP header creating a **TCP segment**. The **TCP segment** is then [encapsulated](https://en.wikipedia.org/wiki/Encapsulation_(networking)) into an **Internet Protocol (IP) datagram**, and exchanged with peers.[[4\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-4)

The term *TCP packet* appears in both informal and formal usage, whereas in more precise terminology *segment* refers to the TCP [protocol data unit](https://en.wikipedia.org/wiki/Protocol_data_unit) (PDU), *datagram*[[5\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-5)to the IP PDU, and *frame* to the data link layer PDU:

> Processes transmit data by calling on the TCP and passing buffers of data as arguments. The TCP packages the data from these buffers into **segments** and calls on the internet module [e.g. IP] to transmit each **segment** to the destination TCP.[[6\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-6)

A TCP segment consists of a segment *header* and a *data* section. The TCP header contains 10 mandatory fields, and an optional extension field (*Options*, pink background in table).

The data section follows the header. Its contents are the payload data carried for the application. The length of the data section is **not** specified in the **TCP segment header**. It can be calculated by subtracting the combined length of the **TCP header** and the encapsulating **IP header** from the total IP datagram length (specified in the IP header).





- Source port (16 bits)

  Identifies the **sending port**.

- Destination port (16 bits)

  Identifies the **receiving port**. 

  需要注意的是在TCP协议的header中仅有port而无IP；IP是在IP协议中需要的；

- Sequence number (32 bits)

  Has a dual role:

  - If the SYN flag is set (1), then this is the initial sequence number. The sequence number of the actual first data byte and the acknowledged number in the corresponding ACK are then this sequence number plus 1.
  - If the SYN flag is clear (0), then this is the accumulated sequence number of the first data byte of this segment for the current session.

- Acknowledgment number (32 bits)

  If the ACK flag is set then the value of this field is the next sequence number that the sender of the ACK is expecting. This acknowledges receipt of all prior bytes (if any). The first ACK sent by each end acknowledges the other end's initial sequence number itself, but no data.

- Data offset (4 bits)

  Specifies the size of the TCP header in 32-bit [words](https://en.wikipedia.org/wiki/Word_(computer_architecture)). The minimum size header is 5 words and the maximum is 15 words thus giving the minimum size of 20 bytes and maximum of 60 bytes, allowing for up to 40 bytes of options in the header. This field gets its name from the fact that it is also the offset from the start of the TCP segment to the actual data.

- Reserved (3 bits)

  For future use and should be set to zero.

- Flags (9 bits) (aka Control bits)

  Contains 9 1-bit flags

  - NS (1 bit): ECN-nonce - concealment protection (experimental: see [RFC 3540](https://tools.ietf.org/html/rfc3540)).

  - CWR (1 bit): Congestion Window Reduced (CWR) flag is set by the sending host to indicate that it received a TCP segment with the ECE flag set and had responded in congestion control mechanism (added to header by [RFC 3168](https://tools.ietf.org/html/rfc3168)).

  - ECE (1 bit): ECN-Echo has a dual role, depending on the value of the SYN flag. It indicates:If the SYN flag is set (1), that the TCP peer is [ECN](https://en.wikipedia.org/wiki/Explicit_Congestion_Notification) capable.If the SYN flag is clear (0), that a packet with Congestion Experienced flag set (ECN=11) in the IP header was received during normal transmission (added to header by [RFC 3168](https://tools.ietf.org/html/rfc3168)). This serves as an indication of network congestion (or impending congestion) to the TCP sender.

  - URG (1 bit): indicates that the Urgent pointer field is significant

  - ACK (1 bit): indicates that the **Acknowledgment field** is significant. All packets after the initial SYN packet sent by the client should have this flag set.

  - PSH (1 bit): Push function. Asks to push the buffered data to the receiving application.

  - RST (1 bit): Reset the connection

  - SYN (1 bit): **Synchronize sequence numbers**. Only the **first packet** sent from each end should have this flag set. Some other flags and fields change meaning based on this flag, and some are only valid when it is set, and others when it is clear.

    ***SUMMARY*** : 标识开始传输

  - FIN (1 bit): Last packet from sender.

    ***SUMMARY*** : 标识完成了传输

- Window size (16 bits)

  The size of the *receive window*, which specifies the number of window size units (by default, bytes) (beyond the segment identified by the sequence number in the acknowledgment field) that the sender of this segment is currently willing to receive (*see Flow control and Window Scaling*).

- Checksum (16 bits)

  The 16-bit [checksum](https://en.wikipedia.org/wiki/Checksum) field is used for error-checking of the header, the Payload and a Pseudo-Header. The Pseudo-Header consists of the [Source IP Address](https://en.wikipedia.org/wiki/IPv4#Source_address), the [Destination IP Address](https://en.wikipedia.org/wiki/IPv4#Destination_address), the [protocol number](https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers) for the TCP-Protocol (0x0006) and the length of the TCP-Headers including Payload (in Bytes).

- Urgent pointer (16 bits)

  if the URG flag is set, then this 16-bit field is an offset from the sequence number indicating the last urgent data byte.

- Options (Variable 0–320 bits, divisible by 32)

  The length of this field is determined by the data offset field. Options have up to three fields: Option-Kind (1 byte), Option-Length (1 byte), Option-Data (variable). The Option-Kind field indicates the type of option, and is the only field that is not optional. Depending on what kind of option we are dealing with, the next two fields may be set: the Option-Length field indicates the total length of the option, and the Option-Data field contains the value of the option, if applicable. For example, an Option-Kind byte of 0x01 indicates that this is a No-Op option used only for padding, and does not have an Option-Length or Option-Data byte following it. An Option-Kind byte of 0 is the End Of Options option, and is also only one byte. An Option-Kind byte of 0x02 indicates that this is the Maximum Segment Size option, and will be followed by a byte specifying the length of the MSS field (should be 0x04). This length is the total length of the given options field, including Option-Kind and Option-Length bytes. So while the MSS value is typically expressed in two bytes, the length of the field will be 4 bytes (+2 bytes of kind and length). In short, an MSS option field with a value of 0x05B4 will show up as (0x02 0x04 0x05B4) in the TCP options section.

  Some options may only be sent when SYN is set; they are indicated below as `[SYN]`. Option-Kind and standard lengths given as (Option-Kind,Option-Length).0 (8 bits): End of options list1 (8 bits): No operation (NOP, Padding) This may be used to align option fields on 32-bit boundaries for better performance.2,4,*SS* (32 bits): Maximum segment size (*see maximum segment size*) `[SYN]`3,3,*S* (24 bits): Window scale (*see window scaling for details*) `[SYN]`[[7\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-7)4,2 (16 bits): Selective Acknowledgement permitted. `[SYN]` (*See selective acknowledgments for details*)[[8\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-8)5,*N,BBBB,EEEE,...* (variable bits, *N* is either 10, 18, 26, or 34)- Selective ACKnowledgement (SACK)[[9\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-9) These first two bytes are followed by a list of 1–4 blocks being selectively acknowledged, specified as 32-bit begin/end pointers.8,10,*TTTT,EEEE* (80 bits)- Timestamp and echo of previous timestamp (*see TCP timestamps for details*)[[10\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-10)

  The remaining options are historical, obsolete, experimental, not yet standardized, or unassigned. Option number assignments are maintained by the IANA[[11\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-11).

- Padding

  The TCP header padding is used to ensure that the TCP header ends, and data begins, on a 32 bit boundary. The padding is composed of zeros.[[12\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-12)



## Protocol operation

**TCP protocol** operations may be divided into three phases. **Connections** must be properly established in a multi-step handshake process (*connection establishment*) before entering the *data transfer* phase. After data transmission is completed, the *connection termination* closes(关闭) established virtual circuits and releases all allocated resources.

A TCP connection is managed by an **operating system** through a programming interface that represents the **local end-point** for communications, the *Internet socket*. During the lifetime of a TCP connection **the local end-point** undergoes a series of [state](https://en.wikipedia.org/wiki/State_(computer_science)) changes:[[13\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-13)

#### LISTEN

(server) represents waiting for a **connection request** from any remote TCP and port.

#### SYN-SENT

(client) represents waiting for a **matching connection request** after having sent a **connection request**.

#### SYN-RECEIVED

(server) represents waiting for a confirming connection request acknowledgment after having both received and sent a **connection request**.

#### ESTABLISHED

(both server and client) represents an open connection, data received can be delivered to the user. The normal state for the data transfer phase of the connection.

#### FIN-WAIT-1

(both server and client) represents waiting for a **connection termination request** from the remote TCP, or an **acknowledgment** of the **connection termination request** previously sent.

#### FIN-WAIT-2

(both server and client) represents waiting for a **connection termination request** from the remote TCP.

#### CLOSE-WAIT

(both server and client) represents waiting for a **connection termination request** from the **local user**.

#### CLOSING

(both server and client) represents waiting for a **connection termination request acknowledgment** from the **remote TCP**.

#### LAST-ACK

(both server and client) represents waiting for an acknowledgment of the connection termination request previously sent to the remote TCP (which includes an acknowledgment of its connection termination request).

#### TIME-WAIT

(either server or client) represents waiting for enough time to pass to be sure the remote TCP received **the acknowledgment of its connection termination request**. [According to [RFC 793](https://tools.ietf.org/html/rfc793) a connection can stay in `TIME-WAIT` for a maximum of four minutes known as two [MSL](https://en.wikipedia.org/wiki/Maximum_Segment_Lifetime) (maximum segment lifetime).]

***SUMMARY*** : 第一句话的含义是：**本端**等待足够的时间以确保remote TCP(即通信的**对端**)接收到了由**本端**发送给对端的acknowledgment（这个acknowledgment是对对端发送过来的connection termination request的`ACK`)

#### CLOSED

(both server and client) represents no connection state at all.



### Connection establishment

To establish a connection, TCP uses a three-way [handshake](https://en.wikipedia.org/wiki/Handshaking). Before a client attempts to connect with a server, the server must first **bind** to and **listen** at a **port** to open it up for connections: this is called a **passive open**. Once the **passive open** is established, a client may initiate an **active open**. To establish a **connection**, the three-way (or 3-step) handshake occurs:

1. **SYN**: The **active open** is performed by the client sending a **SYN** to the server. The client sets the segment's **sequence number** to a random value A.
2. **SYN-ACK**: In response, the server replies with a SYN-ACK. The **acknowledgment number** is set to one more than the **received sequence number** i.e. `A+1`, and the **sequence number** that the server chooses for the packet is another random number, B.
3. **ACK**: Finally, the client sends an ACK back to the server. The **sequence number** is set to the **received acknowledgement value** i.e. `A+1`, and the **acknowledgement number** is set to one more than the received sequence number i.e. B+1.

***SUMMARY*** : 显然TCP协议要求所有的通信都是request-response的，即每个request，都会收到一个response，当这个response是由于acknowledge的时候，我们往往将其称之为`ACK`，那该协议是如何实现response A是request A的response而不是request B的response呢？是使用sequence number和received sequence number吗？对一个endpoint而言，它的sequence number是单调递增的吗？

At this point, both the client and server have received an acknowledgment of the connection. The steps 1, 2 establish the connection parameter (sequence number) for one direction and it is acknowledged. The steps 2, 3 establish the connection parameter (sequence number) for the other direction and it is acknowledged. With these, a **full-duplex communication** is established.



### Connection termination

The **connection termination phase** uses a **four-way handshake**, with each side of the connection terminating independently. When an endpoint wishes to stop its half of the connection, it transmits a **FIN packet**, which the other end acknowledges with an `ACK`. Therefore, a typical tear-down requires a pair of `FIN` and `ACK` segments from each **TCP endpoint**. After the side **that**(引导定语从句) sent the first `FIN` has responded with the final `ACK`, it waits for a **timeout** before finally closing the connection, during which time **the local port** is unavailable for new connections; this prevents confusion due to **delayed packets** being delivered during subsequent connections.

***SUMMARY*** : 最后一段话的意思是：在这段时间内，这个port是不能够用于新的connection的，这样做的原因是：如果允许，可能导致delayed packet被后续在这个port上的connection进行传输；

***THINKING*** : why connection establishment使用three-way handshake，而connection termination使用four-wary handshake？我想这其中的差别在于传输buffer中的数据；

A connection can be ["half-open"](https://en.wikipedia.org/wiki/TCP_half-open), in which case one side has terminated its end, but the other has not. The side that has terminated can no longer send any data into the connection, but the other side can. The terminating side should continue reading the data until the other side terminates as well.

It is also possible to terminate the connection by a 3-way handshake, when host A sends a `FIN` and host B replies with a `FIN` & `ACK` (merely combines 2 steps into one) and host A replies with an `ACK`.[[14\]](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#cite_note-14)

Some host TCP stacks may implement a half-duplex close sequence, as [Linux](https://en.wikipedia.org/wiki/Linux) or [HP-UX](https://en.wikipedia.org/wiki/HP-UX) do. If such a host actively closes a connection but still has not read all the incoming data the stack already received from the link, this host sends a `RST` instead of a `FIN` (Section 4.2.2.13 in [RFC 1122](https://tools.ietf.org/html/rfc1122)). This allows a TCP application to be sure the remote application has read all the data the former sent—waiting the FIN from the remote side, when it actively closes the connection. But the remote TCP stack cannot distinguish between a *Connection Aborting RST* and *Data Loss RST*. Both cause the remote stack to lose all the data received.

Some application protocols using the TCP open/close handshaking for the application protocol open/close handshaking may find the RST problem on active close. As an example:

```
s = connect(remote);
send(s, data);
close(s);
```

For a program flow like above, a TCP/IP stack like that described above does not guarantee that all the data arrives to the other application if unread data has arrived at this end.

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/5/55/TCP_CLOSE.svg/260px-TCP_CLOSE.svg.png)





Connection termination