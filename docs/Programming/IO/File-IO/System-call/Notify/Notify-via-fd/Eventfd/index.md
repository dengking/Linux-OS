# `EVENTFD(2)` 

Linux中遵循everything is a file，因此，很多event都可以以`fd`(file descriptor)的方式来进行通知。

在阅读[folly-io-async: An object-oriented wrapper around libevent](https://github.com/facebook/folly/blob/master/folly/io/async/README.md)时，其中有关于`eventfd`的介绍，引发了我对它的学习。





## stackoverflow [Writing to eventfd from kernel module](https://stackoverflow.com/questions/13607730/writing-to-eventfd-from-kernel-module)

