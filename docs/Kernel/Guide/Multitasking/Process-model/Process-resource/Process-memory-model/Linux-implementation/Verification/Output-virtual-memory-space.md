

# 输出地址空间

原文链接：https://blog.csdn.net/zhongjiekangping/article/details/6910211

```c
#include <stdio.h>   
#include <stdlib.h>   
  
int global_init_a=1;  
int global_uninit_a;  
static int static_global_init_a=1;  
static int static_global_uninit_a;  
const int const_global_a=1;  
  
int global_init_b=1;  
int global_uninit_b;  
static int static_global_init_b=1;  
static int static_global_uninit_b;  
const int const_global_b=1;  
/*上面全部为全局变量，main函数中的为局部变量*/  
int main()  
{  
    int local_init_a=1;  
    int local_uninit_a;  
    static int static_local_init_a=1;  
    static int static_local_uninit_a;  
    const int const_local_a=1;  
  
    int local_init_b=1;  
    int local_uninit_b;  
    static int static_local_init_b=1;  
    static int static_local_uninit_b;  
    const int const_local_b=1;  
  
    int * malloc_p_a;  
    malloc_p_a=malloc(sizeof(int));  
    //将上面定义的变量全部都打印出来
    printf("\n         &global_init_a=%p \t            
         global_init_a=%d\n",&global_init_a,global_init_a);   
  
    printf("       &global_uninit_a=%p \t          
        global_uninit_a=%d\n",&global_uninit_a,global_uninit_a);      
  
    printf("  &static_global_init_a=%p \t     
        static_global_init_a=%d\n",&static_global_init_a,static_global_init_a);  
      
    printf("&static_global_uninit_a=%p \t   
        static_global_uninit_a=%d\n",&static_global_uninit_a,static_global_uninit_a);  
      
    printf("        &const_global_a=%p \t           
        const_global_a=%d\n",&const_global_a,const_global_a);     
  
      
    printf("\n         &global_init_b=%p \t            
        global_init_b=%d\n",&global_init_b,global_init_b);    
  
    printf("       &global_uninit_b=%p \t          
        global_uninit_b=%d\n",&global_uninit_b,global_uninit_b);      
  
    printf("  &static_global_init_b=%p \t     
        static_global_init_b=%d\n",&static_global_init_b,static_global_init_b);  
      
    printf("&static_global_uninit_b=%p \t   
        static_global_uninit_b=%d\n",&static_global_uninit_b,static_global_uninit_b);  
      
    printf("        &const_global_b=%p \t           
        const_global_b=%d\n",&const_global_b,const_global_b);  
  
                  
  
    printf("\n          &local_init_a=%p \t            
        local_init_a=%d\n",&local_init_a,local_init_a);   
  
    printf("        &local_uninit_a=%p \t          
        local_uninit_a=%d\n",&local_uninit_a,local_uninit_a);  
      
    printf("   &static_local_init_a=%p \t     
        static_local_init_a=%d\n",&static_local_init_a,static_local_init_a);  
      
    printf(" &static_local_uninit_a=%p \t   
        static_local_uninit_a=%d\n",&static_local_uninit_a,static_local_uninit_a);    
  
    printf("         &const_local_a=%p \t           
        const_local_a=%d\n",&const_local_a,const_local_a);    
  
      
    printf("\n          &local_init_b=%p \t            
        local_init_b=%d\n",&local_init_b,local_init_b);   
  
    printf("        &local_uninit_b=%p \t          
        local_uninit_b=%d\n",&local_uninit_b,local_uninit_b);  
      
    printf("   &static_local_init_b=%p \t     
        static_local_init_b=%d\n",&static_local_init_b,static_local_init_b);  
      
    printf(" &static_local_uninit_b=%p \t   
        static_local_uninit_b=%d\n",&static_local_uninit_b,static_local_uninit_b);    
  
    printf("         &const_local_b=%p \t           
        const_local_b=%d\n",&const_local_b,const_local_b);  
  
  
    printf("             malloc_p_a=%p \t             
        *malloc_p_a=%d\n",malloc_p_a,*malloc_p_a);  
      
    return 0;  
}  
```

