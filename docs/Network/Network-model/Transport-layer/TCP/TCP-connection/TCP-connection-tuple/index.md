# TCP connection tuple

一个TCP connection由哪些要素组成，一般说法是4个:

**client IP address, client port number, server IP address, server port number**



## stackoverflow [How many tuples are there in a connection?](https://stackoverflow.com/questions/15761436/how-many-tuples-are-there-in-a-connection)

[Some people](https://stackoverflow.com/questions/152457/what-is-the-difference-between-a-port-and-a-socket) said that there are 4 tuples in a connection

**client IP address, client port number, server IP address, server port number**

[Some](https://stackoverflow.com/questions/489036/how-does-the-socket-api-accept-function-work) said that there are 5

**client IP address, client port number, server IP address, server port number, protocol**

Which one is correct ?



### [A](https://stackoverflow.com/a/15763717)

You've misunderstood the terminology. A TCP *connection* is identified by a 5-tuple. That means *one*tuple, with 5 elements. The five elements are:

1. Protocol. This is often omitted as it is understood that we are talking about TCP, which leaves 4.
2. Source IP address.
3. Source port.
4. Target IP address.
5. Target port.



## networkengineering [Why is a TCP Socket identified by a 4 tuple?](https://networkengineering.stackexchange.com/questions/54344/why-is-a-tcp-socket-identified-by-a-4-tuple)

Newbie to networking here. I'm reading the Computer Networking (3rd edition) book, and in section 3.2 they are discussing multiplexing / demultiplexing for both UDP and TCP.

In the **UDP protocol**, a socket is uniquely identified by the **source IP** and the **source port**.

In the **TCP protocol**, the socket is uniquely identified by the source IP, source port, destination IP, and destination port. Why does the TCP protocol require two extra pieces of information for the receiving host to correctly demultiplex the segment and send it to the correct process?

The only reason I can think of why this is necessary is if clients always send the TCP segment to the same port as the connection-request segment. For example, my browser always sends data to port 80 of the server even though the server has established a TCP socket specifically for that session on a different port. In that case, TCP has to use the source IP and source port information to demultiplex to the correct socket. It can't rely solely on the source IP information, because a single host can establish multiple sessions, but each session has to be on a different port.

The reason why UDP does not have this problem is because the destination IP / port combo identifies the socket to which the process that will handle the request is attached, since in UDP there is no "spawning" of multiple new sockets for requests.

Is this correct or have I reached the wrong conclusion?

