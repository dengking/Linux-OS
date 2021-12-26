# `futex`



## wikipedia [Futex](https://en.wikipedia.org/wiki/Futex)

In [computing](https://en.wikipedia.org/wiki/Computing), a **futex** (short for "fast userspace [mutex](https://en.wikipedia.org/wiki/Mutual_exclusion)") is a [kernel](https://en.wikipedia.org/wiki/Kernel_(operating_system)) [system call](https://en.wikipedia.org/wiki/System_call) that [programmers](https://en.wikipedia.org/wiki/Programmer) can use to implement basic [locking](https://en.wikipedia.org/wiki/Lock_(computer)), or as a building block for higher-level locking abstractions such as [semaphores](https://en.wikipedia.org/wiki/Semaphore_(programming)) and [POSIX](https://en.wikipedia.org/wiki/POSIX) mutexes or [condition variables](https://en.wikipedia.org/wiki/Condition_variable).

> NOTE: 
>
> 很多我们常用的synchronization都是基于它实现的

A futex consists of a [kernelspace](https://en.wikipedia.org/wiki/Kernel_(operating_system)) *wait queue* that is attached to an [atomic](https://en.wikipedia.org/wiki/Atomic_operations) [integer](https://en.wikipedia.org/wiki/Integer) in [userspace](https://en.wikipedia.org/wiki/Userspace). Multiple [processes](https://en.wikipedia.org/wiki/Process_(computing)) or [threads](https://en.wikipedia.org/wiki/Thread_(computer_science)) operate on the integer entirely in userspace (using [atomic operations](https://en.wikipedia.org/wiki/Atomic_operation) to avoid interfering(干涉、妨碍) with one another), and only resort to(使用) relatively expensive [system calls](https://en.wikipedia.org/wiki/System_call) to request operations on the **wait queue** (for example to wake up waiting processes, or to put the current process on the **wait queue**). A properly programmed futex-based lock will not use system calls except when the lock is contended; since most operations do not require arbitration(仲裁) between processes, this will not happen in most cases.

> NOTE: 
>
> 一、当lock没有竞争的时候，"A properly programmed futex-based lock will not use system calls except when the lock is contended"
>
> 二、上述所说的 " [atomic](https://en.wikipedia.org/wiki/Atomic_operations) [integer](https://en.wikipedia.org/wiki/Integer) " 指的是什么？其实就是在 [futex(2) — Linux manual page](https://man7.org/linux/man-pages/man2/futex.2.html) 中所说的**futex word**
>
> 三、上述对futex的介绍是基于futex的implementation的



## [futex(7) — Linux manual page](http://man7.org/linux/man-pages/man7/futex.7.html)

A futex is identified by a piece of memory which can be shared between processes or threads. In these different processes, the futex need not have **identical addresses**.  In its bare form, a futex has semaphore semantics; it is a counter that can be incremented and decremented atomically; processes can wait for the value to become positive.

> NOTE: 
>
> futex semaphore

Futex operation occurs entirely in user space for the noncontended case.  The kernel is involved only to arbitrate the contended case. As any sane(理智的，健全的) design will strive for noncontention, futexes are also optimized for this situation.

In its bare form, a futex is an aligned integer which is touched only by atomic assembler instructions.  This integer is four bytes long on all platforms.  Processes can share this integer using mmap(2), via shared memory segments, or because they share memory space, in which case the application is commonly called multithreaded.

### Semantics

## [futex(2) — Linux manual page](https://man7.org/linux/man-pages/man2/futex.2.html)



```C
long syscall(SYS_futex, 
             uint32_t *uaddr, 
             int futex_op, 
             uint32_t val,
             const struct timespec *timeout,   /* or: uint32_t val2 */
             uint32_t *uaddr2, 
             uint32_t val3
            );
```

### Introduction

The `futex()` system call provides a method for waiting until a certain condition becomes true. It is typically used as a blocking construct in the context of **shared-memory synchronization**. 

> NOTE: 
>
> 一、这段话其实是对futex功能的非常好的总结
>
> 二、需要注意的是: **shared-memory synchronization**包括如下情况:
>
> 1、thread **shared-memory synchronization**
>
> 这是天然支持的
>
> 2、process **shared-memory synchronization**
>
> 这是需要IPC的，下面进行了特别的说明

A futex is a 32-bit value—referred to below as a **futex word**—whose address is supplied to the `futex()` system call.  (Futexes are 32 bits in size on all platforms, including 64-bit systems.) All futex operations are governed by this value. In order to **share a futex between processes**, the futex is placed in a region of shared memory, created using (for example) mmap(2) or shmat(2). (Thus, the futex word may have different virtual addresses in different processes, but these addresses all refer to the same location in physical memory.) In a multithreaded program, it is sufficient to place the **futex word** in a global variable shared by all threads.

#### futex usage: blocking via a futex 

> NOTE: 
>
> 一、这一章首先介绍的是如何futex的基本操作: 使一个thread被block，作者将它简称为 "atomic **compare-and-block** operation"，这也是futex的主要功能
>
> 二、这章然后介绍如何使用futex实现一个lock，这个例子是非常好的，通过它我们是能够明白基本的lock的implementation

When executing a **futex operation** that requests to block a thread, the kernel will block only if the **futex word** has the value that the calling thread supplied (as one of the arguments of the `futex()` call) as the expected value of the **futex word**.  The loading of the **futex word**'s value, the comparison of that value with the expected value, and the actual blocking will happen atomically and will be totally ordered with respect to concurrent operations performed by other threads on the same **futex word**. Thus, the **futex word** is used to connect the synchronization in user space with the implementation of blocking by the kernel. Analogously(类似的) to an **atomic compare-and-exchange operation** that potentially changes shared memory, blocking via a futex is an atomic **compare-and-block** operation.

#### example: lock

One use of futexes is for implementing locks.  The state of the lock (i.e., acquired or not acquired) can be represented as an atomically accessed flag in **shared memory**.  In the uncontended case, a thread can access or modify the **lock state** with atomic instructions, for example atomically changing it from not acquired to acquired using an atomic compare-and-exchange instruction.  (Such instructions are performed entirely in user mode, and the kernel maintains no information about the lock state.)  On the other hand, a thread may be unable to acquire a lock because it is already acquired by another thread.  It then may pass the **lock's flag** as a **futex word** and the value representing the **acquired state** as the expected value to a `futex()` wait operation.  This futex() operation will block if and only if the lock is still acquired (i.e., the value in the futex word still matches the "acquired state").  When releasing the lock, a thread has to first reset the lock state to not acquired and then execute a futex operation that wakes threads blocked on the **lock flag** used as a futex word (this can be further optimized to avoid unnecessary wake-ups).  See futex(7) for more detail on how to use futexes.

> NOTE: 
>
> 一、将lock state放在shared memory中；
>
> 1、在"uncontended case"，thread能够通过atomic compare-and-exchange instruction来修改它的值；
>
> 2、在其他情况: 

### Arguments

The `uaddr` argument points to the **futex word**.

### Futex operations

> NOTE: 
>
> operation是非常之多的

### EXAMPLES         

> NOTE: 
>
> 简单的IPC

