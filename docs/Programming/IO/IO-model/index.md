# 关于本章

本章总结Unix-like OS中的I/O model，建立起I/O的big picture。

参考文章: 

1、`ibm-Boost-application-performance-using-asynchronous-IO`

2、`UNP-6.1-IO-Multiplexing`

3、wikipedia [Asynchronous I/O](https://en.wikipedia.org/wiki/Asynchronous_I/O)

## Summary

从上面三篇文章:

1) UNP 6.1 I/O Multiplexing: The `select` and `poll` Functions[¶](https://notes.shichao.io/unp/ch6/#chapter-6-io-multiplexing-the-select-and-poll-functions)

2) ibm [Boost application performance using asynchronous I/O](https://www.ibm.com/developerworks/linux/library/l-async/)

3) wikipedia [Asynchronous I/O](https://en.wikipedia.org/wiki/Asynchronous_I/O)

可以看出，它们对IO model的分类是不同的，需要注意的是，它们的分类都没有错误，对blocking、non-blocking 和 sync、async 的用法也没有错误，它们都是在IO的某个角度来进行描述、分类的。