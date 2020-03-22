# Memory management

本章主要描述现代Linux OS kernel的Memory management，而非process的memory management，维基百科[Memory management](https://en.wikipedia.org/wiki/Memory_management)没有将两者区分开来，因为这两者是有着密切关联的，它主要讨论的是process的memory management，所以本章不引用这篇文章，但是维基百科对memory management的相关的内容总结还是非常好的。OS kernel的memory management技术层出不穷，本章所关注的是现代OS普遍使用的[Paged virtual memory](https://en.wikipedia.org/wiki/Virtual_memory#Paged_virtual_memory)技术（[Memory segmentation](https://en.wikipedia.org/wiki/Memory_segmentation)被视为legacy 了）。

