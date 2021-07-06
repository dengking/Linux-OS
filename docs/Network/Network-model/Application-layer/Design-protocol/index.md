# Application protocol design

双方在进行通信之前，需要首先约定protocol，本文对application protocol design(应用层协议的设计)进行总结。protocol 有时候也被称为data exchange protocol。

## How to design application protocol

在设计application protocol的时候，需要考虑的问题有: 

### Message boundary

使用TCP的一个非常重要的内容是: 如何描述message boundary？



### 底层协议

network protocol model是层次化的结构，在设计一个application protocol的时候，需要考虑它的下一层所采用的protocol，目前主要有如下两种:

1、TCP

2、UDP



### 安全性

安全性是在进行协议设计的时候，需要考虑的一个重要问题。



### 性能

当考虑到性能的时候，需要思考的方面是非常多的: 

一、fast to parse

> NOTE: 
>
> 这是在阅读[Redis Protocol specification](https://redis.io/topics/protocol) 时，其中给出的总结



二、便于实现high concurrent server

1、避免`TIME_WAIT`

这在下面文章中进行了讨论

stackoverflow [When is TCP option SO_LINGER (0) required?](https://stackoverflow.com/questions/3757289/when-is-tcp-option-so-linger-0-required) # [A](https://stackoverflow.com/a/13088864)

> Instead, design your application protocol so the connection termination is always initiated from the client side. If the client always knows when it has read all remaining data it can initiate the termination sequence. As an example, a browser knows from the `Content-Length` HTTP header when it has read all data and can initiate the close. (I know that in HTTP 1.1 it will keep it open for a while for a possible reuse, and then close it.)
>
> If the server needs to close the connection, design the application protocol so the server asks the client to call `close()`.

三、playload要尽可能小

影响带宽。



### Implementation

> NOTE: 这是在阅读[Redis Protocol specification](https://redis.io/topics/protocol) 时，其中给出的总结:
>
> 1、Simple to implement.
>
> 2、Fast to parse.

在设计protocol的时候，也是需要考虑implementation相关的问题:

1) 成本的、难易程度



### Human readable

这是在阅读[Redis Protocol specification](https://redis.io/topics/protocol) 时，其中给出的总结:

> Human readable



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



### 开源软件的application protocol

#### Redis: RESP 

参见 redis.io [Redis Protocol specification](https://redis.io/topics/protocol)。





