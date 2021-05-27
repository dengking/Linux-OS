# 1.6.4. Process Address Space

Each process runs in its private address space. A process running in User Mode refers to private stack, data, and code areas. When running in Kernel Mode, the process addresses the kernel data and code areas and uses another private stack.

> NOTE: 不同的mode，使用不同的address space

Because the kernel is reentrant, several **kernel control paths** each related to a different **process** may be executed in turn. In this case, each **kernel control path** refers to its own **private kernel stack**.

> NOTE : 关于kernel stack参见3.2.2.1. Process descriptors handling

While it appears to each process that it has access to a **private address space**, there are times when part of the address space is **shared** among processes. In some cases, this sharing is explicitly requested by processes; in others, it is done automatically by the kernel to reduce memory usage.

If the same program, say an editor, is needed simultaneously by several users, the program is loaded into memory only once, and its instructions can be shared by all of the users who need it. Its data, of course, must not be shared, because each user will have separate data. This kind of shared address space is done automatically by the kernel to save memory.

Processes also can share parts of their address space as a kind of **interprocess communication**, using the "shared memory" technique introduced in System V and supported by Linux.

Finally, Linux supports the  [`mmap( )`](http://man7.org/linux/man-pages/man2/mmap.2.html) system call, which allows part of a file or the information stored on a block device to be mapped into a part of a process address space. Memory mapping can provide an alternative to normal reads and writes for transferring data. If the same file is shared by several processes, its memory mapping is included in the address space of each of the processes that share it.

