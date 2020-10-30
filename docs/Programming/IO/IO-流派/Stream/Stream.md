# Stream

维基百科 [C file input/output](https://en.wikipedia.org/wiki/C_file_input/output)

stackoverflow [What is the difference between a stream and a file?](https://stackoverflow.com/questions/20937616/what-is-the-difference-between-a-stream-and-a-file)



## stackoverflow [What is the difference between a stream and a file?](https://stackoverflow.com/questions/20937616/what-is-the-difference-between-a-stream-and-a-file)



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