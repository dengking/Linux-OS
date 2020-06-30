# Byte stream and character stream and bitstream

## Byte stream VS character stream

geeksforgeeks [Character Stream Vs Byte Stream in Java](https://www.geeksforgeeks.org/character-stream-vs-byte-stream-java/)

stackoverflow [Byte Stream and Character stream](https://stackoverflow.com/questions/3013996/byte-stream-and-character-stream)

iitk [Character Streams versus Byte Streams](http://www.iitk.ac.in/esc101/05Aug/tutorial/post1.0/converting/charVsByteStreams.html)

通过上述文章可以总结：byte stream和character stream的主要差别在于每次处理的unit不同：

byte stream的unit是byte，character stream的unit是character；一个character由一个或者多个byte组成。

## Byte stream VS bit stream

[Difference between byte stream and bit stream](https://stackoverflow.com/questions/35627938/difference-between-byte-stream-and-bit-stream)

## 维基百科[Bitstream](https://en.wikipedia.org/wiki/Bitstream)

A **bitstream** (or **bit stream**), also known as **binary sequence**, is a [sequence](https://en.wikipedia.org/wiki/Sequence) of [bits](https://en.wikipedia.org/wiki/Bit).

A **bytestream** is a sequence of [bytes](https://en.wikipedia.org/wiki/Byte). Typically, each byte is an 8-bit quantity ([octets](https://en.wikipedia.org/wiki/Octet_(computing))), and so the term **octet stream** is sometimes used interchangeably. An octet may be encoded as a sequence of 8 bits in multiple different ways (see [endianness](https://en.wikipedia.org/wiki/Endianness)) so there is no unique and direct translation between **bytestreams** and **bitstreams**.

**Bitstreams** and **bytestreams** are used extensively in [telecommunications](https://en.wikipedia.org/wiki/Telecommunications) and [computing](https://en.wikipedia.org/wiki/Computing). For example, [synchronous](https://en.wikipedia.org/wiki/Synchronous) bitstreams are carried by [SONET](https://en.wikipedia.org/wiki/SONET), and [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) transports an [asynchronous](https://en.wikipedia.org/wiki/Asynchronous_communication) bytestream.