# Terminal



## stackexchange [What is the exact difference between a 'terminal', a 'shell', a 'tty' and a 'console'?](https://unix.stackexchange.com/questions/4126/what-is-the-exact-difference-between-a-terminal-a-shell-a-tty-and-a-con)

I think these terms almost refer to the same thing, when used loosely:

- terminal
- shell
- tty
- console

What exactly does each of these terms refer to?



### [A](https://unix.stackexchange.com/a/4132)

A **terminal** is at the end of an electric wire, a shell is the home of a turtle, tty is a strange abbreviation and a console is a kind of cabinet.

Well, etymologically speaking, anyway.

In unix terminology, the short answer is that

- terminal = tty = text input/output environment
- console = physical terminal
- shell = command line interpreter



## What is terminal

理解chapter9.2 Terminal Logins的一个关键是知道what is terminal；在chapter 9.2中有一段话点到了关键所在：

> A host had a fixed number of these terminal devices, so there was a known upper limit on the number of simultaneous logins.



显然，标题中的***terminal***的含义是terminal device，即终端设备；显然此设备就如同computer中的很多其他设备如keyboard一般；在文章[The TTY demystified](http://www.linusakesson.net/programming/tty/index.php)对此有非常好的解释；

一个直观的理解就是：每次我们使用我们的笔记本电脑，开机后屏幕中都能够显示登录界面，我们在此登录界面中输入用户名很密码；此即terminal login；Unix中的terminal login和此是相同的；

### terminal 和 shell之间的关系？

shell将它的标准输入和标准输出都连到terminal；



## TODO

在阅读APUE CH9 进程关系章节的时候，产生了如下问题：

1、`/etc/ttys` 设备配置文件何在？

2、`gettty`的功能是什么？

3、在登录的过程中，何时调用`setsid`来创建一个新的会话？

4、通过**串行终端**登录系统和通过**网络**登录系统之间的差异

5、网络登录的优势：一个系统可以同时允许多个用户登录



在[linenoise](https://github.com/antirez/linenoise)的文档时，其中有关于tty的描述。



