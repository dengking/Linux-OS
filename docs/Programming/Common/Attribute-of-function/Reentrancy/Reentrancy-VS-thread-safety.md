# Reentrancy VS thread safety

两者是正交的概念，描述的是不同的性质；

## 共同点

两者的深层原因有些类似，一句话来概括就是"race condition"，下面是详细的分析:

1、execution  flow会不受控制地被suspend/preempt/interrupt

2、可以使用multiple model进行分析，存在race condition: many to one

因此，从many to one来出发，结合各自可能的场景，就可以非常容易的辨明是否Reentrancy、是否thread safety。

3、两者都是reentrant，参见 `Programming\Book-APUE\APUE-Reentrant-and-async-signal-safe-and-thread-safe` 章节

## 差异点

两种本质的差异在于:

1、Reentrancy是非multitasking时代的产物，它的function不是由多个thread同时执行的，ISR是由kernel执行的；而thread safety是multitasking时代的产物，它的function是由多个thread同时执行的

> NOTE: 关于这一点，参见 wikipedia [Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing)) # Background # Reentrancy VS thread-safety 段。

2、由于两者的上述本质的差异，因此实现保护"the one"的手段也是不同的

a、mutex可以用于实现thread safety，但是无法实现Reentrancy(不能用于ISR)

b、使用thread local来将the one变为private，可以能够实现thread safety，但是无法实现Reentrancy 

具体案例参见: wikipedia [Reentrancy (computing) # Thread-safe but not reentrant](https://en.wikipedia.org/wiki/Reentrancy_(computing)#Thread-safe_but_not_reentrant)。

c、两者都可以使用atomicity来保护"the one"



在 wikipedia [Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing)) 中的几个example是非常好的。