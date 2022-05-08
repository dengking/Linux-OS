# 3 File I/O

## 3.1 Introduction

Most file I/O on a UNIX system can be performed using only five functions: `open`, `read`, `write`, `lseek`, and `close`.

> NOTE:
>
> 一、File I/O function:
>
> |       |       |
> | ----- | ----- |
> | open  | close |
> | read  | write |
> | lseek |       |
> 

The functions described in this chapter are often referred to as *unbuffered I/O*, in contrast to the standard I/O routines, which we describe in Chapter 5. The term *unbuffered* means that each read or write invokes a system call in the kernel. These unbuffered I/O functions are not part of ISO C, but are part of POSIX.1 and the Single UNIX Specifification.

> NOTE:
>
> 1、system call-unbuffered I/O-POSIX.1、Single UNIX Specifification
>
> 2、library function-buffered I/O-ISO C
>
> 

