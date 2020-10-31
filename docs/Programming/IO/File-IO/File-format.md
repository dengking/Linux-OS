# File format

在进行IO之前，必须首先定义file format，这是IO的前提。

## What is file format?

file format是一种schema，它描述了data的structure。在superuser [What are the general differences between a format and a protocol](https://superuser.com/questions/736401/what-are-the-general-differences-between-a-format-and-a-protocol) 中，有这样的描述:

> A format describes the structure of some data



## Examples

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



### Redis

[Redis RDB Dump File Format](https://github.com/sripathikrishnan/redis-rdb-tools/wiki/Redis-RDB-Dump-File-Format)