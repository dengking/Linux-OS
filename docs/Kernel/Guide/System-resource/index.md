# System resource



## wikipedia [System resource](https://en.wikipedia.org/wiki/System_resource)

In [computing](https://en.wikipedia.org/wiki/Computing), a **system resource**, or simply **resource**, is any physical or virtual component of limited availability within a computer system. Every device connected to a computer system is a resource. Every internal system component is a resource. Virtual system resources include [files](https://en.wikipedia.org/wiki/Computer_file) (concretely [file handles](https://en.wikipedia.org/wiki/File_handle)), network connections (concretely [network sockets](https://en.wikipedia.org/wiki/Network_socket)), and memory areas. Managing resources is referred to as [resource management](https://en.wikipedia.org/wiki/Resource_management_(computing)), and includes both preventing [resource leaks](https://en.wikipedia.org/wiki/Resource_leak) (not releasing a resource when a process has finished using it) and dealing with [resource contention](https://en.wikipedia.org/wiki/Resource_contention) (when multiple processes wish to access a limited resource).



### Major resource types

1、[Interrupt request](https://en.wikipedia.org/wiki/Interrupt_request_(PC_architecture)) (IRQ) lines

2、[Direct memory access](https://en.wikipedia.org/wiki/Direct_memory_access) (DMA) channels

3、[Locks](https://en.wikipedia.org/wiki/Lock_(computer_science))

4、External [Devices](https://en.wikipedia.org/wiki/Peripheral)

5、External memory or objects, such as memory managed in native code, from Java; or objects in the [Document Object Model](https://en.wikipedia.org/wiki/Document_Object_Model) (DOM), from [JavaScript](https://en.wikipedia.org/wiki/JavaScript)



### General resources

- [CPU](https://en.wikipedia.org/wiki/Central_processing_unit), both time on a single CPU and use of multiple CPUs – see [multitasking](https://en.wikipedia.org/wiki/Multitasking)
- [Random-access memory](https://en.wikipedia.org/wiki/Random-access_memory) and [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) – see [memory management](https://en.wikipedia.org/wiki/Memory_management)
- [Hard disk](https://en.wikipedia.org/wiki/Hard_disk) drives, include space generally, contiguous free space (such as for swap space), and use of multiple physical devices ("spindles"), since using multiple devices allows parallelism
- Cache space, including [CPU cache](https://en.wikipedia.org/wiki/CPU_cache) and MMU cache ([translation lookaside buffer](https://en.wikipedia.org/wiki/Translation_lookaside_buffer))
- [Network](https://en.wikipedia.org/wiki/Computer_networking) throughput
- [Electrical power](https://en.wikipedia.org/wiki/Power_management)
- [Input/output](https://en.wikipedia.org/wiki/Input/output) operations
- [Randomness](https://en.wikipedia.org/wiki/Randomness)



## 实现分析

显然，OS需要描述各种system resource，需要记录下每个进程占用 哪些资源。

## limit

系统资源是有限(具有上限)，所以一个系统能够支持的最大用户数也是有上限的，这是在阅读 https://idea.popcount.org/2014-04-03-bind-before-connect/ 时，想到的

