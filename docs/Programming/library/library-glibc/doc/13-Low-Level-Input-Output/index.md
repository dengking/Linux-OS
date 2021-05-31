# [13 Low-Level Input/Output](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-I_002fO.html)

This chapter describes functions for performing low-level input/output operations on file descriptors. These functions include the primitives for the higher-level I/O functions described in [I/O on Streams](https://www.gnu.org/software/libc/manual/html_node/I_002fO-on-Streams.html), as well as functions for performing low-level control operations for which there are no equivalents on streams.

> NOTE: 
>
> file-descriptor-based-IO

Stream-level I/O is more flexible and usually more convenient; therefore, programmers generally use the descriptor-level functions only when necessary. These are some of the usual reasons:

1、For reading binary files in large chunks.

2、For reading an entire file into core before parsing it.

3、To perform operations other than data transfer, which can only be done with a descriptor. (You can use `fileno` to get the descriptor corresponding to a stream.)

> NOTE: 
>
> 

4、To pass descriptors to a child process. (The child can create its own stream to use a descriptor that it inherits, but cannot inherit a stream directly.)

> NOTE: 
>
> "tag-child process inherit继承parent process's open file descriptor table"