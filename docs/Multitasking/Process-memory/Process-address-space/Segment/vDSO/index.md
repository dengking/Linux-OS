# vDSO

在阅读[folly](https://github.com/facebook/folly)/[folly](https://github.com/facebook/folly/tree/main/folly)/[concurrency](https://github.com/facebook/folly/tree/main/folly/concurrency)/[**CacheLocality.h**](https://github.com/facebook/folly/blob/main/folly/concurrency/CacheLocality.h) 时，其中有这样的介绍: 

> `AccessSpreader` uses the `getcpu` system call via VDSO and the precise locality information retrieved from sysfs by `CacheLocality`.

这引发了我对VDSO的探索。

## wikipedia [vDSO](https://en.wikipedia.org/wiki/VDSO)

**vDSO** (**virtual dynamic shared object**) is a kernel mechanism for exporting a carefully selected set of [kernel space](https://en.wikipedia.org/wiki/Kernel_space) routines to [user space](https://en.wikipedia.org/wiki/User_space) applications so that applications can call these kernel space routines in-process, without incurring the performance penalty of a [mode switch](https://en.wikipedia.org/wiki/Mode_switch) from [user mode](https://en.wikipedia.org/wiki/User_mode) to [kernel mode](https://en.wikipedia.org/wiki/Kernel_mode) that is inherent when calling these same kernel space routines by means of the [system call](https://en.wikipedia.org/wiki/System_call) interface.

> NOTE: 
>
> 上面这段话基本上解释了使用vDSO技术的原因: system call is slow



vDSO is a memory area allocated in user space which exposes some kernel functionalities. vDSO is [dynamically allocated](https://en.wikipedia.org/wiki/Dynamic_allocation), offers improved safety through [address space layout randomization](https://en.wikipedia.org/wiki/Address_space_layout_randomization), and supports more than four system calls. Some [C standard libraries](https://en.wikipedia.org/wiki/C_standard_libraries), like [glibc](https://en.wikipedia.org/wiki/Glibc), may provide vDSO links so that if the kernel does not have vDSO support, a traditional [syscall](https://en.wikipedia.org/wiki/Syscall) is made. vDSO helps to reduce the calling overhead on simple kernel routines, and it also can work as a way to select the best system-call method on some [computer architectures](https://en.wikipedia.org/wiki/Computer_architectures) such as [IA-32](https://en.wikipedia.org/wiki/IA-32).[[6\]](https://en.wikipedia.org/wiki/VDSO#cite_note-6) An advantage over other methods is that such exported routines can provide proper [DWARF](https://en.wikipedia.org/wiki/DWARF) (Debug With Attributed Record Format) debugging information. Implementation generally implies hooks in the dynamic linker to find the vDSOs.

> NOTE: 
>
> 一、
>
> 1、VDSO是一个memory area，它是dynamically allocated的，它包含了一些system call

vDSO uses standard mechanisms for [linking](https://en.wikipedia.org/wiki/Linker_(computing)) and [loading](https://en.wikipedia.org/wiki/Loader_(computing)) i.e. standard [Executable and Linkable Format](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format) (ELF) format. Implementation generally implies hooks in the dynamic linker to find the vDSOs.

> NOTE: 
>
> 上面这段话是对原文的一个重新整理，它主要描述VDSO的implementation，从上面的描述可以看出: VDSO并没有使用的是ELF，是基于现有的linking、loading来实现的。

vDSO was developed to offer the **vsyscall** features while overcoming its limitations.

> NOTE: 
>
> 关于 vDSO 和 **vsyscall** ，在 stackoverflow [What are vdso and vsyscall?](https://stackoverflow.com/questions/19938324/what-are-vdso-and-vsyscall) 中进行了讨论 

## stackoverflow [What are vdso and vsyscall?](https://stackoverflow.com/questions/19938324/what-are-vdso-and-vsyscall)



[A](https://stackoverflow.com/a/19942352/10173843)

> NOTE: 这个回答是非常好的



## see also

ibm [vdso - Optimize system call performance](https://www.ibm.com/docs/ja/linux-on-systems?topic=kp-vdso-3)

man 7 [vdso](https://man7.org/linux/man-pages/man7/vdso.7.html)