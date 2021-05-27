# 关于本章

我们已经知道了一个process可以占有的resource，由于linux OS是multitasking的，所以OS中同时运行着非常多的process，OS需要能够对每个process的resource进行**控制**，一种最最常见的控制方式就是进行limit。limit包含了对process所能够占用的resource进行限制、对process能够执行的operation进行限制，linux中使用[capabilities](http://man7.org/linux/man-pages/man7/capabilities.7.html)来描述process能够执行的操作，显然对process能够执行的operation的限制是通过限制[capabilities](http://man7.org/linux/man-pages/man7/capabilities.7.html) 来实现的。

由于linux是multi-user system，好包括对user进行限制。



本章讨论如何对process的resource进行限制，主要包含：

- 提供系统配置文件进行显式
- 通过system call进行限制

