# Memory-mapped file



## wikipedia [Memory-mapped file](https://en.wikipedia.org/wiki/Memory-mapped_file)

A **memory-mapped file** is a segment of [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory)[[1\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-:0-1) that has been assigned a direct byte-for-byte correlation with some portion of a file or file-like resource. This resource is typically a file that is physically present on disk, but can also be a device, shared memory object, or other resource that the [operating system](https://en.wikipedia.org/wiki/Operating_system) can reference through a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor). Once present, this correlation between the file and the memory space permits applications to treat the mapped portion as if it were primary memory.

### Common uses

Perhaps the most common use for a memory-mapped file is the [process loader](https://en.wikipedia.org/wiki/Loader_(computing)) in most modern operating systems (including [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) and [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems.) When a [process](https://en.wikipedia.org/wiki/Process_(computing)) is started, the operating system uses a memory mapped file to bring the executable file, along with any loadable modules, into memory for execution. Most memory-mapping systems use a technique called [demand paging](https://en.wikipedia.org/wiki/Demand_paging), where the file is loaded into physical memory in subsets (one page each), and only when that page is actually referenced.[[11\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-11) In the specific case of executable files, this permits the OS to selectively load only those portions of a process image that actually need to execute.

Another common use for memory-mapped files is to share memory between multiple processes. In modern [protected mode](https://en.wikipedia.org/wiki/Protected_mode) operating systems, processes are generally not permitted to access memory space that is allocated for use by another process. (A program's attempt to do so causes [invalid page faults](https://en.wikipedia.org/wiki/Page_fault#Invalid) or [segmentation violations](https://en.wikipedia.org/wiki/Segmentation_violation).) There are a number of techniques available to safely **share memory**, and **memory-mapped file I/O** is one of the most popular. Two or more applications can simultaneously map a single physical file into memory and access this memory. For example, the Microsoft Windows operating system provides a mechanism for applications to memory-map a shared segment of the system's page file itself and share data via this section.

> NOTE: inter-process communication

### Platform support

Some free portable implementations of memory-mapped files for Microsoft Windows and POSIX-compliant platforms are:

- Boost.Interprocess,[[15\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-15) in [Boost C++ Libraries](https://en.wikipedia.org/wiki/Boost_C%2B%2B_Libraries)
- Boost.Iostreams,[[16\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-16) also in [Boost C++ Libraries](https://en.wikipedia.org/wiki/Boost_C%2B%2B_Libraries)
- Fmstream[[17\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-17)
- Cpp-mmf[[18\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-18)