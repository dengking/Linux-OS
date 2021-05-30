# Asynchronous I/O

参见: 

1、ibm [Boost application performance using asynchronous I/O](https://www.ibm.com/developerworks/linux/library/l-async/)

## wikipedia [Asynchronous I/O](https://en.wikipedia.org/wiki/Asynchronous_I/O)



|      |  Blocking   |        Non-blocking         |    Asynchronous     |
| :--: | :---------: | :-------------------------: | :-----------------: |
| API  | write, read | write, read + poll / select | aio_write, aio_read |



> NOTE:
>
> 维基百科[Asynchronous I/O](https://en.wikipedia.org/wiki/Asynchronous_I/O)的[Forms](https://en.wikipedia.org/wiki/Asynchronous_I/O#Forms)章节对IO form的分类和本节前面所描述的POSIX 的IO 分类是一致的。
>
> 维基百科[Asynchronous I/O](https://en.wikipedia.org/wiki/Asynchronous_I/O)的[Examples](https://en.wikipedia.org/wiki/Asynchronous_I/O#Examples)章节给出的例子值的一读。
>
> 

