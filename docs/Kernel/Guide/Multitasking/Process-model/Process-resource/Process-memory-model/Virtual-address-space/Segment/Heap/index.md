# Heap

## wikipedia [Data segment # Program memory # Heap](https://en.wikipedia.org/wiki/Data_segment#Heap)

The heap area commonly begins at the end of the `.bss` and `.data` segments and grows to larger addresses from there. The heap area is managed by [malloc](https://en.wikipedia.org/wiki/Malloc), calloc, realloc, and free, which may use the [brk](https://en.wikipedia.org/wiki/Sbrk) and [sbrk](https://en.wikipedia.org/wiki/Sbrk) system calls to adjust its size (note that the use of brk/sbrk and a single "heap area" is not required to fulfill the contract(合同、契约) of malloc/calloc/realloc/free; they may also be implemented using [mmap](https://en.wikipedia.org/wiki/Mmap)/munmap to reserve/unreserve potentially non-contiguous regions of virtual memory into the process' [virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space)). The heap area is shared by all threads, shared libraries, and dynamically loaded modules in a process.

