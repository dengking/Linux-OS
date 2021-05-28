# Cooperative multitasking



## wikipedia [Cooperative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking)

**Cooperative multitasking**, also known as **non-preemptive multitasking**, is a style of [computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking) in which the [operating system](https://en.wikipedia.org/wiki/Operating_system) never initiates a [context switch](https://en.wikipedia.org/wiki/Context_switch) from a running [process](https://en.wikipedia.org/wiki/Process_(computing)) to another process. Instead, processes voluntarily(主动) [yield control](https://en.wikipedia.org/wiki/Yield_(multithreading)) periodically(定期的) or when idle or logically [blocked](https://en.wikipedia.org/wiki/Blocking_(computing)) in order to enable multiple applications to be run concurrently. This type of multitasking is called "cooperative" because all programs must cooperate for the entire scheduling scheme to work. In this scheme, the [process scheduler](https://en.wikipedia.org/wiki/Process_scheduler) of an operating system is known as a **cooperative scheduler**, having its role reduced down to starting the processes and letting them return control back to it voluntarily.[[1\]](https://en.wikipedia.org/wiki/Cooperative_multitasking#cite_note-pcmag-1)[[2\]](https://en.wikipedia.org/wiki/Cooperative_multitasking#cite_note-classiccmp-2)

> NOTE: 由process主动 yield control，而不是有operating system；



### Usage



Although it is rarely used in modern larger systems, it is widely used in memory-constrained [embedded systems](https://en.wikipedia.org/wiki/Embedded_system) and also, in specific applications such as [CICS](https://en.wikipedia.org/wiki/CICS) or the [JES2](https://en.wikipedia.org/wiki/JES2) subsystem. Cooperative multitasking was the **primary scheduling scheme** for 16-bit applications employed by [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) before [Windows 95](https://en.wikipedia.org/wiki/Windows_95) and [Windows NT](https://en.wikipedia.org/wiki/Windows_NT) (such as [Windows 3.1x](https://en.wikipedia.org/wiki/Windows_3.1x)), and by the [classic Mac OS](https://en.wikipedia.org/wiki/Classic_Mac_OS). [Windows 9x](https://en.wikipedia.org/wiki/Windows_9x) used non-[preemptive multitasking](https://en.wikipedia.org/wiki/Preemptive_multitasking) for 16-bit legacy applications, and the [PowerPC](https://en.wikipedia.org/wiki/PowerPC) Versions of Mac OS X prior to [Leopard](https://en.wikipedia.org/wiki/Mac_OS_X_v10.5) used it for [classic](https://en.wikipedia.org/wiki/Classic_(Mac_OS_X)) applications.[[1\]](https://en.wikipedia.org/wiki/Cooperative_multitasking#cite_note-pcmag-1) [NetWare](https://en.wikipedia.org/wiki/NetWare), which is a network-oriented operating system, used cooperative multitasking up to NetWare 6.5. Cooperative multitasking is still used on [RISC OS](https://en.wikipedia.org/wiki/RISC_OS) systems.[[3\]](https://en.wikipedia.org/wiki/Cooperative_multitasking#cite_note-3)

**Cooperative multitasking** is used with [await](https://en.wikipedia.org/wiki/Await) in languages with a **single-threaded**  **event-loop** in their runtime, like JavaScript or Python.

### Problems

As a **cooperatively multitasked system** relies on each process regularly giving up time to other processes on the system, one poorly designed program can consume all of the CPU time for itself, either by performing extensive calculations or by [busy waiting](https://en.wikipedia.org/wiki/Busy_wait); both would cause the whole system to [hang](https://en.wikipedia.org/wiki/Hang_(computing)). In a [server](https://en.wikipedia.org/wiki/Server_(computing)) environment, this is a hazard that makes the entire environment unacceptably fragile.[[1\]](https://en.wikipedia.org/wiki/Cooperative_multitasking#cite_note-pcmag-1) However, cooperative multitasking allows much simpler implementation of applications because their execution is never unexpectedly interrupted by the process scheduler; for example, various [functions](https://en.wikipedia.org/wiki/Subroutine) inside the application do not need to be [reentrant](https://en.wikipedia.org/wiki/Reentrancy_(computing)).[[2\]](https://en.wikipedia.org/wiki/Cooperative_multitasking#cite_note-classiccmp-2)

In contrast, [preemptive](https://en.wikipedia.org/wiki/Preemption_(computing)) multitasking interrupts applications and gives control to other processes outside the application's control.


