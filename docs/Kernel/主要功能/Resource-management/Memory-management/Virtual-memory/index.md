# Virtual memory

## Why use virtual memory?

在文章 Abstraction-and-virtual 中，我们知道

> virtual也是一种抽象，一种分层，这种分层所带来的价值就是解耦。

显然virtual memory是符合abstraction principle的。

下面说明使用virtual address的解耦：

process在运行的时候使用virtual memory address，由OS根据page table将virtual address翻译为physical address；与process直接使用physical address相比，这种设计多添加了一层：转换层。这种设计带来的价值是：它解耦了process的page和page的存储位置，具体来讲就是按照这种设计，page既可以位于RAM，也可以位于disk，而如果直接使用physical address的话，则process的page只能够位于RAM中。所以可以看出，virtual address解耦了process的page和page的存储位置。

那"解耦"带来了什么价值呢？

总的来说是transparency: hide细节，让很多hardware、OS kernel层的optimization称为可能，hardware、OS kernel层的optimization对process层是透明(transparency)的。

hardware、OS kernel层的optimization包括: 

1) wikipedia [Virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) # Primary benefit 中描述的一些价值就是它所带来的

2) wikipedia [Virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) # Properties 

### Virtual memory and fragmentation

在 `Kernel\Guide\Memory-management\Fragmentation` 中讨论了fragmentation，在`Kernel\Guide\Memory-management\Fragmentation\Heap-fragmentation` 中收录了cpp4arduino [What is Heap Fragmentation?](https://cpp4arduino.com/2018/11/06/what-is-heap-fragmentation.html) 中讨论了virtual memory 和fragmentation之间的内容:

> The programs running on our computers use Virtual Memory. The value of the pointer is not the physical location in the RAM; instead, the CPU translates the address on the fly. This decoupling allows defragmenting the RAM without moving anything but requires dedicated hardware that we do not have on our microcontrollers.





## wikipedia [Virtual memory](https://en.wikipedia.org/wiki/Virtual_memory)

> NOTE: [Virtual memory](https://en.wikipedia.org/wiki/Virtual_memory)技术的相关概念都会在名称前面加上“virtual"修饰词，比如：
>
> - [virtual addresses](https://en.wikipedia.org/wiki/Virtual_address_space)
> - [virtual address spaces](https://en.wikipedia.org/wiki/Virtual_address_space)

In [computing](https://en.wikipedia.org/wiki/Computing), **virtual memory** (also **virtual storage**) is a [memory management](https://en.wikipedia.org/wiki/Memory_management_(operating_systems)) technique that provides an "idealized abstraction of the storage resources that are actually available on a given machine" which "creates the illusion to users of a very large (main) memory." 

The computer's [operating system](https://en.wikipedia.org/wiki/Operating_system), using a combination of hardware and software, maps [memory addresses](https://en.wikipedia.org/wiki/Memory_address) used by a program, called *[virtual addresses](https://en.wikipedia.org/wiki/Virtual_address_space)*, into *physical addresses* in [computer memory](https://en.wikipedia.org/wiki/Computer_memory).

> NOTE: 由OS来执行上述映射。
>
> 在[这篇文章](https://cs61.seas.harvard.edu/wiki/2016/Kernel2X)中，有这样的描述：
>
> **Virtual address** When we say virtual address, that refers to a location in a process's address space. In other words, a **pointer**! 
>
> 也就是说，我们一直使用的pointer，实际是virtual address；

[Main storage](https://en.wikipedia.org/wiki/Main_storage#Primary_storage), as seen by a process or task, appears as a contiguous [address space](https://en.wikipedia.org/wiki/Address_space) or collection of contiguous [segments](https://en.wikipedia.org/wiki/Memory_segmentation). The operating system manages [virtual address spaces](https://en.wikipedia.org/wiki/Virtual_address_space) and the assignment of **real memory** to **virtual memory**. **Address translation hardware** in the CPU, often referred to as a [memory management unit](https://en.wikipedia.org/wiki/Memory_management_unit) or ***MMU***, automatically translates **virtual addresses** to **physical addresses**. Software within the operating system may extend these capabilities to provide a virtual address space that can exceed the capacity of real memory and thus reference more memory than is physically present in the computer.

> NOTE: 参见：[how is page size determined in virtual address space?](https://unix.stackexchange.com/questions/128213/how-is-page-size-determined-in-virtual-address-space)

### Primary benefit

The primary benefits of **virtual memory** include 

1) freeing applications from having to manage a shared memory space, 

2) increased security due to **memory isolation**, and 

3) being able to conceptually use more memory than might be physically available, using the technique of [paging](https://en.wikipedia.org/wiki/Paging).

> NOTE: memory isolation指的是每个process有一个独立的[virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space) 。



![img](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6e/Virtual_memory.svg/250px-Virtual_memory.svg.png)



> **Virtual memory** combines active [RAM](https://en.wikipedia.org/wiki/RAM) and inactive memory on [DASD](https://en.wikipedia.org/wiki/Direct_access_storage_device) （Direct-access storage device） to form a large range of contiguous addresses.

### Properties

Virtual memory makes application programming easier 

1) by hiding [fragmentation](https://en.wikipedia.org/wiki/Fragmentation_(computer)) (碎片） of physical memory; 

> NOTE: 关于virtual memory和fragmentation，在前面的"Why use virtual memory?"中进行了专门的介绍。

2) by delegating to the kernel the burden（责任） of managing the [memory hierarchy](https://en.wikipedia.org/wiki/Computer_data_storage#Hierarchy_of_storage) (eliminating the need for the program to handle [overlays](https://en.wikipedia.org/wiki/Overlay_(programming)) explicitly); and, when each process is run in its own dedicated address space, 

3) by obviating（消除） the need [to relocate](https://en.wikipedia.org/wiki/Relocation_(computer_science)) program code or to access memory with [relative addressing](https://en.wikipedia.org/wiki/Addressing_mode#PC-relative).

> NOTE: 核心观点是: makes application programming easier 

[Memory virtualization](https://en.wikipedia.org/wiki/Memory_virtualization) can be considered a generalization of the concept of virtual memory.



### Paged virtual memory

Nearly all current implementations of virtual memory divide a [virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space) into [pages](https://en.wikipedia.org/wiki/Page_(computer_memory)), blocks of contiguous virtual memory addresses. Pages on contemporary systems are usually at least 4 [kilobytes](https://en.wikipedia.org/wiki/Kilobyte) in size; systems with large virtual address ranges or amounts of real memory generally use larger page sizes.

> NOTE: 上面这段话是指将 [virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space)  按照  [pages](https://en.wikipedia.org/wiki/Page_(computer_memory)) 进行划分；

#### Page tables

[Page tables](https://en.wikipedia.org/wiki/Page_table) are used to translate the **virtual addresses** seen by the application into [physical addresses](https://en.wikipedia.org/wiki/Physical_address) used by the hardware to process instructions; such hardware that handles this specific translation is often known as the [memory management unit](https://en.wikipedia.org/wiki/Memory_management_unit). Each entry in the page table holds a **flag** indicating whether the corresponding page is in real memory or not. If it is in real memory, the page table entry will contain the **real memory address** at which the page is stored. When a reference is made to a page by the hardware, if the page table entry for the page indicates that it is not currently in real memory, the hardware raises a [page fault](https://en.wikipedia.org/wiki/Page_fault) [exception](https://en.wikipedia.org/wiki/Trap_(computing)), invoking the **paging supervisor component** of the [operating system](https://en.wikipedia.org/wiki/Operating_system).

> NOTE : 上面这段话中有一句非常重要的：**virtual addresses** seen by application while **physical addresses** use by hardware；即process在运行过程中所使用的是virtual address。

Systems can have one

1、**page table** for the whole system

2、separate page tables for each application and **segment**

3、a tree of page tables for large segments or some combination of these. 

If there is only one page table, different applications [running at the same time](https://en.wikipedia.org/wiki/Multiprogramming) use different parts of a single range of virtual addresses. If there are multiple page or segment tables, there are multiple virtual address spaces and concurrent applications with separate page tables redirect to different real addresses.

Some earlier systems with smaller real memory sizes, such as the [SDS 940](https://en.wikipedia.org/wiki/SDS_940), used *page registers* instead of page tables in memory for address translation.

#### Paging supervisor

This part of the operating system creates and manages **page tables**. If the hardware raises a **page fault exception**, the **paging supervisor** accesses secondary storage, returns the page that has the virtual address that resulted in the page fault, updates the page tables to reflect the physical location of the virtual address and tells the translation mechanism to restart the request.

When all physical memory is already in use, the paging supervisor must free a page in primary storage to hold the swapped-in page. The supervisor uses one of a variety of [page replacement algorithms](https://en.wikipedia.org/wiki/Page_replacement_algorithm) such as [least recently used](https://en.wikipedia.org/wiki/Page_replacement_algorithm#Least_recently_used) to determine which page to free.

#### Pinned pages

Operating systems have memory areas that are *pinned* (never swapped to secondary storage). Other terms used are *locked*, *fixed*, or *wired* pages. For example, [interrupt](https://en.wikipedia.org/wiki/Interrupt) mechanisms rely on an array of pointers to their handlers, such as [I/O](https://en.wikipedia.org/wiki/I/O) completion and [page fault](https://en.wikipedia.org/wiki/Page_fault). If the pages containing these pointers or the code that they invoke were pageable, interrupt-handling would become far more complex and time-consuming, particularly in the case of page fault interruptions. Hence, some part of the page table structures is not pageable.

### Segmented virtual memory

> NOTE: 这种并非主流的，pass掉。



## See also

- [Page table](https://en.wikipedia.org/wiki/Page_table)
- [Page (computer memory)](https://en.wikipedia.org/wiki/Page_(computer_memory))
- [Paging](https://en.wikipedia.org/wiki/Paging)
- [Virtual Addresses](https://www.bottomupcs.com/virtual_addresses.xhtml)