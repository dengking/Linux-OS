# Fragmentation 



## wikipedia [Fragmentation (computing)](https://en.wikipedia.org/wiki/Fragmentation_(computing))



### Basic principle

> NOTE: 理解这一段的核心是理解"chunk"这个词，它表示的是连续的内存空间

When a computer program requests blocks of memory from the computer system, the blocks are allocated in chunks. When the computer program is finished with a chunk, it can free it back to the system, making it available to later be allocated again to another or the same program. The size and the amount of time a chunk is held by a program varies. During its lifespan, a computer program can request and free many chunks of memory.

When a program is started, the free memory areas are long and contiguous. Over time and with use, the long contiguous regions become fragmented into smaller and smaller contiguous areas. Eventually, it may become impossible for the program to obtain large contiguous chunks of memory.

### Types

#### Internal fragmentation

> NOTE: 于此相关的是alignment，参见工程hardware的`CPU\Memory-access\Memory-alignment`章节。
>
> 显然这种fragmentation是由computer的internal机制所决定的，可以说是它天生的

Due to the rules governing [memory allocation](https://en.wikipedia.org/wiki/Memory_allocation), more computer memory is sometimes [allocated](https://en.wikipedia.org/wiki/Memory_allocation) than is needed. For example, memory can only be provided to programs in chunks (multiple of 4), and as a result if a program requests perhaps 29 bytes, it will actually get a chunk of 32 bytes. When this happens, the excess memory goes to waste. In this scenario, the unusable memory is contained within an allocated region. This arrangement, termed fixed partitions, suffers from inefficient memory use - any process, no matter how small, occupies an entire partition. This waste is called **internal fragmentation**.[[1\]](https://en.wikipedia.org/wiki/Fragmentation_(computing)#cite_note-1)[[2\]](https://en.wikipedia.org/wiki/Fragmentation_(computing)#cite_note-2)

Unlike other types of fragmentation, internal fragmentation is difficult to reclaim; usually the best way to remove it is with a design change. For example, in [dynamic memory allocation](https://en.wikipedia.org/wiki/Dynamic_memory_allocation), [memory pools](https://en.wikipedia.org/wiki/Memory_pool) drastically cut internal fragmentation by spreading the space overhead over a larger number of objects.

#### External fragmentation

External fragmentation arises when free memory is separated into small blocks and is interspersed by allocated memory. It is a weakness of certain storage allocation algorithms, when they fail to order memory used by programs efficiently. The result is that, although free storage is available, it is effectively unusable because it is divided into pieces that are too small individually to satisfy the demands of the application. The term "external" refers to the fact that the unusable storage is outside the allocated regions.

#### Data fragmentation

> NOTE: TODO

## stackoverflow [Memory fragmentation](https://stackoverflow.com/questions/37186421/memory-fragmentation)

[A](https://stackoverflow.com/a/37187157)

As per **ISO/IEC 9899:201x -> 7.22.3**

> The order and contiguity of storage allocated by successive calls to the aligned_alloc, calloc, malloc, and realloc functions is unspecified.

A good memory manager will be able to tackle the issue to an extent. However, there are other aspects like data alignment [[1\]](http://www.memorymanagement.org/glossary/p.html) which causes internal fragmentation.

**What you could do if you rely on inbuilt memory management?**

1. Use a profiler - say valgrind - with memory check option to find the memory which is not freed after use. Example:

    

    ```c
     valgrind --leak-check=yes myprog arg1 arg2
    ```

2. Follow good practices. Example - In C++, if you intend others to inherit from your polymorphic class, you may declare its destructor virtual.

3. Use smart pointers.

**Notes:**

1. [Internal fragmentation](http://www.memorymanagement.org/glossary/i.html#term-internal-fragmentation).
2. If you were to use your own memory management system, you may consider [Boehm-Demers-Weiser](http://hboehm.info/gc/) garbage collector.
3. [Valgrind ](http://valgrind.org/)Instrumentation Framework.
4. Memory not freed after use will contribute to fragmentation.



## Example

### 1) wikipedia [Memory-mapped file](https://en.wikipedia.org/wiki/Memory-mapped_file):

For small files, memory-mapped files can result in a waste of [slack space](https://en.wikipedia.org/wiki/Slack_space)[[7\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-7) as memory maps are always aligned to the page size, which is mostly 4 KiB. Therefore, a 5 KiB file will allocate 8 KiB and thus 3 KiB are wasted. 

