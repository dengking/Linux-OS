# Application protocol design

双方在进行通信之前，需要首先约定protocol，本文对application protocol design(应用层协议的设计)进行总结。protocol 有时候也被称为data exchange protocol。

## How to design application protocol

在设计application protocol的时候，需要考虑的问题有: 

### 1) Protocol data format

Protocol data format的设计是application protocol的主要内容，下面是设计的时候需要考虑的一些内容，在`./Protocol-data-format`章节总结了一些当前被广泛采用的format。

#### Message boundary

使用TCP的一个非常重要的内容是: 如何描述message boundary？

#### Implementation

在设计protocol的时候，也是需要考虑implementation相关的问题:

1) 成本的、难易程度

2) 性能

> NOTE: 这是在阅读[Redis Protocol specification](https://redis.io/topics/protocol) 时，其中给出的总结:
>
> > - Simple to implement.
> > - Fast to parse.

#### 性能

当考虑到性能的时候，需要思考的方面是非常多的: 

1) 是否能够快速解析

2) playload要尽可能小

影响带宽。

#### Human readable



> NOTE: 这是在阅读[Redis Protocol specification](https://redis.io/topics/protocol) 时，其中给出的总结:
>
> > Human readable



#### Language-neutral

是否语言中立，如果语言中立的话，那么跨语言就非常容易了。

> NOTE: 本节标题源自 [protobuf](https://github.com/protocolbuffers/protobuf)

#### Platform-neutral

是否平台中立。

> NOTE: 本节标题源自 [protobuf](https://github.com/protocolbuffers/protobuf)

### 2) 底层协议

network protocol model是层次化的结构，在设计一个application protocol的时候，需要考虑它的下一层所采用的protocol，目前主要有如下两种:

- TCP
- UDP

### 3) 安全性

安全性是在进行协议设计的时候，需要考虑的一个重要问题。

## Examples

下面结合一些具体的案例来进行分析。

### 国内企业的application protocol

#### 恒生T2协议

T2SDK

#### 华锐ATP交易数据接口规范

参见: http://developer.archforce.cn/topic/1738 	



### 使用struct来描述

每种服务的入参，都有对应的struct类型，这样调用一个服务的入参的时候，传入对应的struct的object(copy一次)，在server端，服务的实现中，直接使用该服务对应的struct进行反序列化即可，可以通过如下的方式来避免copy:

```C++
struct CRequestStruct{};

const void* Request = Recv(); // 接收得到的请求数据
const CRequestStruct * Req = reinterpret_cast<const CRequestStruct *>(Request); // 
```

这种方式能够保证避免多次的copy，但是需要为每个服务都指定一个struct，或者说，需要为每个服务制定具体的protocol，这带来的一个问题就是: 维护的成本。

### 开源软件的application protocol

#### Redis: RESP 

参见 redis.io [Redis Protocol specification](https://redis.io/topics/protocol)。







## cnblogs [软件开发中的几种数据交换协议](https://www.cnblogs.com/winner-0715/p/7693400.html)

## 如何选择数据交换协议

选择什么样的协议跟我们的应用场景有很大的关系。我们需要考虑我们开发是否方便、接口是否容易发布、是否需要考虑带宽占用成本、序列化和反序列化的性能、接口协议的扩展性等等。下面我们看下几个比较常用的交换协议实现。

| 协议          | 实现                                                    | 跨语言   | 性能 | 传输量 | RPC         |
| ------------- | ------------------------------------------------------- | -------- | ---- | ------ | ----------- |
| xml           | 广泛                                                    | 几乎所有 | 低   | 很大   | N（可实现） |
| json          | 广泛                                                    | 大量     | 一般 | 一般   | N（可实现） |
| php serialize | PHPRPC                                                  | 大量     | 一般 | 一般   | Y           |
| hessian       | hessian                                                 | 大量     | 一般 | 小     | Y           |
| thrift        | [thrift](https://thrift.apache.org/)                    | 大量     | 高   | 小     | Y           |
| protobuf      | [protobuf](https://github.com/protocolbuffers/protobuf) | 大量     | 高   | 小     | N（可实现） |
| ice           | ice                                                     | 大量     | 高   | 小     | Y           |
| avro          | [Apache Avro](http://avro.apache.org/)                  | 少量     | 高   | 小     | Y           |
| messagepack   | [messagepack](http://msgpack.org/)                      | 大量     | 高   | 小     | Y           |