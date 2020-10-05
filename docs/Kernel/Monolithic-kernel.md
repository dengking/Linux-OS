# Monolithic kernel

“monolithic”的意思是 集成的、一体化的，monolithic kernel的意思是“集成核”，Linux采用的就是这种结构。

## wikipedia [Monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)

A **monolithic kernel** is an operating system architecture where the entire operating system is working in [kernel space](https://en.wikipedia.org/wiki/Kernel_space). The monolithic model differs from other operating system architectures (such as the [microkernel](https://en.wikipedia.org/wiki/Microkernel) architecture)[[1\]](https://en.wikipedia.org/wiki/Monolithic_kernel#cite_note-1)[[2\]](https://en.wikipedia.org/wiki/Monolithic_kernel#cite_note-2) in that it alone defines a high-level virtual interface over computer hardware. A set of primitives or [system calls](https://en.wikipedia.org/wiki/System_call) implement all operating system services such as [process](https://en.wikipedia.org/wiki/Process_(computing)) management, [concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science)), and [memory management](https://en.wikipedia.org/wiki/Memory_management). Device drivers can be added to the kernel as [modules](https://en.wikipedia.org/wiki/Module_(programming)).

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/OS-structure2.svg/800px-OS-structure2.svg.png)





Structure of monolithic kernel,microkernel and hybrid kernel-based operating systems

## Loadable modules

Modular operating systems such as [OS-9](https://en.wikipedia.org/wiki/OS-9) and most modern monolithic operating systems such as [OpenVMS](https://en.wikipedia.org/wiki/OpenVMS), [Linux](https://en.wikipedia.org/wiki/Linux_kernel), [BSD](https://en.wikipedia.org/wiki/BSD), [SunOS](https://en.wikipedia.org/wiki/SunOS), [AIX](https://en.wikipedia.org/wiki/AIX), and [MULTICS](https://en.wikipedia.org/wiki/MULTICS) can dynamically load (and unload) executable modules at runtime.

This modularity of the operating system is at the binary (image) level and not at the architecture level. **Modular monolithic operating systems** are not to be confused with the architectural level of modularity inherent in [server-client](https://en.wikipedia.org/wiki/Microkernel) operating systems (and its derivatives sometimes marketed as [hybrid kernel](https://en.wikipedia.org/wiki/Hybrid_kernel)) which use microkernels and servers (not to be mistaken for modules or daemons).

Practically speaking, dynamically loading modules is simply a more flexible way of handling the operating system image at runtime—as opposed to rebooting with a different operating system image. The modules allow easy extension of the operating systems' capabilities as required.[[3\]](https://en.wikipedia.org/wiki/Monolithic_kernel#cite_note-3) Dynamically loadable modules incur a small overhead when compared to building the module into the operating system image.

However, in some cases, loading modules dynamically (as-needed) helps to keep the amount of code running in [kernel space](https://en.wikipedia.org/wiki/Kernel_space) to a minimum; for example, to minimize operating system footprint for embedded devices or those with limited hardware resources. Namely, an unloaded module need not be stored in scarce [random access memory](https://en.wikipedia.org/wiki/Random_access_memory).