下面是输出结果。![img](http://hi.csdn.net/attachment/201110/22/0_1319291233G3Fq.gif)

先仔细分析一下上面的输出结果，看看能得出什么结论。貌似很难分析出来什么结果。好了我们继续往下看吧。

接下来，通过查看**proc文件系统**下的文件，看一下这个进程的**真实内存分配情况**。（我们需要在程序结束前加一个死循环，不让进程结束，以便我们进一步分析）。

​      在`return 0`前，增加 `while(1);` 语句。

重新编译后，运行程序，程序将进入死循环。

使用ps命令查看一下进程的pid。

```shell
ps -aux | grep a.out
```

查看`/proc/2699/maps`文件，这个文件显示了进程在内存空间中各个区域的分配情况。

```shell
cat  /proc/2699/maps
```

![img](http://hi.csdn.net/attachment/201110/22/0_13192938162jG2.gif)

上面红颜色标出的几个区间是我们感兴趣的区间：

- 08048000-08049000  r-xp  貌似是代码段
- 08049000-0804a000 r--p   暂时不清楚，看不出来
- 0804a000-0804b000 rw-p  貌似为数据段
- 08a7e000-08a9f000  rw-p  堆
- bff73000-bff88000     rw-p   栈  


我们把这些数据与最后一次的程序运行结果进行比较，看看有什么结论。

​                &global_init_a=0x804a018       全局初始化：数据段              global_init_a=1
​            &global_uninit_a=0x804a04c      全局未初始化：数据段          global_uninit_a=0
​     &static_global_init_a=0x804a01c      全局静态初始化：数据段      static_global_init_a=1
&static_global_uninit_a=0x804a038      全局静态未初始化：数据段     static_global_uninit_a=0
​             &const_global_a=0x80487c0     全局只读变量： 代码段        const_global_a=1
​                 &global_init_b=0x804a020       全局初始化：数据段      global_init_b=1
​            &global_uninit_b=0x804a048        全局未初始化：数据段      global_uninit_b=0
​     &static_global_init_b=0x804a024        全局静态初始化：数据段    static_global_init_b=1
&static_global_uninit_b=0x804a03c        全局静态未初始化：数据段   static_global_uninit_b=0
​            &const_global_b=0x80487c4        全局只读变量： 代码段             const_global_b=1
​                 &local_init_a=0xbff8600c          局部初始化：栈                     local_init_a=1
​             &local_uninit_a=0xbff86008         局部未初始化：栈                 local_uninit_a=134514459
​     &static_local_init_a=0x804a028         局部静态初始化：数据段      static_local_init_a=1
 &static_local_uninit_a=0x804a040        局部静态未初始化：数据段     static_local_uninit_a=0
​             &const_local_a=0xbff86004        局部只读变量：栈     const_local_a=1
​                  &local_init_b=0xbff86000        局部初始化：栈          local_init_b=1
​                &local_uninit_b=0xbff85ffc         局部未初始化：栈        local_uninit_b=-1074241512
​      &static_local_init_b=0x804a02c        局部静态初始化：数据段      static_local_init_b=1
 &static_local_uninit_b=0x804a044        局部静态未初始化：数据段      static_local_uninit_b=0
​                &const_local_b=0xbff85ff8        局部只读变量：栈        const_local_b=1

​                           p_chars=0x80487c8        字符串常量：代码段          p_chars=abcdef
​                    malloc_p_a=0x8a7e008        malloc动态分配：堆        *malloc_p_a=0

通过以上分析我们暂时可以得到的结论如下，**在进程的地址空间中**：

- **数据段**中存放：**全局变量**（初始化以及未初始化的）、**静态变量**（全局的和局部的、初始化的以及未初始化的）
- 代码段中存放：全局只读变量（const）、字符串常量
- 堆中存放：动态分配的区域
- 栈中存放：局部变量（初始化以及未初始化的，但不包含静态变量）、局部只读变量（const）

这里我们没有发现BSS段，但是我们将未初始化的数据按照地址进行排序看一下，可以发现一个规律。

&global_init_a=0x804a018       全局初始化：数据段              global_init_a=1
​    &static_global_init_a=0x804a01c      全局静态初始化：数据段      static_global_init_a=1
​                &global_init_b=0x804a020       全局初始化：数据段      global_init_b=1
​    &static_global_init_b=0x804a024        全局静态初始化：数据段    static_global_init_b=1
​       &static_local_init_a=0x804a028         局部静态初始化：数据段      static_local_init_a=1
​       &static_local_init_b=0x804a02c        局部静态初始化：数据段      static_local_init_b=1
&static_global_uninit_a=0x804a038      全局静态未初始化：数据段     static_global_uninit_a=0
&static_global_uninit_b=0x804a03c        全局静态未初始化：数据段   static_global_uninit_b=0
  &static_local_uninit_a=0x804a040        局部静态未初始化：数据段     static_local_uninit_a=0
  &static_local_uninit_b=0x804a044        局部静态未初始化：数据段      static_local_uninit_b=0
​           &global_uninit_b=0x804a048        全局未初始化：数据段      global_uninit_b=0
​            &global_uninit_a=0x804a04c      全局未初始化：数据段          global_uninit_a=0

​    这里可以发现，**初始化的和未初始化的数据好像是分开存放的**，因此我们可以猜测BSS段是存在的，只不过数据段是分为初始化和未初始化（即BSS段）的两部分，他们在加载到进程地址空间时是合并为数据段了，在进程地址空间中没有单独分为一个区域。

还有一个问题，静态数据与非静态数据是否是分开存放的呢？请读者自行分析一下。

接下来我们从**程序的角度**看一下，这些存储区域是如何分配的。首先我们先介绍一下ELF文件格式。

ELF（Executable and Linkable Format ）文件格式是一个开放标准，各种UNIX系统的可执行文件都采用ELF格式，它有三种不同的类型：

–可重定位的目标文件（Relocatable，或者Object File）

–可执行文件（Executable）

–共享库（Shared Object，或者Shared Library）

 

下图为ELF文件的结构示意图（来源，不详）：

![img](http://hi.csdn.net/attachment/201110/22/0_1319296523sGdn.gif)

一个程序编译生成目标代码文件（ELF文件）的过程如下，此图引自《程序员的自我修养》一书的一个图：![img](http://hi.csdn.net/attachment/201110/22/0_1319296665xX21.gif)

可以通过readelf命令查看EFL文件的相关信息，例如 readelf  -a  a.out  ，我们只关心各个段的分配情况，因此我们使用以下命令：

```shell
readelf -S a.out
```

![img](http://hi.csdn.net/attachment/201110/22/0_1319297156d3UK.gif)将这里的内存布局与之前看到的程序的运行结果进行分析：

​                &global_init_a=0x804a018       全局初始化：数据段              global_init_a=1
​            &global_uninit_a=0x804a04c      全局未初始化：BSS段          global_uninit_a=0
​     &static_global_init_a=0x804a01c      全局静态初始化：数据段      static_global_init_a=1
&static_global_uninit_a=0x804a038      全局静态未初始化：BSS段     static_global_uninit_a=0
​             &const_global_a=0x80487c0     全局只读变量： 只读数据段        const_global_a=1
​                 &global_init_b=0x804a020       全局初始化：数据段      global_init_b=1
​            &global_uninit_b=0x804a048        全局未初始化：BSS段      global_uninit_b=0
​     &static_global_init_b=0x804a024        全局静态初始化：数据段    static_global_init_b=1
&static_global_uninit_b=0x804a03c        全局静态未初始化：BSS段   static_global_uninit_b=0
​            &const_global_b=0x80487c4        全局只读变量： 只读数据段             const_global_b=1
​     &static_local_init_a=0x804a028         局部静态初始化：数据段      static_local_init_a=1
 &static_local_uninit_a=0x804a040        局部静态未初始化：BSS段     static_local_uninit_a=0
​      &static_local_init_b=0x804a02c        局部静态初始化：数据段      static_local_init_b=1
 &static_local_uninit_b=0x804a044        局部静态未初始化：BSS段      static_local_uninit_b=0
​                           p_chars=0x80487c8        字符串常量：只读数据段          p_chars=abcdef
ELF 文件一般包含以下几个段 :

- **.text section：主要是编译后的源码指令，是只读字段。**
- **.data section ：初始化后的非const的全局变量、局部static变量。**
- **.bss：未初始化后的非const全局变量、局部static变量。**
- **.rodata字段  是存放只读数据 **

分析到这以后，我们在和之前分析的结果对比一下，**会发现确实存在BSS段**，地址为0804a030 ，大小为0x20，之前我们的程序中未初始化的的确存放在这个地址区间中了，只不过执行exec系统调用时，将这部分的数据初始化为0后，放到了进程地址空间的数据段中了，在进程地址空间中就没有必要存在BSS段了，因此都称做数据段。同理，.rodata字段也是与text段放在一起了。

在ELF文件中，找不到局部非静态变量和动态分配的内容。

