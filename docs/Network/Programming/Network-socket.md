# [Network socket](https://en.wikipedia.org/wiki/Network_socket)

A **network socket** is an internal endpoint for sending or receiving data within a [node](https://en.wikipedia.org/wiki/Node_(networking)) on a [computer network](https://en.wikipedia.org/wiki/Computer_network). Concretely, it is a representation of this endpoint in networking software ([protocol stack](https://en.wikipedia.org/wiki/Protocol_stack)), such as an entry in a table (listing communication protocol, destination, status, etc.), and is a form of [system resource](https://en.wikipedia.org/wiki/System_resource).

The term *socket* is analogous to physical [female connectors](https://en.wikipedia.org/wiki/Female_connector), communication between two nodes through a [channel](https://en.wikipedia.org/wiki/Channel_(communications)) being visualized as a cable with two [male connectors](https://en.wikipedia.org/wiki/Male_connector) plugging into sockets at each node. Similarly, the term *port* (another term for a **female connector**) is used for *external* endpoints at a node, and the term *socket* is also used for an internal endpoint of local [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication) (IPC) (not over a network). However, the analogy is strained, as network communication need not be one-to-one or have a dedicated [communication channel](https://en.wikipedia.org/wiki/Communication_channel).

术语套接字类似于物理母连接器，通过信道将两个节点之间的通信视为电缆，其中两个公连接器插入每个节点的插座。 类似地，术语端口（女性连接器的另一个术语）用于节点处的外部端点，术语套接字也用于本地进程间通信（IPC）的内部端点（不通过网络）。 然而，类比是紧张的，因为网络通信不需要是一对一的或具有专用的通信信道。

## Use

A [process](https://en.wikipedia.org/wiki/Process_(computing)) can refer to a socket using a *socket descriptor*, a type of [handle](https://en.wikipedia.org/wiki/Handle_(computing)). A process first requests that the **protocol stack** create a **socket**, and the **stack** returns a **descriptor** to the process so it can identify the socket. The process then passes the **descriptor** back to the **protocol stack** when it wishes to send or receive data using this **socket**.

Unlike [ports](https://en.wikipedia.org/wiki/Port_(computer_networking)), sockets are specific to one node; they are local resources and cannot be referred to directly by other nodes. Further, sockets are not necessarily associated with a **persistent connection** ([channel](https://en.wikipedia.org/wiki/Channel_(communications))) for communication between two nodes, nor is there necessarily some single other endpoint. For example, a [datagram socket](https://en.wikipedia.org/wiki/Datagram_socket) can be used for [connectionless communication](https://en.wikipedia.org/wiki/Connectionless_communication), and a [multicast](https://en.wikipedia.org/wiki/Multicast) socket can be used to send to multiple nodes. However, in practice for [internet](https://en.wikipedia.org/wiki/Internet) communication, sockets are generally used to connect to a specific endpoint and often with a persistent connection.

***SUMMARY*** : socket的行为由它的protocol来指定；

## Socket addresses

In practice, *socket* usually refers to a socket in an [Internet Protocol](https://en.wikipedia.org/wiki/Internet_Protocol) (IP) network (where a socket may be called an **Internet socket**), in particular for the [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) (TCP), which is a protocol for one-to-one connections. In this context, sockets are assumed to be associated with a specific **socket address**, namely the [IP address](https://en.wikipedia.org/wiki/IP_address) and a [port number](https://en.wikipedia.org/wiki/Port_number) for the local node, and there is a corresponding socket address at the foreign node (other node), which itself has an associated socket, used by the foreign process. Associating a socket with a socket address is called *binding*.

***SUMMARY*** : 是否是所有的socket都需要***binding***？不是的，参见《networking-code.md》，其中展示了基本的TCP和UDP socket的编程范式；

Note that while a local process can communicate with a foreign process by sending or receiving data to or from a foreign *socket address*, it does not have access to the foreign *socket* itself, nor can it use the foreign *socket descriptor*, as these are both internal to the foreign node. For example, in a connection between `10.20.30.40:4444` and `50.60.70.80:8888` (local IP address:local port, foreign IP address:foreign port), there will also be an associated socket at each end, corresponding to the internal representation of the connection by the protocol stack on that node. These are referred to locally by numerical socket descriptors, say 317 at one side and 922 at the other. A process on node 10.20.30.40 can request to communicate with node 50.60.70.80 on port 8888 (request that the protocol stack create a socket to communicate with that destination), and once it has created a socket and received a socket descriptor (317), it can communicate via this socket by using the descriptor (317). The protocol stack will then forward data to and from node 50.60.70.80 on port 8888. However, a process on node 10.20.30.40 cannot request to communicate based on the foreign socket descriptor, (e.g. "socket 922" or "socket 922 on node 50.60.70.80") as these are internal to the foreign node and are not usable by the protocol stack on node 10.20.30.40.





## Socket pairs

Communicating local and remote sockets are called **socket pairs**. Each socket pair is described by a unique [4-tuple](https://en.wikipedia.org/wiki/4-tuple) consisting of source and destination IP addresses and port numbers, i.e. of local and remote socket addresses.[[8\]](https://en.wikipedia.org/wiki/Network_socket#cite_note-8)[[9\]](https://en.wikipedia.org/wiki/Network_socket#cite_note-9) As seen in the discussion above, in the TCP case, each unique socket pair 4-tuple is assigned a socket number, while in the UDP case, each unique local socket address is assigned a socket number.

***SUMMARY*** :[How many tuples are there in a connection?](https://stackoverflow.com/questions/15761436/how-many-tuples-are-there-in-a-connection)