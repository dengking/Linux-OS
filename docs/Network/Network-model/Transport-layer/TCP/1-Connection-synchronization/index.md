# Connection establishment

参见:

1、wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) # 4.1 Connection establishment



## 为什么需要三次握手？

在如下文章中，对这个问题进行了回答:

1、networkengineering [Why do we need a 3-way handshake? Why not just 2-way?](https://networkengineering.stackexchange.com/questions/24068/why-do-we-need-a-3-way-handshake-why-not-just-2-way)

2、coolshell [TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)

### networkengineering [Why do we need a 3-way handshake? Why not just 2-way?](https://networkengineering.stackexchange.com/questions/24068/why-do-we-need-a-3-way-handshake-why-not-just-2-way)



A

> NOTE: 
>
> 一、简而言之，通信双方需要进行同步

Break down the handshake into what it is really doing.

In TCP, the two parties keep track of what they have sent by using a Sequence number. Effectively it ends up being a running byte count of everything that was sent. The receiving party can use the opposite speaker's sequence number to acknowledge what it has received.

But the sequence number doesn't start at 0. It starts at the ISN (Initial Sequence Number), which is a randomly chosen value. And since TCP is a bi-directional communication, both parties can "speak", and therefore both must randomly generate an ISN as their starting Sequence Number. Which in turn means, both parties need to notify the other party of their starting ISN.

So you end up with this sequence of events for a start of a TCP conversation between Alice and Bob:

```
Alice ---> Bob    SYNchronize with my Initial Sequence Number of X
Alice <--- Bob    I received your syn, I ACKnowledge that I am ready for [X+1]
Alice <--- Bob    SYNchronize with my Initial Sequence Number of Y
Alice ---> Bob    I received your syn, I ACKnowledge that I am ready for [Y+1]
```

Notice, four events are occurring:

1. Alice picks an ISN and **SYNchronizes** it with Bob.
2. Bob **ACKnowledges** the ISN.
3. Bob picks an ISN and **SYNchronizes** it with Alice.
4. Alice **ACKnowledges** the ISN.

In actuality though, the middle two events (#2 and #3) happen in the same packet. What makes a packet a `SYN` or `ACK` is simply a binary flag turned on or off inside each [TCP header](http://www.freesoft.org/CIE/Course/Section4/8.htm), so there is nothing preventing both of these flags from being enabled on the same packet. So the three-way handshake ends up being:

```
Bob <--- Alice         SYN
Bob ---> Alice     SYN ACK 
Bob <--- Alice     ACK     
```

Notice the two instances of "SYN" and "ACK", one of each, in both directions.

------

So to come back to your question, why not just use a two-way handshake? The short answer is because a two way handshake would only allow one party to establish an ISN, and the other party to acknowledge it. Which means only one party can send data.

But TCP is a bi-directional communication protocol, which means either end ought to be able to send data reliably. Both parties need to establish an ISN, and both parties need to acknowledge the other's ISN.

So in effect, what you have is exactly your description of the two-way handshake, but *in each direction*. Hence, four events occurring. And again, the middle two flags happen in the same packet. As such three packets are involved in a full TCP connection initiation process.
