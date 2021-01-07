# Process resource model

process可能占有的资源有：

| resource       | 参考内容                                                     |      |
| -------------- | ------------------------------------------------------------ | ---- |
| 控制终端       | [man 4 tty](http://man7.org/linux/man-pages/man4/tty.4.html) |      |
| file           |                                                              |      |
| signal handler |                                                              |      |
| memory         |                                                              |      |
| 文件系统       |                                                              |      |

在[3.2. Process Descriptor](../../Book-Understanding-the-Linux-Kernel/Chapter-3-Processes/3.2-Process-Descriptor.md)中也有对此的描述。

## Memory

memory这种resource是非常典型的，参见[Process-memory-model](./Process-memory-model/Process-memory-model.md)。



## Process resource management

process能够占有如此之多的resource，所以对resource的management是一个非常重要的内容，由于这部分内容和 programming language密切相关，且不同的programming language可能采取的方式是不同的，所以将这部分内容放到了工程[programming-language](https://dengking.github.io/programming-language/)中。



## 相关问题

process在肯定会占用一定的resource的，最最典型的就是file。关于此可以衍生出一些列的问题:

- resource的继承问题

- resource的竞争

- resource的共享

在工程Parallel-computing的`Concurrent-computing\Concurrent-server`章节中涉及这个问题。