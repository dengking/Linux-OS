# Control path

> NOTE: 使用task model来进行描述

Control path这个概念是我由kernel control path启发而创建的，Control path表示OS中所有可能的活动/执行流程，之所以创建这个概念，是因为它可以方便我们来统一地、概括地描述一些问题（一个抽象过程）。与它比较接近的一个概念是[Control flow](https://en.wikipedia.org/wiki/Control_flow)。

Linux OS中有如下control path：

- kernel control path
- kernel thread
- task（process/thread，现代OS需要支持[multitasking](./00-Multitask.md)）

在本书的有些章节会使用“execution context”、“execution flow”等词语，其实它们和本文所定义的control path表示的是相同的意思。

Control path的典型特征是“reentrant”，即它的执行可能会被suspend而后被resume。下面枚举了两个例子来说明“reentrant”的含义：

- 一旦发生了hardware interrupt，OS kernel会立即去响应，从而interrupt（suspend）当前执行的kernel control path，转去执行新的kernel control path，即原kernel control path会被interrupted。

- task是现代OS为支持[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)而创建的，它由[scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing))进行调度执行的，目前linux采取的调度策略是[Preemptive multitasking](https://en.wikipedia.org/wiki/Preemption_(computing))，这种策略的本质是：

  > It is normally carried out by a [privileged](https://en.wikipedia.org/wiki/Protection_ring) task or part of the system known as a preemptive [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)), which has the power to **preempt**, or interrupt, and later resume, other tasks in the system.

  即它可能会preempt（suspend）正在执行的task，然后转去执行另外一个task。

## 如何实现Reentrant？

显然这是OS为了高效，让多个control path interleave（交错运行），为了实现[Reentrancy](https://en.wikipedia.org/wiki/Reentrancy_(computing)) ，每个control path都要有自己private的context、address space（这其实是一个separation机制），它能够保证一个control path在被suspend后，过后能够被resume。

显然context包括每个control path的private数据，如下：

hardware context：

- [Program counter](https://en.wikipedia.org/wiki/Program_counter)

每当一个正在执行的control path要被suspend之前，需要将它的context置于它的当前执行它的process（linux 的lightweight process，而不是标准的process）的[call stack](https://en.wikipedia.org/wiki/Call_stack)（可能是Kernel Mode process stack，也可能是User Mode process stack），在它被restart的时候，再将保存在[call stack](https://en.wikipedia.org/wiki/Call_stack)上的context恢复，这就所谓的context switch，后面会进行专门介绍。

关于这一点，证据来源于：

- chapter 4.1. The Role of Interrupt Signals
- 龙书7.2.2 Activation Records









### Context switch

需要注意的是，本节所述的context switch是广义的，而不是[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)中专指task（process/thread）的[context switch](https://en.wikipedia.org/wiki/Context_switch)。



发生context switch的场景：

#### Scheduler触发Process Switch

3.3. Process Switch

kernel substitutes one process for another process

#### Interrupt Signals触发Switch

4.1. The Role of Interrupt Signals

> the code executed by an interrupt or by an exception handler is not a process. Rather, it is a kernel control path that runs at the expense of the same process that was running when the interrupt occurred



> As a kernel control path, the interrupt handler is lighter than a process (it has less context and requires less time to set up or tear down).

4.3. Nested Execution of Exception and Interrupt Handlers



#### 思考：context switch的成本

不同的control path进行context switch的成本是不同的， 软件工程师经常听说的就是thread的context switch比process的context switch要快，就是说的这个道理。





### Control path context switch VS function call

control path的context switch和function call中将[**return state**](https://en.wikipedia.org/wiki/Call_stack#Functions_of_the_call_stack)保存到[call stack](https://en.wikipedia.org/wiki/Call_stack)待被调函数返回后再进行恢复的做法是非常类似的。



## How kernel control path execute?

**kernel control path**（注意不是control path）的执行细节比较复杂，后续需要进行补充。

Kernel control path和process之间的关联是本书中会一直强调的内容，需要进行一下总结，其中最最典型的就是"kernel control path runs on behalf of process"。为了今后便于快速地检索到这些内容，现将本书中所有的与此相关内容的位置全部都整理到这里：

- chapter 1.6.3. Reentrant Kernels

  本节的后半部分对kernel control path的一些可能情况进行了枚举，并描述了这些情况下，kernel control path和process之间的关系

- Chapter 4. Interrupts and Exceptions

  主要描述了Interrupts and Exceptions触发的kernel control path的执行情况。并且其中还对比了interrupt 触发的kernel control path和system call触发的kernel control path之间的差异等内容。



***SUMMARY*** : 执行system call也是kernel control path，那么是否system call的执行步骤和上面描述的类似？在这篇文章中，有如下的提问：[Is the Unix process scheduler itself a process?](https://unix.stackexchange.com/questions/155766/is-the-unix-process-scheduler-itself-a-process)

> Is the **Unix process scheduler** itself a process, or does it piggyback on other processes in the same way a **system call** does (running kernel code in the user process with the **kernel bit** set)?

按照上面这一段的描述来看，interrupt的执行是piggyback on processes ；按照1.6.3. Reentrant Kernels中所定义的kernel control path，它支持A kernel control path denotes the sequence of instructions executed by the kernel to handle a system call, an exception, or an interrupt.显然，system call和exception handler都是kernel control path；上面所描述的exception handler的执行方式是否也适用于system call；

Unix进程调度程序本身是一个进程，还是以与系统调用相同的方式搭载在其他进程上（在内核位设置的用户进程中运行内核代码）？



4.3. Nested Execution of Exception and Interrupt Handlers:

> the first instructions of the corresponding kernel control path are those that save the contents of the CPU registers in the Kernel Mode stack, while the last are those that restore the contents of the registers.

## 总结

通过control path模型我们可以看到，OS在运行和控制它们的时候会面临中类似的问题。

