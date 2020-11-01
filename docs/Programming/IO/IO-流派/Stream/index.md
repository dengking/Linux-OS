# Stream-based IO

关于stream，参见工程discrete的`Relation-structure-computation\Model\Stream`章节。

Stream抽象了数据的流动（流出、流入），stream模型可以抽象 input/output device，它能够抽象file、network device、custom adaptor device，所以使用stream模型构建的程序，允许我们实现使用抽象的stream来完成对多种device的IO。这个思想就是[abstraction](https://dengking.github.io/Post/Abstraction/Abstraction/)思想。

stream模型基本上统治了IO领域：

- 在[Everything-is-a-file](../../../Philosophy/Everything-is-a-file/Everything-is-a-file.md)中，我们其实已经探讨了linux的file descriptor其实代表的就是一个stream，它使用的就是stream模型，并且维基百科[Everything is a file](https://en.wikipedia.org/wiki/Everything_is_a_file)描述的思想和上一段中的思想一致。
- C++的[Input/output library](Input/output library)就是基于stream模型创建的。

IO即输入、输出，就是典型的可以使用stream来进行描述的。

## wikipedia [Stream (computing)](https://en.wikipedia.org/wiki/Stream_(computing)) # Examples

2) On [Unix](https://en.wikipedia.org/wiki/Unix) and related systems based on the [C language](https://en.wikipedia.org/wiki/C_(programming_language)), a stream is a source or [sink](https://en.wikipedia.org/wiki/Sink_(computing)) of data, usually individual bytes or [characters](https://en.wikipedia.org/wiki/Character_(computing)). Streams are an **abstraction** used when reading or writing files, or communicating over [network sockets](https://en.wikipedia.org/wiki/Network_socket). The **standard streams** are three streams made available to all programs.

3) I/O devices can be interpreted as **streams**, as they produce or consume potentially unlimited data over time.

## wikipedia [C file input/output](https://en.wikipedia.org/wiki/C_file_input/output)



## C++ IO library

参见工程programming-language的`C-family-language\C++\Library\Standard-library\IO-library`章节。



