# Connection establishment



## wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) # 4.1 Connection establishment

To establish a connection, TCP uses a three-way [handshake](https://en.wikipedia.org/wiki/Handshaking). Before a client attempts to connect with a server, the server must first **bind** to and **listen** at a **port** to open it up for connections: this is called a **passive open**. Once the **passive open** is established, a client may initiate an **active open**. To establish a **connection**, the three-way (or 3-step) handshake occurs:

1) **SYN**: The **active open** is performed by the client sending a **SYN** to the server. The client sets the segment's **sequence number** to a random value `A`.

2) **SYN-ACK**: In response, the server replies with a SYN-ACK. The **acknowledgment number** is set to one more than the **received sequence number** i.e. `A+1`, and the **sequence number** that the server chooses for the packet is another random number, `B`.

> NOTE: SYN-ACK其实可以看做是同时发送SYN和ACK

3) **ACK**: Finally, the client sends an ACK back to the server. The **sequence number** is set to the **received acknowledgement value** i.e. `A+1`, and the **acknowledgement number** is set to one more than the received sequence number i.e. `B+1`.

> NOTE: 为什么是plus 1？在`Network\Theory\TCP\TCP-SEQ-number-and-ACK-number.md`的cnblogs [TCP 中的Sequence Number](https://www.cnblogs.com/JenningsMao/p/9487252.html)中对这个问题进行解释



At this point, both the client and server have received an acknowledgment of the connection. The steps 1, 2 establish the connection parameter (**sequence number**) for one direction and it is acknowledged. The steps 2, 3 establish the connection parameter (**sequence number**) for the other direction and it is acknowledged. With these, a **full-duplex communication** is established.

> NOTE: full-duplex，每个direction都有对应的connection parameter: sequence number。

> NOTE: 在文章packetlife [Understanding TCP Sequence and Acknowledgment Numbers](https://packetlife.net/blog/2010/jun/7/understanding-tcp-sequence-acknowledgment-numbers/) 中展示了如何使用wireshark来观察connection establishment的过程，这篇文章收录在`Network\Theory\TCP\TCP-SEQ-number-and-ACK-number.md`中。

