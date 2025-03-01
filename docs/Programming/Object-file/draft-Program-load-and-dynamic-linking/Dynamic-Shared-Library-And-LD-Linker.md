[Linux Dynamic Shared Library && LD Linker](https://www.cnblogs.com/LittleHann/p/4244863.html)

## 动态链接的意义


1. **静态链接**对**内存**和**磁盘**的浪费很严重，在静态链接中，C语言静态库是很典型的占用空间的例子
2. 静态链接对程序的更新、部署、发布会造成严重的麻烦


> 第一点所说的包括内存和磁盘，其实这就是程序和进程的关系。

为了解决这些问题，最好的思路就是把程序的模块相互**分割**开来，形成独立的文件，而不再将它们静态地链接在一起。简单来说，就是不对那些组成程序的目标文件进行链接，等到程序要**运行时**才进行**链接**，也就是说，把**链接**这个过程推迟到了**运行时**再进行，这就是**"动态链接(dynamic linking)"**的基本思想

### 动态链接的优点


1. 多个进程使用到同一个动态链接库文件，只要在内存中映射一份ELF .SO文件即可，有效地减少了进程的内存消耗

2. 减少物理页面的换入换出(减少page out、page in操作)

3. 增加CPU缓存的命中率，因为不同进程间的数据和指令访问都集中在了同一个共享模块上

4. 使程序的升级更加容易，在升级程序库或共享某个模块时，只要简单地将旧的目标文件覆盖掉，而无须将所有的程序再重新链接一遍。当程序下一次运行的时候，新版本的目标文件会被自动装载到内存并链接起来，程序就完成了升级的操作
>这让我想到了之前碰到的undefined symbol错误，如果我们使用的函数在第三方提供的动态链接库中，我们往往会在编译的时候加上`-llib`的方式来指定这个动态链接库。所以即使是动态链接，在编译的时候，还是需要提供需要使用的动态链接库的信息的，并且保证程序在运行的时候是能够链接到的，还有一个问题是，在编译so的时候，如果编译器发现了某个符号是undefined的，但是编译器是不会报错的。这种undefined symbol错误，可能会导致程序异常。也有可能程序还是正常运行。

5. 程序可扩展性和兼容性
使用动态链接技术，程序在运行时可以动态地选择加载各种程序模块，即**插件技术(Plug-in)**
    1) 程序按照一定的规则制定好程序的**接口**，第三方开发者可以按照这种**接口**来编写符合要求的**动态链接文件**，该程序可以**动态地载入**各种由第三方开发的模块，在程序运行时动态地链接，实现程序功能的扩展。典型地如php的**zend扩展**、iis的filter/extension、apache的**mod模块**
    2) 动态链接还可以加强程序的兼容性。一个程序在不同的平台运行时可以动态地链接到由操作系统提供的**动态链接库**，这些动态链接库在**程序**和**操作系统**之间增加了一个**中间层**，从而消除了程序对不同平台之间依赖的差异性




### 动态链接文件的类别

动态链接涉及运行时的链接及多个文件的装载，必须要有操作系统的支持，因为动态链接的情况下，进程的**虚拟地址空间**的分布会比静态链接的情况下更为复杂，还需要考虑到一些存储管理、内存共享、进程线程等机制的考虑


1. Linux
在Linux系统中，ELF动态链接文件被称为动态共享对象(DSO Dynamic Shared Objects)，一般以".so"为扩展名
常用的C语言库的**运行库glibc**，它的**动态链接形式的版本**保存在"/lib/libc.so"、"/lib64/libc.so"。整个系统只保留一份C语言库的动态链接文件，而所有的由C语言编写的、动态链接的程序都可以在运行时使用它，当程序被装载时，系统的**动态链接器**会将程序所需的**所有动态链接库**(最基本的就是libc.so)装载到**进程的地址空间**，并且将程序中所有**未决议的符号**绑定到相应的**动态链接库**中，并进行**重定位**工作

2. Windows
在Windows系统中，动态链接文件被称为动态链接库(Dynamic Linking Library)，一般以".dll"为扩展名

## 地址无关代码: PIC
1. **可执行文件**在**编译**时可以确定自己在**进程虚拟地址空间**中的位置，因为可执行文件往往都是第一个被加载的文件，它可以选择一个固定的位置
    1) Linux: 0x08040000
    2) Windows: 0x0040000

2. **共享对象**在**编译时**不能假设自己在进程虚拟地址空间中的位置
>需要注意“共享”这个词的含义
### 装载时重定位
Linux和GCC支持2种重定位的方法：
1. **链接时**重定位(Link Time Relocation)
-shared -fPIC
在程序**链接**的时候就将代码中**绝对地址的引用**重定位为**实际的地址**

2. 装载时重定位(Load Time Relocation)
-shared 
程序模块在编译时目标地址不确定而需要在装载时将模块重定位

