# 关于本章

我们可以使用类比的方法来理解linux namespace，即从其他使用了namespace的领域来类比理解linux namespace，比如`c++`中的`namespace`。wikipedia [Namespace](https://en.wikipedia.org/wiki/Namespace)对计算机科学中的`namespace`进行了总结，这篇文章比较好。显然，无论在哪个层级（programming language、operating system），使用namespace的目的是：

1、separation

2、以Hierarchy的结构来组织数据

在理解了使用namespace的目的后，推荐阅读toptal [Separation Anxiety: A Tutorial for Isolating Your System with Linux Namespaces](https://www.toptal.com/linux/separation-anxiety-isolating-your-system-with-linux-namespaces)，这篇文章比较输入浅出，阅读完成后，基本上能够知道linux namespace所解决的实际问题和它的价值了。

掌握了这些后，再去阅读man中对它的解释就会非常容易了。



## wikipedia [Linux namespaces](https://en.wikipedia.org/wiki/Linux_namespaces)

