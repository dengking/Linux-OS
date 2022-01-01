# Program break

在阅读 [brk(2) — Linux manual page](https://man7.org/linux/man-pages/man2/brk.2.html) 时，其中大量使用了**program break**这个词语，那它的含义是什么呢？本文对此进行说明。

## holbertonschool [Hack the Virtual Memory: malloc, the heap & the program break](https://blog.holbertonschool.com/hack-the-virtual-memory-malloc-the-heap-the-program-break/)

在这篇文章中，介绍了malloc、brk、program break、data segment、heap概念之间的关系，在`Kernel\Guide\Multitasking\Process-model\Process-resource\Process-memory-model\Linux-implementation\Verification\Holberton-Hack-the-virtual-memory\Chapter-3-malloc-the-heap&the-program-break`中收录了这篇文章。基本上，通过这篇文章的阅读是能够完整的认识program break的含义的。

## stackoverflow [What is program break? Where does it start from,0x00?](https://stackoverflow.com/questions/6338162/what-is-program-break-where-does-it-start-from-0x00)

[A](https://stackoverflow.com/a/6338195)

A program break is end of the process's data segment. AKA...

> the program break is the first location after the end of the uninitialized data segment

As to where it starts from, it's system dependent but probably not 0x00.

[A](https://stackoverflow.com/a/6351139)

Oversimplifying:

A process has several segments of memory:

- Code (text) segment, which contains the code to be executed.
- Data segment, which contains data the compiler knows about (globals and statics).
- Stack segment, which contains (drumroll...) the stack.

(Of course, nowadays it's much more complex. There is a rodata segment, a uninitialized data segment, mappings allocated via mmap, a vdso, ...)

One traditional way a program can request more memory in a Unix-like OS is to increment the size of the data segment, and use a memory allocator (i.e. `malloc()` implementation) to manage the resulting space. This is done via the `brk()` system call, which changes the point where the data segment "breaks"/ends.

