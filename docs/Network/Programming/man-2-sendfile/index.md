# Send file

一、典型的zero copy

## developer.51cto [高性能开发的“十大武器”，爱了爱了！# I/O优化：零拷贝技术](https://developer.51cto.com/art/202011/630654.htm) 

> 在阅读 developer.51cto [高性能开发的“十大武器”，爱了爱了！# I/O优化：零拷贝技术](https://developer.51cto.com/art/202011/630654.htm) 时，其中介绍了 [man 2 sendfile](https://man7.org/linux/man-pages/man2/sendfile.2.html) :

**I/O 优化：零拷贝技术**

上面的工作线程，从磁盘读文件、再通过网络发送数据，数据从磁盘到网络，兜兜转转需要拷贝四次，其中 CPU 亲自搬运都需要两次。

[![img](https://s4.51cto.com/oss/202011/03/a8d13bf4dd8f6c2438cb2038af3c6260.jpg)](https://s4.51cto.com/oss/202011/03/a8d13bf4dd8f6c2438cb2038af3c6260.jpg)

零拷贝技术，解放 CPU，文件数据直接从内核发送出去，无需再拷贝到应用程序缓冲区，白白浪费资源。

[![img](https://s5.51cto.com/oss/202011/03/3108cb6ce718e71b16181ba4e203000c.jpg)](https://s5.51cto.com/oss/202011/03/3108cb6ce718e71b16181ba4e203000c.jpg)

Linux API：

```C
ssize_t sendfile(   int out_fd,    int in_fd,    off_t *offset,    size_t count   ); 
```

函数名字已经把函数的功能解释的很明显了：发送文件。指定要发送的文件描述符和网络套接字描述符，一个函数搞定!





## [man 2 sendfile(2)](https://man7.org/linux/man-pages/man2/sendfile.2.html) 

`sendfile()` copies data between one file descriptor and another. Because this copying is done within the **kernel**, `sendfile()` is more efficient than the combination of [`read(2)`](https://man7.org/linux/man-pages/man2/read.2.html) and [`write(2)`](https://man7.org/linux/man-pages/man2/write.2.html) , which would require transferring data to and from **user space**.

> NOTE:上面章节已经详细介绍了这样做的原因。