# Application protocol design

双方在进行通信之前，需要首先约定protocol，本文对application protocol design(应用层协议的设计)进行总结。protocol 有时候也被称为data exchange protocol。

## How to design application protocol

在设计application protocol的时候，需要考虑的问题有: 

### 1) Protocol data format

这在`./Protocol-data-format`章节进行讨论。

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





