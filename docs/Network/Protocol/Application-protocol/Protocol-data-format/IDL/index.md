# 关于本章

使用IDL的方式，我们能够实现以language-neutral的方式来描述protocol data format，通过IDL compiler来实现将IDL描述的protocol data format编译为具体programming language implementation，从而实现了抽象，实现了cross-language、cross-plateform。

目前实现这种方式的有:

1) [Protobuf](https://github.com/protocolbuffers/protobuf)

2) [Thrift](https://thrift.apache.org/)

3) [Apache Avro](http://avro.apache.org/)

## 时代背景

为什么它们会流行？其实这是由当前的时代背景所决定的，下面是我的总结: 

在cloud computing、distributed-computing、microservice大行其道的今天，这种方式是极具价值。

在文章eprosima [Apache Thrift vs Protocol Buffers vs Fast Buffers](https://www.eprosima.com/index.php/resources-all/performance/apache-thrift-vs-protocol-buffers-vs-fast-buffers) 中有这样的描述: 

> Middleware alternatives based on verbose serialization formats such as XML or JSON, used in Web Services and REST, expose very poor performance. The emergence of cloud computing and service integration in large distributed systems is driving companies and developers to consider again fast binary formats and lightweight Remote Procedure Call (RPC) frameworks. We compared Apache Thrift vs Protocol Buffers vs Fast Buffers.

在文章 medium [Supercharge your REST APIs with Protobuf](https://medium.com/swlh/supercharge-your-rest-apis-with-protobuf-b38d3d7a28d3) 中有这样的描述:

> This problem magnifies(放大) when you have a micro-services architecture and have 100s (if not 1000s) of services talking to each other over JSON and you accidentally change the JSON response of one of the service.

## 实现的共性

在文章 medium [Use **Binary** Encoding Instead of JSON](https://medium.com/better-programming/use-binary-encoding-instead-of-json-dec745ec09b6) 中，对它们实现上的共性有较好的分析:

> All three provide efficient, cross-language serialization of data using a **schema** and have **code generation tools**. All three support **schema evolution** by ensuring both **backward** and **forward** compatibility.

> NOTE: 由于使用schema，所以不需要为数据带上field；
>
> 支持schema evolution的特性是非常有价值的

在`Network\Protocol\Application-protocol\Protocol-data-format\Binary-VS-textual`中收录了这篇文章。

## Thrift VS Protobuf

## stackoverflow [Biggest differences of Thrift vs Protocol Buffers?](https://stackoverflow.com/questions/69316/biggest-differences-of-thrift-vs-protocol-buffers)

What are the biggest pros and cons of [Apache Thrift](http://incubator.apache.org/thrift/) vs [Google's Protocol Buffers](http://code.google.com/apis/protocolbuffers/)?

**A**:

They both offer many of the same features; however, there are some differences:

- Thrift supports 'exceptions'
- Protocol Buffers have much better documentation/examples
- Thrift has a builtin `Set` type
- Protocol Buffers allow "extensions" - you can extend an external proto to add extra fields, while still allowing external code to operate on the values. There is no way to do this in Thrift
- I find Protocol Buffers much easier to read

Basically, they are fairly equivalent (with Protocol Buffers slightly more efficient from what I have read).

**A**: 

**RPC** is another key difference. Thrift generates code to implement RPC clients and servers wheres Protocol Buffers seems mostly designed as a **data-interchange format** alone.



## eprosima [Apache Thrift vs Protocol Buffers vs Fast Buffers](https://www.eprosima.com/index.php/resources-all/performance/apache-thrift-vs-protocol-buffers-vs-fast-buffers)

> NOTE: 这篇文章从performance的角度对它们进行了对比

## williamqliu [Data Exchange Formats (Avro, Thrift, Protocol Buffers)](https://williamqliu.github.io/2020/01/02/data-exchange-avro-thrift-protocolbuffers.html)

> NOTE: 这篇文章重要从schema evolution的角度对它们进行了对比。关于schema evolution，将在`./Schema-evaluation.md`中进行展开说明。

