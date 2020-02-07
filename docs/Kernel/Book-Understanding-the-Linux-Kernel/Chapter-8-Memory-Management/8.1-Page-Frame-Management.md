# 8.1. Page Frame Management

We saw in the section "Paging in Hardware" in Chapter 2 how the Intel Pentium processor can use two different page frame sizes: 4 KB and 4 MB (or 2 MB if PAE is enabled see the section "The Physical Address Extension (PAE) Paging Mechanism" in Chapter 2). Linux adopts the smaller 4 KB page frame size as the **standard memory allocation unit**. This makes things simpler for two reasons:

- The Page Fault exceptions issued by the paging circuitry are easily interpreted. Either the page requested exists but the process is not allowed to address it, or the page does not exist. In the second case, the memory allocator must find a free 4 KB page frame and assign it to the process.
- Although both 4 KB and 4 MB are multiples of all disk block sizes, transfers of data between main memory and disks are in most cases more efficient when the smaller size is used.

## 8.1.1. Page Descriptors

The kernel must keep track of the current status of each **page frame**. For instance, it must be able to distinguish the **page frames** that are used to contain pages that belong to processes from those that contain kernel code or kernel data structures. Similarly, it must be able to determine whether a page frame in dynamic memory is free. A page frame in dynamic memory is free if it does not contain any useful data. It is not free when the page frame contains data of a User Mode process, data of a software cache, dynamically allocated kernel data structures, buffered data of a device driver, code of a kernel module, and so on.

State information of a **page frame** is kept in a **page descriptor** of type  `page` , whose fields are shown in Table 8-1. All **page descriptors** are stored in the  `mem_map` array. Because each descriptor is 32 bytes long, the space required by  `mem_map` is slightly less than 1% of the whole RAM. The `virt_to_page(addr)` macro yields the address of the **page descriptor** associated with the linear address  `addr` . The `pfn_to_page(pfn)` macro yields the address of the **page descriptor** associated with the **page frame** having number  `pfn` .

> NOTE: 根据page frame来获得其对应的page descriptor。

Table 8-1. The fields of the page descriptor

| Type                     | Name        | Description                                                  |
| ------------------------ | ----------- | ------------------------------------------------------------ |
| `unsigned long`          | `flags`     | Array of flags (see Table 8-2). Also encodes the zone number to which the page frame belongs. |
| `atomic_t`               | `_count`    | Page frame's reference counter.                              |
| `atomic_t`               | `_mapcount` | Number of Page Table entries that refer to the **page frame** ( - 1 if none). |
| `unsigned long`          | `private`   | Available to the kernel component that is using the page (for instance, it is a buffer head pointer in case of buffer page; see "Block Buffers and Buffer Heads" in Chapter 15). If the page is free, this field is used by the buddy system (see later in this chapter). |
| `struct address_space *` | `mapping`   | Used when the page is inserted into the page cache (see the section "The Page Cache" in Chapter 15), or when it belongs to an anonymous  region (see the section "Reverse Mapping for Anonymous Pages" in Chapter 17). |
| `unsigned long`          | `index`     | Used by several kernel components with different meanings. For instance, it identifies the position of the data stored in the page frame within the page's disk image or within an anonymous region (Chapter 15), or it stores a swapped-out **page identifier** (Chapter 17). |
| `struct list_head`       | `lru`       | Contains pointers to the least recently used doubly linked list of pages. |

You don't have to fully understand the role of all fields in the page descriptor right now. In the following chapters, we often come back to the fields of the page descriptor. Moreover, several fields have different meaning, according to whether the page frame is free or what kernel component is using the page frame.