# [Thrift: Scalable Cross-Language Services Implementation](https://thrift.apache.org/static/files/thrift-20070401.pdf)

> NOTE: 未阅读完成

## Abstract

Thrift is a software library and set of **code-generation tools** developed at Facebook to expedite(促进) development and implementation of efficient and scalable **backend services**. Its primary goal is to enable
efficient and reliable **communication** across programming languages by abstracting the portions of each language that tend to require the most customization into a common library that is implemented in each language. Specifically, Thrift allows developers to define **datatypes** and **service interfaces** in a single **language-neutral file** and generate all the necessary code to build RPC clients and servers.

This paper details the motivations and design choices we made in Thrift, as well as some of the more interesting implementation details. It is not intended to be taken as research, but rather it is an exposition on what we did and why.

## 1 Introduction

As Facebook’s traffic and network structure have scaled, the resource demands of many operations on the site (i.e. search, ad selection and delivery, event logging) have presented technical requirements drastically outside the scope of the LAMP framework.

> 随着Facebook流量和网络结构的扩大，网站上许多操作(如搜索、广告选择和发布、事件记录)的资源需求已经大大超出了LAMP框架的范围。

In our implementation of these services, various programming languages have been selected to optimize for the right combination of performance, ease and speed of development, availability of existing libraries, etc. By and large, Facebook’s engineering culture has tended towards choosing the best tools and implementations available over standardizing on any one programming language and begrudgingly(吝啬的)
accepting its inherent limitations.

Given this design choice, we were presented with the challenge of building a transparent, high-performance bridge across many programming languages. We found that most available solutions were either too limited, did not offer sufficient datatype freedom, or suffered from subpar(低于标准的) performance. 1

The solution that we have implemented combines a language-neutral software stack implemented across numerous programming languages and an associated code generation engine that transforms a simple interface and data definition language into client and server remote procedure call libraries. Choosing static code generation over a dynamic system allows us to create validated code that can be run without the need for any advanced introspective(内省的) run-time type checking. It is also designed to be as simple as possible for the developer, who can typically define all the necessary data structures and interfaces for a complex service in a single short file.

Surprised that a robust open solution to these relatively common problems did not yet exist, we committed early on to making the Thrift implementation open source.

In evaluating the challenges of cross-language interaction in a networked environment, some key components were identified:

### Types

***Types***. A common type system must exist across programming languages without requiring that the **application developer** use custom Thrift datatypes or write their own serialization code. That is, a C++
programmer should be able to transparently exchange a strongly typed STL map for a dynamic Python dictionary. Neither programmer should be forced to write any code below the application layer to achieve this. Section 2 details the Thrift type system. 

### Transport

***Transport***. Each language must have a common interface to bidirectional raw data transport. The specifics of how a given transport is implemented should not matter to the service developer. The same application code should be able to run against TCP stream sockets, raw data in memory, or files on disk. Section 3 details the Thrift Transport layer.

### Protocol

***Protocol***. Datatypes must have some way of using the **Transport layer** to encode and decode themselves. Again, the application developer need not be concerned by this layer. Whether the service uses an XML or binary protocol is immaterial(透明的) to the application code. All that matters is that the data can be read and written in a consistent, deterministic matter. Section 4 details the **Thrift Protocol layer**.

### Versioning

***Versioning***. For robust services, the involved datatypes must provide a mechanism for versioning themselves. Specifically, it should be possible to add or remove fields in an object or alter the argument
list of a function without any interruption in service (or, worse yet, nasty segmentation faults). Section 5 details Thrift’s versioning system.

### Processors

***Processors***. Finally, we generate code capable of processing data streams to accomplish remote procedure calls. Section 6 details the generated code and **TProcessor paradigm**. 

Section 7 discusses implementation details, and Section 8 describes our conclusions.

## 2 Types

### 2.1 Base Types

### 2.2 Structs

### 2.3 Containers

### 2.4 Exceptions

### 2.5 Services

## 3 Transport

The transport layer is used by the generated code to facilitate data transfer.

### 3.1 Interface

### 3.2 Implementation

#### 3.2.1 TSocket

#### 3.2.2 TFileTransport

#### 3.2.3 Utilities



## 4 Protocol

A second major abstraction in Thrift is the separation of data structure from transport representation. Thrift enforces a certain messaging structure when transporting data, but it is agnostic to the protocol encoding in use. That is, it does not matter whether data is encoded as XML, human-readable ASCII, or a dense binary format as long as the data supports a fixed set of operations that allow it to be deterministically read and written by generated code.