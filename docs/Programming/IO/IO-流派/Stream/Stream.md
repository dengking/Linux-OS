# Stream

“stream”即“流”，在计算机科学中它是一个非常重要的概念：计算机科学是关于数据的科学，我们的计算机系统处理着各种各样的数据，我们可以形象地将数据的传递看做是“水流”一般，数据就像水流的流转一般在计算机系统中进行流转，可以将stream看做是一种描述数据流的模型，在使用stream来进行抽象的时候，我们可以考虑这样的问题：

- 数据流向何处
- 数据从何处流入

stream模型抽象了数据的流动（流出、流入），stream模型可以抽象 input/output device，它能够抽象file、network device、custom adaptor device，所以使用stream模型构建的程序，允许我们实现使用抽象的stream来完成对多种device的IO。这个思想就是[abstraction](https://dengking.github.io/Post/Abstraction/Abstraction/)思想。

stream模型基本上统治了IO领域：

- 在[Everything-is-a-file](../../../Philosophy/Everything-is-a-file/Everything-is-a-file.md)中，我们其实已经探讨了linux的file descriptor其实代表的就是一个stream，它使用的就是stream模型，并且维基百科[Everything is a file](https://en.wikipedia.org/wiki/Everything_is_a_file)描述的思想和上一段中的思想一致。
- C++的[Input/output library](Input/output library)就是基于stream模型创建的。

stream模型的另外一个非常重要的特性是它是discrete的，所以我们可以one-by-one地来对它计算，一种最最常见的方式就是iteration，关于此，参见工程[discrete-math](https://dengking.github.io/discrete-math/)的iteration章节，关于此，在维基百科[Stream (computing)](https://en.wikipedia.org/wiki/Stream_(computing))中也进行了详细地介绍。

IO即输入、输出，就是典型的可以使用stream来进行描述的。





参考内容：

- 维基百科[Stream (computing)](https://en.wikipedia.org/wiki/Stream_(computing))
- 维基百科[C file input/output](https://en.wikipedia.org/wiki/C_file_input/output)
- [What is the difference between a stream and a file?](https://stackoverflow.com/questions/20937616/what-is-the-difference-between-a-stream-and-a-file)
- [Bitstream](https://en.wikipedia.org/wiki/Bitstream)



## 维基百科[Stream (computing)](https://en.wikipedia.org/wiki/Stream_(computing))

In [computer science](https://en.wikipedia.org/wiki/Computer_science), a **stream** is a [sequence](https://en.wikipedia.org/wiki/Sequence) of [data elements](https://en.wikipedia.org/wiki/Data_element) made available over time. A stream can be thought of as items on a [conveyor belt](https://en.wikipedia.org/wiki/Conveyor_belt) (传送带) being processed one at a time rather than in large batches.

> TRANSLATION: 在计算机科学中，stream是随时间推移可用的一系列数据元素。 可以将stream视为传送带上的物品，一次一个地处理，而不是大批量处理。

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

## TODO

[Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)

基于流的方式