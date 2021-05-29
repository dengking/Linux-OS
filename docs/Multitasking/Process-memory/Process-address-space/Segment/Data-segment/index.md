# Data segment

"data segment段=bss段+initialized data segment段"

## wikipedia [Data segment](https://en.wikipedia.org/wiki/Data_segment)

In [computing](https://en.wikipedia.org/wiki/Computing), a **data segment** (often denoted **.data**) is a portion of an [object file](https://en.wikipedia.org/wiki/Object_file) or the corresponding [address space](https://en.wikipedia.org/wiki/Address_space) of a program that contains **initialized** [static variables](https://en.wikipedia.org/wiki/Static_variable), that is, [global variables](https://en.wikipedia.org/wiki/Global_variable) and [static local variables](https://en.wikipedia.org/wiki/Static_local_variable). The size of this segment is determined by the size of the values in the program's source code, and does not change at [run time](https://en.wikipedia.org/wiki/Run_time_(program_lifecycle_phase)).

> NOTE: 在一些其他的文章中，也使用了 [data segment](https://en.wikipedia.org/wiki/Data_segment) 这个词，在其中的一些内容初读起来是会和上面的最后一句话 "and does not change at [run time](https://en.wikipedia.org/wiki/Run_time_(program_lifecycle_phase)) " 相矛盾的，在下面章节中，罗列了这些文章，这些文章主要是Linux OS相关的，其实它们是并不矛盾的，这些文章的内容涉及到了底层的实现细节，当深入这些实现细节后，会发现它们其实是并不矛盾的。



## Use case

下面这些文章中，也使用了data segment这个词语，初读起来，是和 wikipedia [Data segment](https://en.wikipedia.org/wiki/Data_segment) 中的 "The size of this segment is determined by the size of the values in the program's source code, and does not change at [run time](https://en.wikipedia.org/wiki/Run_time_(program_lifecycle_phase)) " 相矛盾的，参看 `Kernel\Guide\Multitasking\Process-model\Process-resource\Process-memory-model\Linux-implementation` 章节学习实现细节后，从实现角度来看，它们是并不矛盾的。

### wikipedia [C dynamic memory allocation # Implementations # Heap-based](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation#Heap-based)

Implementation of the allocator is commonly done using the [heap](https://en.wikipedia.org/wiki/Heap_memory), or [data segment](https://en.wikipedia.org/wiki/Data_segment). The allocator will usually expand and contract the heap to fulfill allocation requests.



### wikipedia [sbrk](https://en.wikipedia.org/wiki/Sbrk)

**brk** and **sbrk** are basic [memory management](https://en.wikipedia.org/wiki/Memory_management) [system calls](https://en.wikipedia.org/wiki/System_call) used in [Unix](https://en.wikipedia.org/wiki/Unix) and [Unix-like](https://en.wikipedia.org/wiki/Unix-like) operating systems to control the amount of memory allocated to the [data segment](https://en.wikipedia.org/wiki/Data_segment) of the [process](https://en.wikipedia.org/wiki/Process_(computing)).[[1\]](https://en.wikipedia.org/wiki/Sbrk#cite_note-1) 

> NOTE: 上面这段话中，说明了在Linux OS中的implementation中会改变 the [data segment](https://en.wikipedia.org/wiki/Data_segment) of the [process](https://en.wikipedia.org/wiki/Process_(computing))。



### man7 [brk(2) — Linux manual page](https://man7.org/linux/man-pages/man2/brk.2.html)

`brk()` and `sbrk()` change the location of the program break, which defines the end of the process's data segment (i.e., the **program break** is the first location after the end of the **uninitialized data segment**).