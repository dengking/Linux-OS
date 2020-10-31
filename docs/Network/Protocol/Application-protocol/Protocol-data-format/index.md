# Protocol data format/data exchange format

本章讨论protocol data format。

## Protocol data format and file format

如果从"format"进行联想的话，protocol data format与file format类似，需要注意的是: 一些file format可以作为protocol data format，一些protocol data format也可以作为file format。本质上它们都是在描述structure of stream of byte(参见 superuser [What are the general differences between a format and a protocol](https://superuser.com/questions/736401/what-are-the-general-differences-between-a-format-and-a-protocol) )。



## cnblogs [软件开发中的几种数据交换协议](https://www.cnblogs.com/winner-0715/p/7693400.html) # 如何选择数据交换协议

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







## 使用struct来描述

每种服务的入参，都有对应的struct类型，这样调用一个服务的入参的时候，传入对应的struct的object(copy一次)，在server端，服务的实现中，直接使用该服务对应的struct进行反序列化即可，可以通过如下的方式来避免copy:

```C++
struct CRequestStruct{};

const void* Request = Recv(); // 接收得到的请求数据
const CRequestStruct * Req = reinterpret_cast<const CRequestStruct *>(Request); // 
```

这种方式能够保证避免多次的copy，但是需要为每个服务都指定一个struct，或者说，需要为每个服务制定具体的protocol，这带来的一个问题就是: 维护的成本。