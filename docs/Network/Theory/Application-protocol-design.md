# Application protocol design

双方在进行通信之前，需要首先约定protocol，本文对application protocol design(应用层协议的设计)进行总结。protocol 有时候也被称为data exchange protocol、data exchange format。

## How to design

在设计application protocol的时候，需要考虑的问题有: 

### Message boundary

使用TCP的一个非常重要的内容是: 如何描述message boundary？

### Implementation

在设计protocol的时候，也是需要考虑implementation相关的问题:

1) 成本的、难易程度

2) 性能

> NOTE: 这是在阅读[Redis Protocol specification](https://redis.io/topics/protocol) 时，其中给出的总结:
>
> > - Simple to implement.
> > - Fast to parse.

### 性能

当考虑到性能的时候，需要思考的方面是非常多的: 

1) 是否能够快速解析

2) playload要尽可能小

### Human readable



> NOTE: 这是在阅读[Redis Protocol specification](https://redis.io/topics/protocol) 时，其中给出的总结:
>
> > Human readable



### Language-neutral

是否语言中立，如果语言中立的话，那么跨语言就非常容易了。

> NOTE: 本节标题源自 [protobuf](https://github.com/protocolbuffers/protobuf)

### Platform-neutral

是否平台中立。

> NOTE: 本节标题源自 [protobuf](https://github.com/protocolbuffers/protobuf)





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





## TODO

cnblogs [软件开发中的几种数据交换协议](https://www.cnblogs.com/winner-0715/p/7693400.html)