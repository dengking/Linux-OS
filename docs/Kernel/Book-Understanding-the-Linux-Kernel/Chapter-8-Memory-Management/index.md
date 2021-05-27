# Chapter 8. Memory Management

We saw in Chapter 2 how Linux takes advantage of 80 x 86's segmentation and paging circuits to translate logical addresses into physical ones. We also mentioned that some portion of RAM is permanently assigned to the kernel and used to store both the kernel code and the static kernel data structures.

> NOTE: 现代大多数都是采用的基于page的memory management。

The remaining part of the RAM is called *dynamic memory* . It is a valuable resource, needed not only by the processes but also by the kernel itself. In fact, the performance of the entire system depends on how efficiently **dynamic memory** is managed. Therefore, all current multitasking operating systems try to optimize the use of **dynamic memory**, assigning it only when it is needed and freeing it as soon as possible. Figure 8-1 shows schematically the **page frames** used as **dynamic memory**; see the section "Physical Memory Layout" in Chapter 2 for details.

This chapter, which consists of three main sections, describes how the **kernel** allocates **dynamic memory** for its own use. The sections "Page Frame Management" and "Memory Area Management" illustrate two different techniques for handling physically contiguous memory areas, while the section "Noncontiguous Memory Area Management" illustrates a third technique that handles noncontiguous memory areas. In these sections we'll cover topics such as memory zones, kernel mappings, the buddy system, the slab cache, and memory pools.

![](./Figure-8-1-Dynamic-memory.jpg)