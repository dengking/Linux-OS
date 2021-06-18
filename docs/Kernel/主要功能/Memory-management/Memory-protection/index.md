# Memory protection

让我们再次回忆在`Architecture-of-computing-system`的“通过architecture来分析OS的作用”段中总结的OS的两大作用，简而言之就是管理hardware和为process提供 **execution environment** ，对于运行于它之中的process，OS kernel需要对process的所有行为（包括memory access）都了如指掌，它能够发现process是否进行了错误的操作，一旦发现它就会“提醒”这个process，本文所描述的memory protection就属于此，即OS kernel对process的memory access行为进行管控。

## wikipedia [Memory protection](https://en.wikipedia.org/wiki/Memory_protection)

**Memory protection** is a way to control memory access rights on a computer, and is a part of most modern [instruction set architectures](https://en.wikipedia.org/wiki/Instruction_set_architecture) and [operating systems](https://en.wikipedia.org/wiki/Operating_system). The main purpose of memory protection is to prevent a [process](https://en.wikipedia.org/wiki/Process_(computing)) from accessing memory that has not been allocated to it. This prevents a bug or [malware](https://en.wikipedia.org/wiki/Malware)(恶意软件) within a process from affecting other processes, or the operating system itself. Protection may encompass(环绕) all accesses to a specified area of memory, write accesses, or attempts to execute the contents of the area. An attempt to access unowned memory results in a hardware [fault](https://en.wikipedia.org/wiki/Trap_(computing)), called a [segmentation fault](https://en.wikipedia.org/wiki/Segmentation_fault) or [storage violation](https://en.wikipedia.org/wiki/Storage_violation) exception, generally causing [abnormal termination](https://en.wikipedia.org/wiki/Abnormal_termination) of the offending process. Memory protection for [computer security](https://en.wikipedia.org/wiki/Computer_security) includes additional techniques such as [address space layout randomization](https://en.wikipedia.org/wiki/Address_space_layout_randomization) and [executable space protection](https://en.wikipedia.org/wiki/Executable_space_protection).

### Methods



#### Segmentation

[Segmentation](https://en.wikipedia.org/wiki/Segmentation_(memory)) 

> NOTE: 这种方式现代OS以及很少采用了。

#### Paged virtual memory

*Main article:* [Paged virtual memory](https://en.wikipedia.org/wiki/Paged_virtual_memory)

> NOTE: 这种方式是目前采用最多的。



## SUMMARY

本文仅仅讨论的是memory protection的概念，OS kernel实际的实现远比这要复杂。关于具体的实现细节，参见Book-Understanding-the-Linux-Kernel的[2.4-Paging-in-Hardware](https://dengking.github.io/Linux-OS/Kernel/Book-Understanding-the-Linux-Kernel/Chapter-2-Memory-Addressing/2.4-Paging-in-Hardware/)。由于OS kernel所采用的memory protection，则一旦process的memory access违法，则它能够立即发现并予以通知。与此相关的是一类programming error，叫做memory access error，在`Memory-access-error`中进行了详细描述。