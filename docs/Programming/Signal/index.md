# Signal

内容：

## APUE 

### Chapter 10 Signals

signal是什么？

10.2 Signal Concepts：Signals are software interrupts. 

信号的来源？

10.2 Signal Concepts

这一节对信号来源总结的非常好。可以看到signal的来源是非常广泛的。在阅读[Understanding.The.Linux.kernel.3rd.Edition](https://www.oreilly.com/library/view/understanding-the-linux/0596005652/)的Chapter 4. Interrupts and Exceptions时，我思考了如下问题：Unix signal都对应的是exceptions？显然不是的，比如`SIGINT`就不是源自于exception。在本章中对此进行了总结，所以我们应该清楚，exception是信号的众多来源中的一种。



## [Understanding.The.Linux.kernel.3rd.Edition](https://www.oreilly.com/library/view/understanding-the-linux/0596005652/)

### Chapter 4. Interrupts and Exceptions



### Chapter 11. Signals



## [SIGNAL(7)](http://man7.org/linux/man-pages/man7/signal.7.html)





## csdn [linux下 signal信号机制的透彻分析与各种实例讲解](https://blog.csdn.net/u012183924/article/details/53888972/)

这篇文章讲解signal还是比较详细的，可以作为guide。