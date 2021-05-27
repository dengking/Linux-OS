# Kernel control path and reentrant kernel

> 本节的内容主要源自chapter 1.6.3. Reentrant Kernels

在前一节中，我们已经建立起来了Linux OS kernel的运行模型了，即OS kernel是event-driven的，那现在让我们站在内核设计者的角度来思考如何来实现？

内核的设计者会追求系统能够快速地响应用户的请求，系统能够高效地运行，系统需要尽可能的压缩CPU的空闲时间，让CPU更多地进行运转。所以，它就需要在某个system call暂时无法完成的情况下，将它挂起并转向另外一个system call；当该system call的执行条件满足的时候再将它重启；另外，kernel还需要处理无法预测何时会出现的各种interrupt和exception，一旦出现，则需要转去执行相应的interrupt handler，当这个interrupt handler执行完成后，再重启之前被中断的流程（是否会重启其实是一个比较复杂的问题，后面会对此进行专门分析）。这种能力就是chapter 1.6.3. Reentrant Kernels所述的***reentrant***。显然这种设计能够最大程度地保证系统的高效。

## Kernel control path

为了便于描述reentrant kernel的实现思路，在chapter 1.6.3. Reentrant Kernels中作者提出了*kernel control path*的概念，它表示了kernel所有的可能的activity，在[Linux-OS-kernel-is-event-driven](./Linux-OS-kernel-is-event-driven.md)中我们已经总结了，kernel的activity可能有如下几种情况触发：

- system call
- interrupt and exception(在Chapter 4. Interrupts and Exceptions区分这两者)

也就是说：

当process向kernel请求一个system call，此时kernel中就执行此system call，使用*kernel control path*概念来进行理解的话，则是kernel创建了一个执行这个system call的kernel control path；

当产生interrupt或exception，此时kernel转去执行它们对应的handler，使用*kernel control path*概念来进行理解的话，可以认为kernel创建了一个执行这个handler的kernel control path；

为什么要使用*kernel control path*概念来进行描述呢？因为我们知道，operating system的kernel的执行情况是非常复杂的，它需要同时处理非常多的事情，比如process请求的system call，在此过程中是会伴随中随时可能发生的interrupt和exception的。前面我们已经铺垫了，kernel为了保持高效，可能需要挂起正在执行的流程转去执行另外一个流程，而后在重启之前挂起的流程。此处所谓的流程，我们使用更加专业的术语就是kernel control path。显然与function相比，kernel control path蕴含着更加丰富的，更加符合kernel调度情况的内涵，比如它能够表示kernel的suspend（挂起），resume（重启），能够表示多个control path的interleave（交错运行）。这种通过创造新的概念来使表述更加便利的做法是在各种学科非常普遍的。



这种设计也不可避免地导致系统的复杂，正如在chapter 1.6.3. Reentrant Kernels后面所述的， 系统是在多个*kernel control path*中交错运行的。这种设计会派生出一系列的问题，比如将在1.6.5. Synchronization and Critical Regions中介绍的race condition，所以它对kernel的实现提出了更高的要求。当然可以预期的是，系统是在这样的交错中不断向前进的。

如何来实现reentrant kernel呢？这是一个需要系统地进行设计才能够解决的问题，下面总结了和这个问题相关的一些章节：

- 1.6.4. Process Address Space

  Kernel control path refers to its own private kernel stack.

- 1.6.5. Synchronization and Critical Regions

  描述了kernel control path的Synchronization



## See also

[Kernel Control Path Definition](http://www.linfo.org/kernel_control_path.html)



