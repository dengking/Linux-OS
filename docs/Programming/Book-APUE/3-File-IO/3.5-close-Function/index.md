# 3.5 close Function

> APUE中，对本函数的解释是非常浅陋的，根本就不够深入；要想深入地理解`close`函数调用，还需要从the data structures used by the kernel for all I/O的角度来入手，这部分内容在APUE的3.10 File Sharing中进行了介绍；
>
> 下面的输入剖析是结合the data structures used by the kernel for all I/O和[close(2) - Linux man page](https://linux.die.net/man/2/close) ，其中的内容都是源于[close(2) - Linux man page](https://linux.die.net/man/2/close)  ，我在此基础上添加了注解；



