# Process run model

本文的内容基于：

- [上一篇](../Process-model.md)

- 龙书 [Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)
- 维基百科ABI

本文将对process的run-time进行分析，以对process model进行更加深入的分析。

本文的标题是参考自龙书 [Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)，本文的内容主要是基于龙书 [Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)的内容，在它的基础上进行了扩充。龙书正如其名（原文原名），它所述的是原理，它所讲述的是[概念模型](https://dengking.github.io/Post/Abstraction/Abstraction-and-model/)（是一个简化的模型，没有考虑multi-thread等），实际的实现肯定是基于该概念模型的，需要考虑的很多其他元素，如：

- multi-thread
- ......（TODO:还要一些其他的因素）

本文所扩充的是：

- 一些实现相关的细节，如ABI等
- 添加multi-thread相关的内容

总的来说，本文的目标是对process的runtime进行分析，构建起更加完整的process model。

## Thread run model

在上一篇中，我们已经知道了：thread是OS kernel调度单位（线程的执行可能被[preempt](https://en.wikipedia.org/wiki/Pre-emptive_multitasking)），即每个thread都能够独立执行；在文章[Unit](https://dengking.github.io/Post/Unit)中，我们已经知道了thread的unit of user-defined **action**是**subroutine**，也就是我们平时所说的**线程执行函数**。（需要注意的是，这些都是computer science中的规定、事实，它们是无数的计算机科学家们经过精心设计而构建出来的，作为工程师，我们无需去证明为什么是这样的，我们需要的是知道这个事实，我们可以去思考这样设计的优势有哪些）

综合上面的内容：“thread的unit of user-defined **action**是subroutine，thread是OS kernel调度单位”。

那thread是如何运行的呢？在龙书的chapter [7.2 Stack Allocation of Space](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/7.2-Stack-Allocation-of-Space/)中有对此的描述：

> Languages that use procedures, functions, or methods as **units of user-defined actions** manage at least part of their **run-time memory** as a **stack**. Each time a procedure is called, space for its local variables is pushed onto a stack, and when the procedure terminates, that space is popped off the stack. As we shall see, this arrangement not only allows space to be shared by procedure calls whose durations do not overlap in time, but it allows us to compile code for a procedure in such a way that the relative addresses of its nonlocal variables are always the same, regardless of the sequence of procedure calls.

上面这段话中的stack，所指为call stack（在后面会对此进行展开）。

让我们站在OS kernel的设计者的角色来思考如何实现这种设计？显然，OS kernel需要为每个thread都提供一套“**基础设施**”和一种“**调度机制**”来实现这种设计，下面对此进行分析：

### “thread的unit of user-defined **action**是function”

要求OS至少要为thread配备function的执行所需要的"**基础设施**"，诸如：

- [Call stack](./Subroutine/Call-subroutine/Call-stack.md)

每个thread都有一个自己独立的call stack，function的运行都是发生在call stack上，每次调用function，则入栈， 函数运行结束，则出栈，这就是thread的**运行模型**。

Call stack 又称为 control stack，所以它也体现了它与**program counter**，**flow of control** 之间的关系。

### “thread是OS kernel调度单位"

OS中的所有的thread共享CPU，“**调度机制**”是由OS kernel scheduler（后面简称scheduler）来完成，scheduler能够suspend、restart一个thread，在suspend一个thread之前需要保存thread运行的**context**，在restart一个thread的时候，需要恢复之前保存的**context**，context的内容如下：

- [Program counter](https://en.wikipedia.org/wiki/Program_counter)
- [Stack pointer](https://en.wikipedia.org/wiki/Stack_pointer)
- ......

这就是“**调度机制**”中非常重要的**context switch**步骤。



每个thread都有自己的独立的一份“**基础设施**”，“**基础设施**”包括：

- thread的[thread control block](https://en.wikipedia.org/wiki/Thread_control_block)
- call stack

### Subroutine（函数）

参见[Subroutine](./Subroutine/Subroutine.md)。

### Call stack

参见[Call-stack](./Subroutine/Call-subroutine/Call-stack.md)。

### Call convention

前面我们已经分析了，每个thread都配备了自己的call stack来作为subroutine运行场所，由此就引出了一些列的问题：函数传参如何实现、在进入函数之前，如何得知要申请多少栈空间？应该不是提前一次性申请该函数所需要的所有的栈空间，而是运行到该指令的时候，才在栈上分配空间。这些内容都将在工程[programming-language](https://dengking.github.io/programming-language/)的[ABI](https://dengking.github.io/programming-language/ABI)章节的Call-convention中进行讲解。



## Process run model

有了前面的thread run model，那么process的run model就相对比较好分析了。显然一个process有多个process组成，多个thread独立进行运行，共享process的resource。





