# Memory-mapped file

一、memory-mapped file的实现应该是和virtual memory的实现有些相关:

1、都涉及random access memory 和 disk

2、都涉及page、swap等等

## wikipedia [Memory-mapped file](https://en.wikipedia.org/wiki/Memory-mapped_file)

A **memory-mapped file** is a segment of [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory)[[1\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-:0-1) that has been assigned a direct byte-for-byte correlation with some portion of a file or file-like resource. This resource is typically a file that is physically present on disk, but can also be a device, shared memory object, or other resource that the [operating system](https://en.wikipedia.org/wiki/Operating_system) can reference through a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor). Once present, this correlation between the file and the memory space permits applications to treat the mapped portion as if it were primary memory.

> NOTE: 
>
> "memory-mapped file"的file并不仅仅是我们通常理解下的 "file that is physically present on disk"，它还包括:
>
> 1、device
>
> 2、shared memory object
>
> 3、fd
>
> 这充分体现了: "Unix philosophy everything is a file descriptor"

### Benefits

The benefit of memory mapping a file is increasing I/O performance, especially when used on large files. For small files, memory-mapped files can result in a waste of [slack space](https://en.wikipedia.org/wiki/Slack_space) as memory maps are always aligned to the page size, which is mostly 4 KiB. Therefore, a 5 KiB file will allocate 8 KiB and thus 3 KiB are wasted. Accessing memory mapped files is faster than using direct read and write operations for two reasons. Firstly, a system call is orders of magnitude slower than a simple change to a program's local memory. Secondly, in most operating systems the memory region mapped actually *is* the kernel's [page cache](https://en.wikipedia.org/wiki/Page_cache) (file cache), meaning that no copies need to be created in user space.

> NOTE: 
>
> 一、上述[slack space](https://en.wikipedia.org/wiki/Slack_space) 链接到的是 [Internal fragmentation](https://en.wikipedia.org/wiki/Fragmentation_(computing)#Internal_fragmentation)
>
> 二、上述对memory-mapped file的优势的介绍是非常好的

### Types

#### Persisted

> NOTE: 
>
> 这种file是一个 "file on disk"

#### Non-persisted

> NOTE: 
>
> 这种file不是一个 "file on disk"，对于这种情况，我们要使用"Unix philosophy everything is a file descriptor"来进行理解

These files are suitable for creating shared memory for inter-process communications (IPC).

### Common uses

> NOTE: 
>
> 本节总结的两种application都是非常典型的

#### Process loader

Perhaps the most common use for a memory-mapped file is the [process loader](https://en.wikipedia.org/wiki/Loader_(computing)) in most modern operating systems (including [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) and [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems.) When a [process](https://en.wikipedia.org/wiki/Process_(computing)) is started, the operating system uses a memory mapped file to bring the executable file, along with any loadable modules, into memory for execution. Most memory-mapping systems use a technique called [demand paging](https://en.wikipedia.org/wiki/Demand_paging), where the file is loaded into physical memory in subsets (one page each), and only when that page is actually referenced.[[11\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-11) In the specific case of executable files, this permits the OS to selectively load only those portions of a process image that actually need to execute.

#### Shared memory IPC

Another common use for memory-mapped files is to share memory between multiple processes. In modern [protected mode](https://en.wikipedia.org/wiki/Protected_mode) operating systems, processes are generally not permitted to access memory space that is allocated for use by another process. (A program's attempt to do so causes [invalid page faults](https://en.wikipedia.org/wiki/Page_fault#Invalid) or [segmentation violations](https://en.wikipedia.org/wiki/Segmentation_violation).) There are a number of techniques available to safely **share memory**, and **memory-mapped file I/O** is one of the most popular. Two or more applications can simultaneously map a single physical file into memory and access this memory. For example, the Microsoft Windows operating system provides a mechanism for applications to memory-map a shared segment of the system's page file itself and share data via this section.

> NOTE: inter-process communication

### Platform support

Some free portable implementations of memory-mapped files for Microsoft Windows and POSIX-compliant platforms are:

- Boost.Interprocess,[[15\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-15) in [Boost C++ Libraries](https://en.wikipedia.org/wiki/Boost_C%2B%2B_Libraries)
- Boost.Iostreams,[[16\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-16) also in [Boost C++ Libraries](https://en.wikipedia.org/wiki/Boost_C%2B%2B_Libraries)
- Fmstream[[17\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-17)
- Cpp-mmf[[18\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-18)

## stackoverflow [What are the advantages of memory-mapped files?](https://stackoverflow.com/questions/192527/what-are-the-advantages-of-memory-mapped-files)

n particular, I am concerned about the following, in order of importance:

- concurrency
- random access
- performance
- ease of use
- portability



### [A](https://stackoverflow.com/a/192854)

I think the advantage is really that you reduce the amount of data copying required over traditional methods of reading a file.

> NOTE: 
>
> 1、这是典型的的"avoid-copy-optimization"

If your application can use the data "in place" in a memory-mapped file, it can come in without being copied; if you use a system call (e.g. Linux's `pread()` ) then that typically involves the kernel copying the data from its own buffers into user space. This extra copying not only takes time, but decreases the effectiveness of the CPU's caches by accessing this extra copy of the data.

If the data actually have to be read from the disc (as in physical I/O), then the OS still has to read them in, a page fault probably isn't any better performance-wise than a system call, but if they don't (i.e. already in the OS cache), performance should in theory be much better.

On the downside, there's no asynchronous interface to memory-mapped files - if you attempt to access a page which isn't mapped in, it generates a page fault then makes the thread wait for the I/O.

------

The obvious disadvantage to memory mapped files is on a 32-bit OS - you can easily run out of address space.

### [A](https://stackoverflow.com/a/192674)

I have used a memory mapped file to implement an 'auto complete' feature while the user is typing. I have well over 1 million product part numbers stored in a single index file. The file has some typical header information but the bulk of the file is a giant array of fixed size records sorted on the key field.

At runtime the file is memory mapped, cast to a `C`-style `struct` array, and we do a binary search to find matching part numbers as the user types. Only a few memory pages of the file are actually read from disk -- whichever pages are hit during the binary search.

1、Concurrency - I had an implementation problem where it would sometimes memory map the file multiple times in the same process space. This was a problem as I recall because sometimes the system couldn't find a large enough free block of virtual memory to map the file to. The solution was to only map the file once and thunk(形实转换程序) all calls to it. In retrospect using a full blown Windows service would of been cool.

2、Random Access - The binary search is certainly random access and lightning fast

3、Performance - The lookup is extremely fast. As users type a popup window displays a list of matching product part numbers, the list shrinks as they continue to type. There is no noticeable lag while typing.


