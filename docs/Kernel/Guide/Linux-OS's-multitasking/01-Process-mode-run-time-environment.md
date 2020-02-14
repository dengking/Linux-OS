# Process model

本文处于草稿状态。本文描述process的运行模型。

编写思路：从进程的运行形态作为切入点：

目前的所有的hight level programming language都将函数作为程序中user-defined action的单位（在hardware层，显然user-defined action的单位是instruction），这可以作为程序的运行模型（对于该运行模型是还可以进一步修正的，它的最小粒度的user-defined action其实是语句，但是这种运行模型是更加符合call stack的）。

为了实现这个运行模型，使用的结构是stack，call stack。由此就引出了一些列的问题：函数传参如何实现等等，由此就引出了calling convention。

其实我的这个描述思路是和龙书的7.2 Stack Allocation of Space的描述思路类似的。

将所有与此相关的内容集中到这里来进行，包括：

- ABI。
- 龙书chapter 7所论述的concept model。

本章的内容是主要源自龙书的[Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)，原文内容是非常好的，为我们清晰地勾画出了process的memory、runtime的concept model。



## 需要建立统一的memory model

龙书，OS书、维基百科

逻辑与实现。

龙书正如其名，它所述的是原理，所以它所讲述的是概念模型。

stack是process活动的场所，所以它是memory management的关键所在。

call stack 又称为 control stack，所以它也体现了它与**program counter**，**flow of control** 之间的关系。

往更加宽泛来所，其实是application binary interface，因为programing language的很多东西最终都需要翻译为指令，而application binary interface则是这类场景的总体描述。


函数调用对应的是JMP指令，那声明一个`int`类型的变量对应的是什么指令呢？与此类似的一个问题是：函数调用的时候，需要分配栈空间，那这是如何实现的？

push 指令就可以实现

process在运行过程中的主要活动其实就是不断地函数调用，所以搞清楚函数调用的过程对理解process是非常重要的。龙书的chapter 7就是介绍此的非常好的内容。这些内容我觉得全部都整理到OS book中去。

### linux OS process model的实现

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

### 进程运行形态

进程完全是基于function的运行模式，它的所有活动都发生在call stack上。

在进入函数之前，如何得知要申请多少栈空间？应该不是提前一次性申请该函数所需要的所有的栈空间，而是运行到该指令的时候，才在栈上分配空间。这让我想到了stored-program思想。

关于这一点在龙书的7.2 Stack Allocation of Space中有这样的描述：

> Almost all compilers for languages that use procedures, functions, or methods as units of user-defined actions manage at least part of their run-time memory as a stack. Each time a procedure is called, space for its local variables is pushed onto a stack, and when the procedure terminates, that space is popped off the stack. 
