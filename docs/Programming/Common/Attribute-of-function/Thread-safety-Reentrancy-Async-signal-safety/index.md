# Reentrant and async-signal safe and thread-safe



## 三者相同点

Thread-safety、Reentrancy、Async-signal-safety，都是基于一个相同的场景: 

同一个函数被重复执行，导致了race。

### APUE 中的 definition

有的地方，将这种情况称为"重入"，比如:

APUE 12.5 Reentrancy给出的definition如下：

> If a function is **reentrant** with respect to multiple threads, we say that it is ***thread-safe***. This doesn’t tell us, however, whether the function is reentrant with respect to signal handlers. We say that a function that is safe to be reentered from an asynchronous signal handler is ***async-signal safe***. We saw the async-signal safe functions in Figure 10.4 when we discussed reentrant functions in Section 10.6.



APUE 10.6 Reentrant Functions给出的definition如下：

> The Single UNIX Specification specifies the functions that are guaranteed to be safe to call from within a signal handler. These functions are reentrant and are called ***async-signal safe*** by the Single UNIX Specification. Besides being reentrant, they block any signals during operation if delivery of a signal might cause inconsistencies.



基于APUE中的definition，我们可以得出如下结论:

1、"If a function is **reentrant** with respect to multiple threads, we say that it is ***thread-safe***"

多个线程在相同的时刻，调用同一个函数

2、"A function that is safe to be reentered from an asynchronous signal handler is ***async-signal safe***"

调用signal handler，而中断正在执行的函数，在signal handler中调用与被中断函数相同的函数，这就是重入

但是，在很多地方，**Reentrancy**都特指 ***async-signal safe***，比如 wikipedia [Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing)) 中，因此后续为了区分，我们最好使用: Thread-safety、Async-signal-safety。



## Reentrancy VS thread safety

两者是正交的概念，描述的是不同的性质；

### 共同点

两者的深层原因有些类似，一句话来概括就是"race condition"，下面是详细的分析:

1、execution  flow会不受控制地被suspend/preempt/interrupt

2、可以使用multiple model进行分析，存在race condition: many to one

因此，从many to one来出发，结合各自可能的场景，就可以非常容易的辨明是否Reentrancy、是否thread safety。

3、两者都是reentrant，参见 `Programming\Book-APUE\APUE-Reentrant-and-async-signal-safe-and-thread-safe` 章节

### 差异点

两种本质的差异在于:

一、Reentrancy是非multitasking时代的产物，它的function不是由多个thread同时执行的，ISR是由kernel执行的；而thread safety是multitasking时代的产物，它的function是由多个thread同时执行的

> NOTE: 关于这一点，参见 wikipedia [Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing)) # Background # Reentrancy VS thread-safety 段。

二、由于两者的上述本质的差异，因此实现保护"the one"的手段也是不同的

a、mutex可以用于实现thread safety，但是无法实现Reentrancy(不能用于ISR)

b、使用thread local来将the one变为private，可以能够实现thread safety，但是无法实现Reentrancy 

具体案例参见: wikipedia [Reentrancy (computing) # Thread-safe but not reentrant](https://en.wikipedia.org/wiki/Reentrancy_(computing)#Thread-safe_but_not_reentrant)。

c、两者都可以使用atomicity来保护"the one"



在 wikipedia [Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing)) 中的几个example是非常好的。



### 素材

在下面章节中，也对这个topic进行了讨论:

1、`programming-language\docs\C++\Resource-management\Memory\Dynamic-allocation\new-operator\Thread-safety-Reentrancy`

2、`programming-language\docs\C++\Resource-management\Memory\Dynamic-allocation\malloc\Thread-safety-Reentrancy`

3、stackoverflow [Why are malloc() and printf() said as non-reentrant?](https://stackoverflow.com/questions/3941271/why-are-malloc-and-printf-said-as-non-reentrant)

这篇文章 非常好





## draft

### 不使用async-signal unsafe function

当然有些情况下的race condition是通过OS提供的各种方法是无法avoid，比如在APUE 的10.6 Reentrant Functions章节介绍的情况，这种情况下，就只有不使用这些async-signal unsafe function才能够彻底规避；

> 思考:原子操作有哪些优良性质



