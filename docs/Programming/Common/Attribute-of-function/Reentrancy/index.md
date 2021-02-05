# 关于本章

本章讨论reentrancy。



## TODO

microchip [Sharing global variables with multiple Interrupt Service Routines](https://www.microchip.com/forums/m921817.aspx)



## Drafts

1

典型的例子是：函数在执行过程中，以不可预知的方式被interrupt，然后改函数又再次被执行。

2

Reentrant：

OS book的1.6.3. Reentrant Kernels中的“Reentrant”和Reentrant function中的Reentrant的含义是不同的

关于Reentrant function，维基百科的介绍是非常好的

3

https://www.gnu.org/software/libc/manual/html_node/Nonreentrancy.html

https://stackoverflow.com/questions/3941271/why-are-malloc-and-printf-said-as-non-reentrant

https://stackoverflow.com/questions/855763/is-malloc-thread-safe

4

在 https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf 中，提及了

> Unfortunately, this implementation is not reliable in a multithreaded environment. Suppose that Thread A enters the instance function, executes through Line 14, and is then suspended. At the point where it is suspended, it has just determined that pInstance is null, i.e., that no Singleton object has yet been created