### 地址无关代码
**装载时重定位**是解决动态模块中有**绝对地址引用**的方法之一，但是还存在一个问题，**指令部分**无法在多个进程间**共享**，为了解决这个问题，一个基本思想就是把指令中那些需要被修改的部分分离出来，跟**数据部分**放在一起，这样指令就可以保持不变，而**数据部分**可以在每个进程中拥有一个副本，这种方案就是**地址无关代码(PIC Position-Independent Code)**

> 关于地址无关代码的补出内容在[这篇文章](./load-time-relocation.md)中介绍了。

我们把共享对象模块中的地址引用按照模块内部引用/模块外部引用、指令引用/数据访问分为4类
```
/*
pic.c
*/
static int a;
extern int b;
extern void ext();

void bar()

{
    //Type2: Inner-module data access(模块内数据访问)
    a = 1;

    //Tyep4: Inter-module data access(模块间数据访问)
    b = 2;
}

void foo()
{
    //Type1: Inner-module call(模块内指令引用)
    bar();

    //Type3: Inter-module call()
    ext();
}
```
值得注意的是，当编译器在编译pic.c时，它并不能确定变量b、函数ext()是**模块外部**还是**模块内部**的，因为它们有可能被定义在同一个共享对象的其他**目标文件**中，所以编译器只能把它们都当作模块外部的函数和变量来处理。

#### Type1: Inner-module call(模块内指令引用)

这是最简单的一种情况，被调用的函数与调用者都处于**同一个模块**，它们之间的相对位置是固定的，对于现代操作系统来说，模块内部跳转、函数调用都可以是"相对地址调用"、或者是"基于寄存器的相对调用"，所以对于这种指令是*不需要重定位*的，只要模块内的相对位置不变，则模块内的指令调用就是**地址无关**的

#### Type2: Inner-module data access(模块内数据访问)

我们知道，一个模块前面一般是若干个页的代码，后面紧跟着若干个页的数据，这些页之间的相对位置是固定的，所以只需要相对于当前指令加上"固定的偏移量"就可以访问到*模块内部数据*了

![](https://images0.cnblogs.com/blog/532548/201502/011002133948420.png)

#### Type3: Inter-module call()

GOT实现指令地址无关的方式和GOT实现模块间数据访问的方式类似，唯一不同的是，GOT中的项保存的是**目标函数**的地址，当模块要调用目标函数时，可以通过GOT中的项进行间接跳转

#### Tyep4: Inter-module data access(模块间数据访问)

模块间的数据访问比模块内部稍微麻烦一点，因为模块间的数据访问*目标地址*要等到*装载*时才能确定。而我们要达到**代码**和**地址**无关的目的，最基本的思想就是把和**地址**相关的部分放到**数据段**中，ELF的做法是在**数据段**里建立一个指向这些变量的**指针数组**，也被称为**全局偏移表**(global offset table GOT)，当代码需要引用到该全局变量时，可以通过GOT中相对应的项进行间接引用。
链接器在装载动态模块的时候会查找每个变量所在的地址，然后填充GOT中的各个项，以确保每个指针所指向的地址正确，由于GOT本身是放在数据段的，所以它可以在模块装载时被修改，并且每个进程都可以有独立的副本，相互不受影响。

综上所述，地址无关代码的实现方式如下:
```
1. 模块内部
    1) 指令跳转、调用: 相对跳转和调用
    2) 数据访问: 相对地址访问
2. 模块外部
    1) 指令跳转、调用: 间接跳转和调用(GOT)
    2) 数据访问: 间接访问(GOT)
```

使用GCC产生**地址无关代码**很简单，只需要使用`-fPIC`参数即可

区分一个**DSO**(动态共享对象)是否为**PIC**的方法很简单，输入以下指令
```
readelf -d hook.so | grep TEXTREL
/*
1. PIC
PIC的DSO是不会包含任何代码段重定位表的，TEXTREL表示代码段重定位表地址

2. 非PIC
本条指令有任何输出，则hook.so就不是PIC
*/ 
```
**地址无关代码**技术除了可以用在**共享对象**上面，它也可以用于**可执行文件**，一个以地址无关方式编译的可执行文件被称作**地址无关可执行文件**(PIE Position-Independent Executable)，与GCC的"-fPIC"类似，产生PIE的参数为"-fPIE"。
## 全局偏移表(GOT)
1. 对于**模块外部**引用的**全局变量**和**全局函数**，用GOT表的表项内容作为地址来**间接寻址**
2. 对于本模块内的**静态变量**和**静态函数**，用GOT表的首地址作为一个基准，用相对于该基准的偏移量来引用，因为不论程序被加载到何种地址空间，模块内的静态变量和静态函数与GOT的距离是固定的，并且在链接阶段就可知晓其距离的大小

？？它这是基于怎样的一种运算才能够保证准确无误
