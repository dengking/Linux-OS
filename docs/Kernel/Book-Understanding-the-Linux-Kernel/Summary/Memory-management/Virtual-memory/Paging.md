# [Paging](https://en.wikipedia.org/wiki/Paging)

In [computer](https://en.wikipedia.org/wiki/Computer) [operating systems](https://en.wikipedia.org/wiki/Operating_system), **paging** is a [memory management](https://en.wikipedia.org/wiki/Memory_management) scheme by which a computer stores and retrieves data from [secondary storage](https://en.wikipedia.org/wiki/Computer_data_storage#Secondary_storage) for use in [main memory](https://en.wikipedia.org/wiki/Computer_data_storage#Primary_storage). In this scheme, the operating system retrieves data from secondary storage in same-size [blocks](https://en.wikipedia.org/wiki/Block_(data_storage)) called *[pages](https://en.wikipedia.org/wiki/Page_(computer_memory))*. **Paging** is an important part of [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) implementations in modern operating systems, using **secondary storage** to let programs exceed the size of available **physical memory**.

For simplicity, **main memory** is called "RAM" (an acronym of "[random-access memory](https://en.wikipedia.org/wiki/Random-access_memory)") and **secondary storage** is called "disk" (a shorthand for "[hard disk drive](https://en.wikipedia.org/wiki/Hard_disk_drive)"), but the concepts do not depend on whether these terms apply literally to a specific computer system.



## Page faults

Main article: [Page fault](https://en.wikipedia.org/wiki/Page_fault)

When a process tries to reference a page not currently present in RAM, the processor treats this invalid memory reference as a [page fault](https://en.wikipedia.org/wiki/Page_fault) and transfers control from the program to the operating system. The operating system must:

1. Determine the location of the data on disk.
2. Obtain an empty [page frame](https://en.wikipedia.org/wiki/Page_frame) in RAM to use as a container for the data.
3. Load the requested data into the available page frame.
4. Update the [page table](https://en.wikipedia.org/wiki/Page_table) to refer to the new page frame.
5. Return control to the program, transparently retrying the [instruction](https://en.wikipedia.org/wiki/Instruction_(computer_science)) that caused the page fault.

When all **page frames** are in use, the operating system must select a **page frame** to reuse for the page the program now needs. If the evicted page frame was [dynamically allocated](https://en.wikipedia.org/wiki/Dynamic_allocation) by a program to hold data, or if a program modified it since it was read into RAM (in other words, if it has become "dirty"), it must be written out to disk before being freed. If a program later references the evicted page, another page fault occurs and the page must be read back into RAM.

The method the operating system uses to select the page frame to reuse, which is its [page replacement algorithm](https://en.wikipedia.org/wiki/Page_replacement_algorithm), is important to efficiency. The operating system predicts the page frame least likely to be needed soon, often through the [least recently used](https://en.wikipedia.org/wiki/Least_recently_used) (LRU) algorithm or an algorithm based on the program's [working set](https://en.wikipedia.org/wiki/Working_set). To further increase responsiveness, paging systems may predict which pages will be needed soon, preemptively loading them into RAM before a program references them.

## Page replacement techniques

*Main articles:* [Page replacement algorithm](https://en.wikipedia.org/wiki/Page_replacement_algorithm) *and* [Demand paging](https://en.wikipedia.org/wiki/Demand_paging)



## Sharing

In [multi-programming](https://en.wikipedia.org/wiki/Multi-programming) or in a [multi-user](https://en.wikipedia.org/wiki/Multi-user) environment, many users may execute the same program, written so that its code and data are in separate pages. To minimize RAM use, all users share a single copy of the program. Each process's [page table](https://en.wikipedia.org/wiki/Page_table) is set up so that the pages that address code point to the single shared copy, while the pages that address data point to different physical pages for each process.

Different programs might also use the same libraries. To save space, only one copy of the shared library is loaded into physical memory. Programs which use the same library have virtual addresses that map to the same pages (which contain the library's code and data). When programs want to modify the library's code, they use [copy-on-write](https://en.wikipedia.org/wiki/Copy-on-write), so memory is only allocated when needed.

Shared memory is an efficient way of communication between programs. Programs can share pages in memory, and then write and read to exchange data.

## Implementations

### Unix and Unix-like systems

[Unix](https://en.wikipedia.org/wiki/Unix) systems, and other [Unix-like](https://en.wikipedia.org/wiki/Unix-like) operating systems, use the term "**swap**" to describe both the act of moving memory pages between RAM and disk, and the region of a disk the pages are stored on. In some of those systems, it is common to dedicate an entire partition of a hard disk to swapping. These partitions are called *swap partitions*（交换区）. Many systems have an entire hard drive dedicated to swapping, separate from the data drive(s), containing only a swap partition. A hard drive dedicated to swapping is called a "swap drive" or a "scratch drive" or a "[scratch disk](https://en.wikipedia.org/wiki/Scratch_disk)". Some of those systems only support swapping to a swap partition; others also support swapping to files.

> NOTE: **swap**就是我们平时所说的交换区

#### Linux

The Linux kernel supports a virtually unlimited number of swap backends (devices or files), and also supports assignment of backend priorities. When the kernel needs to swap pages out of physical memory, it uses the highest-priority backend with available free space. If multiple swap backends are assigned the same priority, they are used in a [round-robin](https://en.wikipedia.org/wiki/Round-robin_scheduling) fashion (which is somewhat similar to [RAID 0](https://en.wikipedia.org/wiki/RAID_0) storage layouts), providing improved performance as long as the underlying devices can be efficiently accessed in parallel.