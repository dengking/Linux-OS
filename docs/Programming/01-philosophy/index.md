我们已经知道了[linux kernel](https://en.wikipedia.org/wiki/Linux_kernel)所采用的架构是[monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)，也就是linux kernel掌管着这个系统，application提供调用system call来获得系统服务。按照linux的管理，system call所返回的叫做descriptor，在Windows系统中一般叫做handler。

# 20200128

使用《Understanding.The.Linux.kernel.3rd.Edition》1.6. An Overview of Unix Kernels中的内容作为入场是非常好的。