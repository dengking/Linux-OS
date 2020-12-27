# sbrk

是在阅读 wikipedia [C dynamic memory allocation # Heap-based](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation#Heap-based) 时，发现了其中提及了 [sbrk](https://en.wikipedia.org/wiki/Sbrk)。



## man7 [brk(2) — Linux manual page](https://man7.org/linux/man-pages/man2/brk.2.html) 

```C++
#include <unistd.h>

int brk(void *addr);

void *sbrk(intptr_t increment);
```

`brk()` and `sbrk()` change the location of the **program break**, which defines the end of the process's **data segment** (i.e., the **program break** is the first location after the end of the **uninitialized data segment**). Increasing the program break has the effect of  allocating memory to the process; decreasing the break deallocates memory.

> NOTE: 关于 program break，参见 `Kernel\Guide\Multitasking\Process-model\Process-resource\Process-memory-model\Linux-implementation\Program-break` 章节。
>
> 上述 **uninitialized data segment**，其实就是bss。



## wikipedia [sbrk](https://en.wikipedia.org/wiki/Sbrk)