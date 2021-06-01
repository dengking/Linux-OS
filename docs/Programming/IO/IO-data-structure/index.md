# Linux IO data structure



APUE3.10 File Sharing

we’ll examine **data structures** used by the kernel for all I/O, The following description is conceptual; it may or may not match a particular implementation.

The kernel uses three data structures to represent an open file, and the relationships among them determine the effect one process has on another with regard to file sharing.

一、file descriptor table、file table、inode table



file descriptor attribute: 

File Descriptor Flags

file table entry: 

File Status Flags







## 三级机构

本节内容参考自:

### APUE3.10 File Sharing

> NOTE: 
> 1、原文的内容非常好

### wikipedia [File descriptor](https://en.wikipedia.org/wiki/File_descriptor) 

In the traditional implementation of Unix, **file descriptors** index into a per-process **file descriptor table** maintained by the kernel, that in turn indexes into a system-wide table of files opened by all processes, called the **file table**. This table records the *mode* with which the file (or other resource) has been opened: for reading, writing, appending, and possibly other modes. It also indexes into a third table called the [inode table](https://en.wikipedia.org/wiki/Inode) that describes the actual underlying files. 



### wikipedia [Process control block](https://en.wikipedia.org/wiki/Process_control_block)



## 可能的组合情况

1、三级结构存在着多种可能的组合情况，下面罗列了典型的组合

2、下面的图是参考"APUE3.10 File Sharing"绘制的



#### 一个进程打开多个不同的文件

```
Process Control Block          
|                              
|  File descriptor Table       File Table Entry         V-Node
|  | 1-------------------------|------------------------|
|  | 2\                        |                        |
|  | 3 \                       
|  |    \                      File Table Entry         V-Node
|        ----------------------|------------------------|
                               |                        |
```

file descriptor 1 和 file descriptor 2分别对应不同的file



#### 一个进程以不同的**模式**打开同一个文件多次

```
Process Control Block          
|                              
|  File descriptor Table       File Table Entry         V-Node
|  | 1-------------------------|------------------------|
|  | 2\                        |                    /---|
|  | 3 \                                           /
|  |    \                      File Table Entry   /      
|        ----------------------|-----------------/
                               |                     
```





#### 不同进程打开同一个文件

```
Process Control Block          
|                              
|  File descriptor Table       File Table Entry         V-Node
|  | 1-------------------------|------------------------|
|  |                           |                --------|
|  |                                            |
|  |                                            |
|                                               |
                                                |
                                                |
Process Control Block                           |
|                                               |
|  File descriptor Table       File Table Entry |
|  |                           |                |
|  | 2-------------------------|-----------------                       
|  | 
|  | 
|    
     
```

#### 父子进程的每一个打开的文件描述符共享同一个文件表项

```
Process Control Block          
|                              
|  File descriptor Table       File Table Entry         V-Node
|  | 1-------------------------|------------------------|
|  |                      -----|                    
|  |                      |
|  |                      |
|                         |
                          |
                          |
Process Control Block     |  
|                         |  
|  File descriptor Table  |     
|  | 1---------------------
|  |                           
|  | 
|  | 
|    
```

#### 进程执行`dup`系列函数来clone a file descriptor

```
Process Control Block          
|                              
|  File descriptor Table       File Table Entry         V-Node
|  | 1-------------------------|------------------------|
|  |    /----------------------|------------------------|
|  |   /                                        
|  | 4/                                         
|                                                                                           
     
```

上述是执行了`dup2(1,4)`后的结构；可以看到，其实`dup`系列函数类似于浅拷贝；
