# mmap 

## 用法总结

在 linuxhint [How to use mmap function in C language?](https://linuxhint.com/using_mmap_function_linux/) 中，对它的用法进行了非常好的总结。

一、创建一个file/device mapping

二、dynamic allocation

下面是这种用法的一些例子:

1、[clone(2)](https://man7.org/linux/man-pages/man2/clone.2.html)

三、interprocess communication



## wikipedia [mmap](https://en.wikipedia.org/wiki/Mmap)

In computing, mmap(2) is a POSIX-compliant Unix system call that maps files or devices into memory. It is a method of memory-mapped file I/O. It implements demand paging because file contents are not read from disk directly and initially do not use physical RAM at all. The actual reads from disk are performed in a "lazy" manner, after a specific location is accessed. After the memory is no longer needed, it is important to munmap(2) the pointers to it. Protection information can be managed using mprotect(2), and special treatment can be enforced using madvise(2).



## gnu libc [13.8 Memory-mapped I/O](https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html)

