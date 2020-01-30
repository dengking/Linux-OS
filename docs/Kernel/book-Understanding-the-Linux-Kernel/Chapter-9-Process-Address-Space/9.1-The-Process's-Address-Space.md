# 9.1. The Process's Address Space

The *address space* of a process consists of all **linear addresses** that the process is allowed to use. Each process sees a different set of **linear addresses**; the address used by one process bears no relation to the address used by another. As we will see later, the kernel may dynamically modify a **process address space** by adding or removing **intervals** of **linear addresses**.

The **kernel** represents intervals of linear addresses by means of resources called memory regions, which are characterized by an **initial linear address**, a **length**, and some **access rights**. For reasons of efficiency, both the initial address and the length of a memory region must be multiples of 4,096, so that the data identified by each **memory region** completely fills up the **page frames** allocated to it. Following are some typical situations in which a process gets new **memory regions**:

- When the user types a command at the console, the shell process creates a new process to execute the command. As a result, a fresh address space, and thus a set of **memory regions**, is assigned to the new process (see the section "Creating and Deleting a Process Address Space" later in this chapter; also, see Chapter 20).
- A running process may decide to load an entirely different program. In this case, the process ID remains unchanged, but the **memory regions** used before loading the program are released and a new set of **memory regions** is assigned to the process (see the section "The exec Functions" in Chapter 20).
- A running process may perform a "memory mapping" on a file (or on a portion of it). In such cases, the kernel assigns a new **memory region** to the process to map the file (see the section "Memory Mapping" in Chapter 16).
- A process may keep adding data on its **User Mode stack** until all addresses in the **memory region** that map the stack have been used. In this case, the kernel may decide to expand the size of that memory region (see the section "Page Fault Exception Handler" later in this chapter).
- A process may create an IPC-shared memory region to share data with other cooperating processes. In this case, the kernel assigns a new memory region to the process to implement this construct (see the section "IPC Shared Memory" in Chapter 19).
- A process may expand its dynamic area (the heap) through a function such as  [malloc( )](http://man7.org/linux/man-pages/man3/malloc.3.html) . As a result, the kernel may decide to expand the size of the memory region assigned to the heap (see the section "Managing the Heap" later in this chapter).



Table 9-1 illustrates some of the system calls related to the previously mentioned tasks.  [brk( )](http://man7.org/linux/man-pages/man2/brk.2.html) is discussed at the end of this chapter, while the remaining system calls are described in other chapters.

Table 9-1. System calls related to memory region creation and deletion

| System call                                                  | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [`brk( )`](http://man7.org/linux/man-pages/man2/brk.2.html)  | Changes the heap size of the process                         |
| [`execve( )`](http://man7.org/linux/man-pages/man2/execve.2.html) | Loads a new executable file, thus changing the process address space |
| [`_exit( )`](https://linux.die.net/man/2/_exit)              | Terminates the current process and destroys its address space |
| [`fork( )`](http://man7.org/linux/man-pages/man2/fork.2.html) | Creates a new process, and thus a new address space          |
| [`mmap( )`](http://man7.org/linux/man-pages/man2/mmap.2.html) ,  [`mmap2( )`](http://man7.org/linux/man-pages/man2/mmap.2.html) | Creates a memory mapping for a file, thus enlarging the process address space |
| [`mremap( )`](http://man7.org/linux/man-pages/man2/mremap.2.html) | Expands or shrinks a memory region                           |
| [`remap_file_pages()`](http://man7.org/linux/man-pages/man2/remap_file_pages.2.html) | Creates a non-linear mapping for a file (see Chapter 16)     |
| [`munmap( )`](https://linux.die.net/man/2/munmap)            | Destroys a memory mapping for a file, thus contracting the process address space |
| [`shmat( )`](https://linux.die.net/man/2/shmat)              | Attaches a shared memory region                              |
| [`shmdt( )`](https://linux.die.net/man/2/shmdt)              | Detaches a shared memory region                              |

As we'll see in the later section "Page Fault Exception Handler," it is essential for the kernel to identify the **memory regions** currently owned by a process (the address space of a process), because that allows the **Page Fault exception handler** to efficiently distinguish between two types of invalid linear addresses that cause it to be invoked:

- Those caused by programming errors.
- Those caused by a missing page; even though the **linear address** belongs to the process's address space, the **page frame** corresponding to that address has yet to be allocated.

The latter addresses are not invalid from the process's point of view; the induced Page Faults are exploited by the kernel to implement demand paging : the kernel provides the missing page frame and lets the process continue.

