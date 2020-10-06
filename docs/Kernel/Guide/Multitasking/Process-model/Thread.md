# Thread

## 维基百科的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))



## Thoughts

不同的OS有着不同的实现，但是它们肯定都会符合标准。

按照计算机科学的发展流程来看，应该是首先有计算机理论学家提出了这些概念/标准，然后操作系统厂商再实现这些概念/标准。所以从标准的出现到操作系统厂商实现这些标准，两者之间是有一个时间间隔的。不同厂商的对同一概念/标准的实现方式也会有所不同，并且它们的实现方式也会不断地演进。所以在开始进入到本书的内容之前，我们需要首先建立如下观念：

- 标准与实现之间的关系
- 以发展的眼光来看待软件的演进

下面以operating system如何来实现[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))为例来进行说明，目前存在着两种实现方式：

- user level thread，常称为user thread
- kernel level thread

两者之间的差异可以参见如下文章：

- https://www.geeksforgeeks.org/difference-between-user-level-thread-and-kernel-level-thread/
- [What is a user thread and a kernel thread?](https://superuser.com/questions/455316/what-is-a-user-thread-and-a-kernel-thread)

显然，对于标准所提出的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))，可以有多种实现方式。关于此，维基百科的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))有着非常好的总结。