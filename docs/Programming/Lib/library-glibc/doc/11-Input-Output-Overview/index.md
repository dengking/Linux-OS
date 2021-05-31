# [11 Input/Output Overview](https://www.gnu.org/software/libc/manual/html_node/I_002fO-Overview.html)



1、[I/O on Streams](https://www.gnu.org/software/libc/manual/html_node/I_002fO-on-Streams.html)

> NOTE: 
>
> stream-based IO

2、[Low-Level I/O](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-I_002fO.html)

> NOTE: 
>
> file-descriptor-based-IO

3、[File System Interface](https://www.gnu.org/software/libc/manual/html_node/File-System-Interface.html)

4、[Pipes and FIFOs](https://www.gnu.org/software/libc/manual/html_node/Pipes-and-FIFOs.html)

5、[Sockets](https://www.gnu.org/software/libc/manual/html_node/Sockets.html)

6、[Low-Level Terminal Interface](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Terminal-Interface.html)



## [11.1 Input/Output Concepts](https://www.gnu.org/software/libc/manual/html_node/I_002fO-Concepts.html)

Before you can read or write the contents of a file, you must establish a connection or communications channel to the file. This process is called *opening* the file. You can open a file for reading, writing, or both.

> NOTE: 
>
> connection to file

The connection to an open file is represented either as a stream or as a file descriptor. 