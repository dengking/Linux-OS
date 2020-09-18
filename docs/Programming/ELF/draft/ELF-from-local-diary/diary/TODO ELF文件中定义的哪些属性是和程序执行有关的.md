# ELF Header的e_entry成员

对于可执行文件和动态链接库，它们的e_entry是有值的，我看ELF文档中对于这个字段的解释如下：

e_entry

This member gives the **virtual address** to which the system first transfers control,thus starting the process. If the file has no associated entry point, this member holds zero.

看我这段话我的理解是，当我们编译生成一个可执行程序后，如果执行这个可执行程序，这个地址就是进程开始的虚地址，也就是说，一个进程的开始地址是在编译完成后就已经确定了，并且一直不变。那么操作系统中有如此之多的可执行程序，他们的开始地址都是提前确定的，难道不会冲突吗？并且我们编译生成的可执行程序是可以在不同的机器上进行执行的，那么在在另外一台机器上，就有可能冲突了。

#Section Header的sh_addr成员

在section的结构中也有类似的成员变量：sh_addr，这个变量给出了这个section在内存中的位置。关于这个成员，文档的解释如下：

sh_addr

If the section will appear in the memory image of a process, this member gives the address at which the section's first byte should reside. Otherwise,the member contains 0.

#Section Header的sh_flags成员

![section header flag](D:\mydoc\others\ELF\diary\section header flag.png)

显然这个字段的值影响了在该section被加载到内存中后，进程开始执行时，对这个section的操作。



参考[ELF文件的加载和动态链接过程](http://jzhihui.iteye.com/blog/1447570)

