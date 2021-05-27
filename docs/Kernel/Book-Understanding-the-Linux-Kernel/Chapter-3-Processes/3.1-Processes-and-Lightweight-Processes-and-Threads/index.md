# 3.1. Processes, Lightweight Processes, and Threads

The term "process" is often used with several different meanings. In this book, we stick to the usual OS textbook definition: a ***process*** is an instance of a program in execution. You might think of it as the collection of data structures that fully describes how far the execution of the program has progressed.

> NOTE: 本节中的process指的是标准[Process](https://en.wikipedia.org/wiki/Process_(computing)) 

Processes are like human beings: they are generated, they have a more or less significant life, they optionally generate one or more child processes, and eventually they die. A small difference is that sex is not really common among processes each process has just one parent. 

> NOTE: process的生命周期

From the kernel's point of view, the purpose of a process is to act as an entity to which system resources (CPU time, memory, etc.) are allocated.

> NOTE: 
>
> process是OS的资源分配单位

When a process is created, it is almost identical to its parent. It receives a (logical) copy of the parent's address space and executes the same code as the parent, beginning at the next instruction following the process creation system call. Although the parent and child may share the pages containing the program code (text), they have separate copies of the data (stack and heap), so that changes by the child to a memory location are invisible to the parent (and vice versa).

While earlier Unix kernels employed this simple model, modern Unix systems do not. They support
***multithreaded applications*** user programs having many relatively independent execution flows
sharing a large portion of the application data structures. In such systems, a **process** is composed of
several ***user threads*** (or simply ***threads***), each of which represents an execution flow of the process.
Nowadays, most multithreaded applications are written using standard sets of library functions
called `pthread` (POSIX thread) libraries .

> NOTE :  这段话中的**user threads**具有特殊的含义，在《`VS-process-VS-thread-VS-lightweight process.md`》中对这个问题进行了分析。理解它对于理解本段是比较重要的。

Older versions of the Linux kernel offered no support for multithreaded applications. From the kernel
point of view, a multithreaded application was just a normal **process**. The multiple execution flows of
a multithreaded application were created, handled, and scheduled entirely in **User Mode**, usually by
means of a POSIX-compliant `pthread` library.

> NOTE:  在《`VS-process-VS-thread-VS-lightweight process.md`》中对这个问题进行了深刻分析

However, such an implementation of multithreaded applications is not very satisfactory. For
instance, suppose a chess program uses two threads: one of them controls the graphical
chessboard, waiting for the moves of the human player and showing the moves of the computer,
while the other thread ponders the next move of the game. While the first thread waits for the
human move, the second thread should run continuously, thus exploiting the thinking time of the
human player. However, if the chess program is just a single process, the first thread cannot simply
issue a blocking system call waiting for a user action; otherwise, the second thread is blocked as
well. Instead, the first thread must employ sophisticated nonblocking techniques to ensure that the
process remains runnable.

> NOTE : 显然Older versions of the Linux kernel offered no support for multithreaded applications.

Linux uses *lightweight processes* to offer better support for multithreaded applications. Basically, two
lightweight processes may share some resources, like the **address space**, the **open files**, and so on.
Whenever one of them modifies a shared resource, the other immediately sees the change. Of
course, the two processes must synchronize themselves when accessing the shared resource.

A straightforward way to implement multithreaded applications is to associate a **lightweight process**
with each **thread**. In this way, the threads can access the same set of application data structures by
simply sharing the same memory address space, the same set of open files, and so on; at the same
time, each thread can be scheduled independently by the kernel so that one may sleep while another
remains runnable. Examples of POSIX-compliant `pthread` libraries that use Linux's **lightweight**
**processes** are LinuxThreads, Native POSIX Thread Library (NPTL), and IBM's Next Generation Posix
Threading Package (NGPT).

> NOTE: 关于LinuxThreads、Native POSIX Thread Library (NPTL)，参见[PTHREADS(7)](http://man7.org/linux/man-pages/man7/pthreads.7.html)，其中的Linux implementations of POSIX threads章节描述了linux的GNU C library实现POSIX threads的方式的细节，其中给出了如何查看系统的 `pthread` libraries的实现方式的命令。

POSIX-compliant multithreaded applications are best handled by kernels that support "**thread**
**groups** ." In Linux a **thread group** is basically a set of **lightweight processes** that implement a
multithreaded application and act as a whole with regards to some system calls such as  `getpid( )` ,
`kill( )` , and  `_exit( )` . We are going to describe them at length later in this chapter.

> NOTE : 新版本的linux使用 **lightweight process**来实现thread；使用**thread group**来作为process；
>
> 其实linux kernel提供了非常灵活的[CLONE(2)](http://man7.org/linux/man-pages/man2/clone.2.html) system call来让用户灵活地创建process或thread。



