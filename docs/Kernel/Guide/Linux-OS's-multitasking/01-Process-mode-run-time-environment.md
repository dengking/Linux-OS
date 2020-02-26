# Process mode: run time environment

本文的内容基于：

- [上一篇](./01-Process-model.md)

- 龙书 [Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)
- 维基百科ABI

本文将对process的run-time进行分析，以对process model进行更加深入的分析。

本文的标题是参考自龙书 [Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)，本文的内容主要是基于龙书 [Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)的内容，在它的基础上进行了扩充。龙书正如其名（原文原名），它所述的是原理，它所讲述的是[概念模型](https://dengking.github.io/Post/Abstraction/Abstraction-and-model/)（是一个简化的模型，没有考虑multi-thread等），实际的实现肯定是基于该概念模型的，需要考虑的很多其他元素，如：

- multi-thread
- ......（TODO:还要一些其他的因素）

本文所扩充的是：

- 一些实现相关的细节，如ABI等
- 添加multi-thread相关的内容

总的来说，本文的目标是对process的run-time进行分析，构建起更加完整的process model。

## Thread run model:  function as user-defined action

在上一篇中，我们已经知道了：thread是OS kernel调度单位（即线程的执行可能被[preempt](https://en.wikipedia.org/wiki/Pre-emptive_multitasking)），即每个thread都能够独立执行；

在文章[Unit](https://dengking.github.io/Post/Unit)中，通过分析我们已经知道了thread的unit of user-defined **action**是function（也就是我们平时所说的线程执行函数）。

那thread是如何运行的呢？这就是本节所要进行讨论的。

在龙书的chapter [7.2 Stack Allocation of Space](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/7.2-Stack-Allocation-of-Space/)中有对此的描述：

> Languages that use procedures, functions, or methods as **units of user-defined actions** manage at least part of their **run-time memory** as a **stack**. Each time a procedure is called, space for its local variables is pushed onto a stack, and when the procedure terminates, that space is popped off the stack. As we shall see, this arrangement not only allows space to be shared by procedure calls whose durations do not overlap in time, but it allows us to compile code for a procedure in such a way that the relative addresses of its nonlocal variables are always the same, regardless of the sequence of procedure calls.

上面这段话中的stack，所指为call stack（在后面会对此进行展开）。

综合上面的内容：“thread的unit of user-defined **action**是function，thread是OS kernel调度单位”，让我们站在OS kernel的设计者的角色来思考如何实现这种设计？显然，OS kernel需要为每个thread都提供一套“设施”和提供一种“机制”来实现此，下面对此进行分析：

### “thread的unit of user-defined **action**是function”

要求OS至少要为thread配备function的执行所需要的"基础设施"，诸如：

- [Call stack](https://en.wikipedia.org/wiki/Call_stack)

每个thread都有一个自己独立的call stack，function的运行都是发生在call stack上，每次调用function，则入栈， 函数运行结束，则出栈，这就是thread的运行模型。

Call stack 又称为 control stack，所以它也体现了它与**program counter**，**flow of control** 之间的关系。

### “thread是OS kernel调度单位"

OS中的所有的thread共享CPU，OS kernel scheduler能够suspend、restart一个thread，在suspend一个thread之前需要保存thread运行的context，在restart一个thread的时候，需要恢复之前保存的context。

context的内容如下：

- [Program counter](https://en.wikipedia.org/wiki/Program_counter)
- [Stack pointer](https://en.wikipedia.org/wiki/Stack_pointer)

这就是“调度机制”中非常重要的context switch步骤。



每个thread都需要有自己的独立的一份这样的“配套设施”，thread的[thread control block](https://en.wikipedia.org/wiki/Thread_control_block)需要保存这些内容。

> Function（包括成员函数）是很多现代programming language都会提供的一个概念（参见文章[Abstraction](https://dengking.github.io/Post/Abstraction/Abstraction/)），比如`C++`、python，对于SQL这种语言是不存在的。



### call stack

前面我们已经分析了，每个thread都配备了自己的call stack来作为function运行场所，由此就引出了一些列的问题：函数传参如何实现等等，由此就引出了calling convention。



在进入函数之前，如何得知要申请多少栈空间？应该不是提前一次性申请该函数所需要的所有的栈空间，而是运行到该指令的时候，才在栈上分配空间。这让我想到了stored-program思想。



TODO 此段对call stack相关的ABI进行描述，由此引出控制流、传参、等等一系列问题。



关于函数调用，下面内容是需要进行补充的：

- [Entry point](https://en.wikipedia.org/wiki/Entry_point)
- [Function prologue](https://en.wikipedia.org/wiki/Function_prologue)
- [Housekeeping (computing)](https://en.wikipedia.org/wiki/Housekeeping_(computing))
- [Subroutine](https://en.wikipedia.org/wiki/Subroutine)



## Linux OS process model的实现

之前我一直有一个疑问就是：一个process的所有的thread都共享该process的address space，而每个thread有一个自己的[call stack](https://en.wikipedia.org/wiki/Call_stack)，并且call stack是向下生长的，当时我就非常疑惑，这要如何实现呀？今天在阅读[Call stack](https://en.wikipedia.org/wiki/Call_stack)、[Stack register](https://en.wikipedia.org/wiki/Stack_register)的时候，我有了如下的认知：

- 函数调用所使用的是JMP指令
- x86有segment register，这样就可以指定call stack
- 其实call stack就是一片内存区域而已，只要指定一片内存区域作为call stack，就可以使用calling convention来实现函数调用了。实现函数调用、执行的指令是与这片内存区域在何处无关的，所以用户是可以指定任意的、合法的内存区域来作为call stack的。

所以我就去看了[pthread_create](https://linux.die.net/man/3/pthread_create)的文档，其中是有这样的描述的：

> On Linux/x86-32, the default stack size for a new thread is 2 megabytes. Under the NPTL threading implementation, if the **RLIMIT_STACK** soft resource limit *at the time the program started* has any value other than "unlimited", then it determines the default stack size of new threads. Using **[pthread_attr_setstacksize](https://linux.die.net/man/3/pthread_attr_setstacksize)**(3), the stack size attribute can be explicitly set in the *attr* argument used to create a thread, in order to obtain a stack size other than the default.

即新创建的thread的默认的call stack的大小默认是2M，这说明是可以由用户了来指定新创建的thread的call stack的，我们知道，[pthread_create](https://linux.die.net/man/3/pthread_create)最终是通过调用[clone(2)](https://linux.die.net/man/2/clone)，该函数的第二个入参就是由用户来指定该lightweight process的call stack的。

看到了上面的描述， 其实我又想到了一个问题：一个函数，如果声明的自动变量大小超过了call stack的大小，会发生什么？关于这个问题，参见：

https://www.cnblogs.com/zmlctt/p/3987181.html

https://blog.csdn.net/zDavid_2018/article/details/89255630

维基百科的[Stack overflow](https://en.wikipedia.org/wiki/Stack_overflow)总结的非常好。

总的来说，龙书的chapter 7总结的是非常好的。

## Process run model

有了前面的thread run model，那么process的run model就相对比较好分析了。显然一个process有多个process组成，多个thread独立进行运行，共享process的resource。





