# Stream

在阅读[Input/output](https://en.wikipedia.org/wiki/Input/output)时，其中的一句话引起了我的注意：

> For example, most operating systems provide application programs with the concept of [files](https://en.wikipedia.org/wiki/Computer_file). The [C](https://en.wikipedia.org/wiki/C_(programming_language)) and [C++](https://en.wikipedia.org/wiki/C%2B%2B) programming languages, and operating systems in the [Unix](https://en.wikipedia.org/wiki/Unix) family, traditionally abstract files and devices as [streams](https://en.wikipedia.org/wiki/Stream_(computing)), which can be read or written, or sometimes both. The [C standard library](https://en.wikipedia.org/wiki/C_standard_library) provides [functions for manipulating streams](https://en.wikipedia.org/wiki/C_file_input/output) for input and output.

这提示了我们：C系语言、Unix-like OS可以（说明不止一种方式）使用stream来描述IO。本文将对stream进行总结。



参考内容：

- 维基百科[Stream (computing)](https://en.wikipedia.org/wiki/Stream_(computing))
- 维基百科[C file input/output](https://en.wikipedia.org/wiki/C_file_input/output)
- [What is the difference between a stream and a file?](https://stackoverflow.com/questions/20937616/what-is-the-difference-between-a-stream-and-a-file)
- [Bitstream](https://en.wikipedia.org/wiki/Bitstream)



## 维基百科[Stream (computing)](https://en.wikipedia.org/wiki/Stream_(computing))

In [computer science](https://en.wikipedia.org/wiki/Computer_science), a **stream** is a [sequence](https://en.wikipedia.org/wiki/Sequence) of [data elements](https://en.wikipedia.org/wiki/Data_element) made available over time. A stream can be thought of as items on a [conveyor belt](https://en.wikipedia.org/wiki/Conveyor_belt) (传送带) being processed one at a time rather than in large batches.

***TRANSLATION*** : 在计算机科学中，stream是随时间推移可用的一系列数据元素。 可以将stream视为传送带上的物品，一次一个地处理，而不是大批量处理。

**Streams** are processed differently from [batch data](https://en.wikipedia.org/wiki/Batch_processing) – normal functions cannot operate on streams as a whole(不能够整个的操作stream), as they have potentially **unlimited data**, and formally, streams are [*codata*](https://en.wikipedia.org/wiki/Codata_(computer_science)) (potentially unlimited), not data (which is finite). Functions that operate on a stream, producing another stream, are known as [filters](https://en.wikipedia.org/wiki/Filter_(software)), and can be connected in [pipelines](https://en.wikipedia.org/wiki/Pipeline_(computing)), analogously to [function composition](https://en.wikipedia.org/wiki/Function_composition_(computer_science)). Filters may operate on one item of a stream at a time, or may base an item of output on multiple items of input, such as a [moving average](https://en.wikipedia.org/wiki/Moving_average).



### Examples

The term "stream" is used in a number of similar ways:

- "Stream editing", as with [sed](https://en.wikipedia.org/wiki/Sed), [awk](https://en.wikipedia.org/wiki/Awk), and [perl](https://en.wikipedia.org/wiki/Perl). Stream editing processes a file or files, in-place, without having to load the file(s) into a user interface. One example of such use is to do a search and replace on all the files in a directory, from the command line.
- On [Unix](https://en.wikipedia.org/wiki/Unix) and related systems based on the [C language](https://en.wikipedia.org/wiki/C_(programming_language)), a stream is a source or [sink](https://en.wikipedia.org/wiki/Sink_(computing)) of data, usually individual bytes or [characters](https://en.wikipedia.org/wiki/Character_(computing)). Streams are an abstraction used when reading or writing files, or communicating over [network sockets](https://en.wikipedia.org/wiki/Network_socket). The **standard streams** are three streams made available to all programs.
- I/O devices can be interpreted as **streams**, as they produce or consume potentially unlimited data over time.
- In [object-oriented programming](https://en.wikipedia.org/wiki/Object-oriented_programming), input streams are generally implemented as [iterators](https://en.wikipedia.org/wiki/Iterator).
- In the [Scheme language](https://en.wikipedia.org/wiki/Scheme_(programming_language)) and some others, a stream is a [lazily evaluated](https://en.wikipedia.org/wiki/Lazy_evaluation) or *delayed* sequence of data elements. A stream can be used similarly to a list, but later elements are only calculated when needed. Streams can therefore represent infinite [sequences](https://en.wikipedia.org/wiki/Sequence) and [series](https://en.wikipedia.org/wiki/Series_(mathematics)). 
- In the [Smalltalk](https://en.wikipedia.org/wiki/Smalltalk) [standard library](https://en.wikipedia.org/wiki/Standard_library) and in other [programming languages](https://en.wikipedia.org/wiki/Programming_language) as well, a stream is an **external iterator**. As in Scheme, streams can represent finite or infinite sequences.
- **Stream processing** — in [parallel processing](https://en.wikipedia.org/wiki/Parallel_computing), especially in graphic processing, the term stream is applied to [hardware](https://en.wikipedia.org/wiki/Computer_hardware) as well as [software](https://en.wikipedia.org/wiki/Software). There it defines the quasi-continuous flow of data that is processed in a [dataflow programming](https://en.wikipedia.org/wiki/Dataflow_programming) language as soon as the [program state](https://en.wikipedia.org/wiki/Program_state) meets the starting condition of the stream.

### Applications

Streams can be used as the underlying data type for [channels](https://en.wikipedia.org/wiki/Channel_(programming)) in [interprocess communication](https://en.wikipedia.org/wiki/Interprocess_communication).

### [Other uses](https://en.wikipedia.org/wiki/Stream_(computing)#Other_uses)



## [What is the difference between a stream and a file?](https://stackoverflow.com/questions/20937616/what-is-the-difference-between-a-stream-and-a-file)



### [A](https://stackoverflow.com/a/20937904)

In the context of the C Standard Library a stream is a generic interface for performing certain I/O operations. You can read from streams, write to streams, some streams are seekable. Opening a file as a stream is only one way to get a stream as an I/O interface for an application.

[Let me quote:](https://www.gnu.org/software/libc/manual/html_mono/libc.html#Streams-and-File-Descriptors)

> **11.1.1 Streams and File Descriptors**
>
> When you want to do input or output to a file, you have a choice of two basic mechanisms for representing the connection between your program and the file: file descriptors and streams. File descriptors are represented as objects of type `int`, while streams are represented as `FILE *` objects.
>
> File descriptors provide a primitive, low-level interface to input and output operations. Both file descriptors and streams can represent a connection to a device (such as a terminal), or a pipe or socket for communicating with another process, as well as a normal file. [...]

[... and further:](https://www.gnu.org/software/libc/manual/html_mono/libc.html#Streams)

> **12.1 Streams**
>
> For historical reasons, the type of the C data structure that represents a stream is called `FILE` rather than “stream”. Since most of the library functions deal with objects of type `FILE *`, sometimes the term *file pointer* is also used to mean “stream”. This leads to unfortunate confusion over terminology in many books on C.

Examples for I/O streams in C:

- **Standard Streams:** https://linux.die.net/man/3/stdin
- **File Streams:** https://linux.die.net/man/3/fopen
- **Pipes:** https://linux.die.net/man/3/popen
- **Stream Sockets:** https://linux.die.net/man/2/socket

For further reading, also have a look at these links:

- https://www.gnu.org/software/libc/manual/html_mono/libc.html#I_002fO-Overview
- https://www.gnu.org/software/libc/manual/html_mono/libc.html#I_002fO-on-Streams

The stream-based API is built on top of the low-level *file descriptor* API and provides additional functionality. Some low-level features are however only available via the lower level API, e.g., *memory-mapped I/O*, *non-blocking I/O* or "event-driven" I/O:

- https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html
- https://linux.die.net/man/2/poll
- https://linux.die.net/man/4/epoll



## Stream VS file descriptor



## C++ Files and Streams

https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm

http://www.cplusplus.com/doc/tutorial/files/	

## [C file input/output](https://en.wikipedia.org/wiki/C_file_input/output)