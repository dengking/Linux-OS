# Protocol

在进行IO的时候，非常重要的一个环节是约定protocol，这是IO的前提，本文描述的protocol，有时候也被称format，比如在[protobuf](https://github.com/protocolbuffers/protobuf)中，称为 "data interchange format"。

| IO         |          | 章节                        |
| ---------- | -------- | --------------------------- |
| File IO    | format   |                             |
| Network IO | protocol | 工程Linux-OS的`Network`章节 |



## File format

### [protobuf](https://github.com/protocolbuffers/protobuf)



### SQLite

在[About SQLite](https://www.sqlite.org/about.html)中，有这样的介绍: 

> A complete SQL database with multiple tables, indices, triggers, and views, is contained in a single disk file. The database [file format](https://www.sqlite.org/fileformat2.html) is cross-platform - you can freely copy a database between 32-bit and 64-bit systems or between [big-endian](http://en.wikipedia.org/wiki/Endianness) and [little-endian](http://en.wikipedia.org/wiki/Endianness) architectures. These features make SQLite a popular choice as an [Application File Format](https://www.sqlite.org/appfileformat.html). SQLite database files are a [recommended storage format](https://www.sqlite.org/locrsf.html) by the US Library of Congress. Think of SQLite not as a replacement for [Oracle](http://www.oracle.com/database/index.html) but as a replacement for [fopen()](http://man.he.net/man3/fopen)



#### SQLite [Database File Format](https://www.sqlite.org/fileformat2.html)

This document describes and defines the on-disk database file format used by all releases of SQLite since version 3.0.0 (2004-06-18).



#### [SQLite As An Application File Format](https://www.sqlite.org/appfileformat.html)





### Json







### MessagePack 

> NOTE: 这是我在阅读cnblogs [软件开发中的几种数据交换协议](https://www.cnblogs.com/winner-0715/p/7693400.html)时，其中提及的一种