# Application protocol design

双方在进行通信之前，需要首先约定protocol，本文对application protocol design(应用层协议的设计)进行总结。protocol 有时候也被称为data exchange protocol。

## How to design application protocol

在设计application protocol的时候，需要考虑的问题有: 

### 1) Protocol data format

Protocol data format(有时候也被称为data exchange format)的设计是application protocol的主要内容，下面是设计的时候需要考虑的一些内容，在`./Protocol-data-format`章节总结了一些当前被广泛采用的format。

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



### 开源软件的application protocol

#### Redis: RESP 

参见 redis.io [Redis Protocol specification](https://redis.io/topics/protocol)。






