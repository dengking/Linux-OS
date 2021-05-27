# 1.6.8. Memory Management

Memory management is by far the most complex activity in a Unix kernel. More than a third of this book is dedicated just to describing how Linux handles memory management. This section illustrates some of the main issues related to memory management.

## 1.6.8.1. Virtual memory

All recent Unix systems provide a useful abstraction called *virtual memory* . **Virtual memory** acts as a logical layer between the application memory requests and the hardware Memory Management Unit (MMU). Virtual memory has many purposes and advantages: 

- Several processes can be executed concurrently.
- It is possible to run applications whose memory needs are larger than the available physical
  memory.
- Processes can execute a program whose code is only partially loaded in memory.
- Each process is allowed to access a subset of the available physical memory.
- Processes can share a single memory image of a library or program.
- Programs can be relocatable that is, they can be placed anywhere in physical memory.

The main ingredient of a virtual memory subsystem is the notion of *virtual address space*. The set of memory references that a process can use is different from physical memory addresses. When a process uses a **virtual address**, `[*]` the kernel and the MMU cooperate to find the actual physical location of the requested memory item.

> `[*]` These addresses have different nomenclatures, depending on the computer architecture. As we'll see in Chapter 2, Intel manuals refer to them as "logical addresses."

Today's CPUs include hardware circuits that automatically translate the **virtual addresses** into physical ones. To that end, the available RAM is partitioned into **page frames** typically 4 or 8 KB in length and a set of **Page Tables** is introduced to specify how **virtual addresses** correspond to **physical addresses**. These circuits make memory allocation simpler, because a request for a block of contiguous virtual addresses can be satisfied by allocating a group of page frames having noncontiguous physical addresses.

> NOTE: 本节的内容主要是对如下章节的内容的概括：
>
> - chapter 2.1. Memory Addresses
> - chapter 2.4. Paging in Hardware
> - chapter 2.5. Paging in Linux

## 1.6.8.2. Random access memory usage

All Unix operating systems clearly distinguish between two portions of the random access memory (RAM). A few megabytes are dedicated to storing the kernel image (i.e., the kernel code and the kernel static data structures). The remaining portion of RAM is usually handled by the virtual memory system and is used in three possible ways:

- To satisfy kernel requests for buffers, descriptors, and other dynamic kernel data structures
- To satisfy process requests for generic memory areas and for memory mapping of files
- To get better performance from disks and other buffered devices by means of caches

> NOTE: 关于RAM的usage，在Chapter 8. Memory Management有类似上面这段的描述。

Each request type is valuable. On the other hand, because the available RAM is limited, some balancing among request types must be done, particularly when little available memory is left. Moreover, when some critical threshold of available memory is reached and a page-frame-reclaiming algorithm is invoked to free additional memory, which are the page frames most suitable for reclaiming? As we will see in Chapter 17, there is no simple answer to this question and very little support from theory. The only available solution lies in developing carefully tuned empirical algorithms.

One major problem that must be solved by the virtual memory system is **memory fragmentation** . Ideally, a memory request should fail only when the number of free page frames is too small. However, the kernel is often forced to use physically contiguous memory areas. Hence the memory request could fail even if there is enough memory available, but it is not available as one contiguous chunk.



## 1.6.8.3. Kernel Memory Allocator

The Kernel Memory Allocator (KMA) is a subsystem that tries to satisfy the requests for memory areas from all parts of the system. Some of these requests come from other kernel subsystems needing memory for kernel use, and some requests come via system calls from user programs to increase their processes' address spaces. A good KMA should have the following features:

- It must be fast. Actually, this is the most crucial attribute, because it is invoked by all kernel subsystems (including the interrupt handlers).
- It should minimize the amount of wasted memory.
- It should try to reduce the memory fragmentation problem.
- It should be able to cooperate with the other memory management subsystems to borrow and release page frames from them.

Several proposed KMAs, which are based on a variety of different algorithmic techniques, include:

- Resource map allocator

- Power-of-two free lists

- McKusick-Karels allocator

- Buddy system

- Mach's Zone allocator

- Dynix allocator

- Solaris 's Slab allocator

As we will see in Chapter 8, Linux's KMA uses a Slab allocator on top of a buddy system.

> NOTE: 
>
> - [Memory Allocation Guide](https://www.kernel.org/doc/html/latest/core-api/memory-allocation.html)

## 1.6.8.4. Process virtual address space handling

The **address space** of a process contains all the virtual memory addresses that the process is allowed to reference. The kernel usually stores a process virtual address space as a **list** of *memory area descriptors* . For example, when a process starts the execution of some program via an  exec( ) -like system call, the kernel assigns to the process a virtual address space that comprises **memory areas** for:

- The executable code of the program
- The initialized data of the program
- The uninitialized data of the program
- The initial program stack (i.e., the User Mode stack)
- The executable code and data of needed shared libraries
- The heap (the memory dynamically requested by the program)

All recent Unix operating systems adopt a memory allocation strategy called *demand paging* . With demand paging, a process can start program execution with none of its pages in physical memory. As it accesses a nonpresent page, the MMU generates an exception; the **exception handler** finds the affected memory region, allocates a free page, and initializes it with the appropriate data. In a similar fashion, when the process dynamically requires memory by using  [`malloc( )`](http://man7.org/linux/man-pages/man3/malloc.3.html) , or the  [`brk( )`](http://man7.org/linux/man-pages/man2/brk.2.html) system call (which is invoked internally by   [`malloc( )`](http://man7.org/linux/man-pages/man3/malloc.3.html) ), the kernel just updates the size of the **heap memory region** of the process. A page frame is assigned to the process only when it generates an exception by trying to refer its virtual memory addresses.

**Virtual address spaces** also allow other efficient strategies, such as the Copy On Write strategy mentioned earlier. For example, when a new process is created, the kernel just assigns the parent's page frames to the child address space, but marks them read-only. An exception is raised as soon the parent or the child tries to modify the contents of a page. The exception handler assigns a new page frame to the affected process and initializes it with the contents of the original page.

## 1.6.8.5. Caching

A good part of the available physical memory is used as cache for hard disks and other block devices. This is because hard drives are very slow: a disk access requires several milliseconds, which is a very long time compared with the RAM access time. Therefore, disks are often the bottleneck in system performance. As a general rule, one of the policies already implemented in the earliest Unix system is to defer writing to disk as long as possible. As a result, data read previously from disk and no longer used by any process continue to stay in RAM.

This strategy is based on the fact that there is a good chance that new processes will require data read from or written to disk by processes that no longer exist. When a process asks to access a disk, the kernel checks first whether the required data are in the cache. Each time this happens (a cache hit), the kernel is able to service the process request without accessing the disk. 

The  [sync( )](http://man7.org/linux/man-pages/man2/sync.2.html) system call forces disk synchronization by writing all of the "dirty" buffers (i.e., all the buffers whose contents differ from that of the corresponding disk blocks) into disk. To avoid data loss, all operating systems take care to periodically write dirty buffers back to disk.