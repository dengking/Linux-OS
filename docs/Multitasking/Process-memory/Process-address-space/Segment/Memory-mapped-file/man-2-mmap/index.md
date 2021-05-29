# mmap 



## linuxhint [How to use mmap function in C language?](https://linuxhint.com/using_mmap_function_linux/)

The ***mmap()*** function is used for mapping between a process address space and either files or devices. When a file is mapped to a process address space, the file can be accessed like an array in the program. This is one of the most efficient ways to access data in the file and provides a seamless coding interface that is natural for a data structure that can be assessed without he abstraction of reading and writing from files. In this article, we are going to discuss how to use the ***mmap()*** function in Linux. So, let’s get started.

[![img](https://linuxhint.com/wp-content/uploads/2020/07/1-22.jpg)](https://linuxhint.com/wp-content/uploads/2020/07/1-22.jpg)



## [mmap(2) — Linux manual page](https://man7.org/linux/man-pages/man2/mmap.2.html)

`mmap()` creates a new mapping in the virtual address space of the calling process.  The starting address for the new mapping is specified in `addr`.  The length argument specifies the length of the mapping (which must be greater than 0).

If `addr` is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.



## wikipedia [mmap](https://en.wikipedia.org/wiki/Mmap)



## gnu libc [13.8 Memory-mapped I/O](https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html)

