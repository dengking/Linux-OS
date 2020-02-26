# 关于本章

我们已经知道了[linux kernel](https://en.wikipedia.org/wiki/Linux_kernel)所采用的架构是[monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)，也就是linux kernel掌管着这个系统，application通过调用system call来获得系统服务。按照linux的惯例，system call所返回的叫做descriptor，在Windows系统中一般叫做handler。


