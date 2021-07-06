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



