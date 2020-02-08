# [Memory protection](https://en.wikipedia.org/wiki/Memory_protection)

**Memory protection** is a way to control memory access rights on a computer, and is a part of most modern [instruction set architectures](https://en.wikipedia.org/wiki/Instruction_set_architecture) and [operating systems](https://en.wikipedia.org/wiki/Operating_system). The main purpose of memory protection is to prevent a [process](https://en.wikipedia.org/wiki/Process_(computing)) from accessing memory that has not been allocated to it. This prevents a bug or [malware](https://en.wikipedia.org/wiki/Malware)(恶意软件) within a process from affecting other processes, or the operating system itself. Protection may encompass(环绕) all accesses to a specified area of memory, write accesses, or attempts to execute the contents of the area. An attempt to access unowned memory results in a hardware [fault](https://en.wikipedia.org/wiki/Trap_(computing)), called a [segmentation fault](https://en.wikipedia.org/wiki/Segmentation_fault) or [storage violation](https://en.wikipedia.org/wiki/Storage_violation) exception, generally causing [abnormal termination](https://en.wikipedia.org/wiki/Abnormal_termination) of the offending process. Memory protection for [computer security](https://en.wikipedia.org/wiki/Computer_security) includes additional techniques such as [address space layout randomization](https://en.wikipedia.org/wiki/Address_space_layout_randomization) and [executable space protection](https://en.wikipedia.org/wiki/Executable_space_protection).

## Methods



### Segmentation

[Segmentation](https://en.wikipedia.org/wiki/Segmentation_(memory)) 

> NOTE: 这种方式现代OS以及很少采用了。

### Paged virtual memory

*Main article:* [Paged virtual memory](https://en.wikipedia.org/wiki/Paged_virtual_memory)

> NOTE: 这种方式是目前采用最多的。