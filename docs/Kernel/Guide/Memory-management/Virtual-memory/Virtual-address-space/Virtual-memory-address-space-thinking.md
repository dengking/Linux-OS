# 关于Virtual address space的思考

## 一个process的virtual address space的上限？

我之前出现out-of-memory的情况是：process非常高频地执行一个存在memory leakage的function，最终导致out-of-memory（这个function使用的是`malloc`式的，所以它所获得的memory是位于heap的，那位于heap上的memory没有上限吗？它如何能够导致out-of-memory？）。一个process如何能够将一台机器的memory耗尽？这个问题转换一下就是难道一个process的address space没有上限吗?

一个process的address space是有上限的，这就是virtual address的长度决定的，比如32bit，则它的上限就是4G（仅仅只有4G，这可能吗？）直观感受virtual address的长度就是C中的指针类型的长度，正如在[Virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space)中所描述的。

需要考虑的一个问题是：CPU的word size和virtual address length之间的关系。两者肯定不是一回事儿。

每个process有一个virtual address space，与这个virtual address space相匹配的是一个page table，这个page table记录着归属于它的所有的memory，那是否是在预先就将这个page table的size给固定了呢？还是后续在process运行过程中，这个page table的大小会改变？

与out-of-memory相关的另外一个问题是：stackoverflow。




## virtual address的意义
lazy，即无需一次性分配整个virtual address space，而是用时再分配。

copy on write



其实通过这个思考才发现virtual memory的重要价值所在，它是实现demand page的基础，它是实现扩充memory的基础，它是实现copy on write的基础。


## linux process virtual address space和page table之间的关系

当然是有差别的，process virtual address space则是表示进程的地址空间，其中所使用的是virtual address，page table是记录着virtual address和physical address之间的映射关系。

显然page table对user是透明的，但是我们却可以访问到virtual address，通过pointer。

### 描述process virtual address space的数据结构

在9.2. The Memory Descriptor中指出：

[`mm_struct`](https://elixir.bootlin.com/linux/latest/ident/mm_struct)

### 描述page table的data structure

每个virtual address space都有一个对应的page table，那这page table的data structure是如何的？

其实这在Chapter 2. Memory Addressing中已经描述了。

## 从memory usage的角度来分析process的运行

进程的运行伴随着内存的使用，目前为止，我还没有一个完整、清晰的认知。如何时分配memory？何时回收memory？

分配memory的场景：

- 函数调用
- stored program
- 在context switch的时候，OS需要将process的context保存起来



其实我知道，回答这个问题的更好的方式是阅读计算机执行指令的流程。



### Address space

这个问题是由前面的关于process的resource的思考衍生出来的。Address space是一个process非常重要的resource，可以认为它是process进行活动的空间。目前的OS都是采用的virtual address，即process运行的时候，所使用的是virtual memory，所以也可以将Address space称为Virtual address space。关于process的Virtual address space，我有如下疑问：

Question:

process使用virtual memory，并且使用基于page的memory management，那它是如何实现的基于page的virtual memory呢？是分割为一个一个的page？

经过简单的思考，我觉得应该是编译器在给生成代码的时候其实是不需要考虑这个问题的，因为是OS在运行program的时候按照page进行memory management，无论编译器生成的program是怎样的，是OS负责将这些program装入到memory中，这一切对compiler而言都是透明的。

但是这个问题可以延伸一下：我们知道，编译器生成的代码肯定是需要遵循alignment的，那这就涉及到alignment和page size之间的关系；应该只要符合alignment，那么应该就不会存在一个数据存储跨越了多个page的情况了。

Question:

进程的virtual address space都是相同的，那virtual address是如何映射到physical memory address的呢？

既然使用的是demand page，也就是在process运行的时候需要访问该virtual memory的时候，才allocate physical memory或者swap-in，才将virtual address映射到physical memory并将这些信息保存到该process的page table中。

其实通过这个思考才发现virtual memory的重要价值所在，它是实现demand page的基础，它是实现扩充memory的基础，它是实现copy on write的基础。



Question:

如1.6.8.4. Process virtual address space handling节所叙述的

> The kernel usually stores a process virtual address space as a list of memory area descriptors .

即我们通常将virtual address space分割为多块，那是在什么地方将virtual address space分割为如上所述的a **list** of *memory area descriptors* ？

operating system采用的是demand paging，并且stack的增长方向和heap的增长方向相反，那这些又是如何实现的呢？

要想完全理解这个问题，阅读calling convention。我觉得process在运行过程中，对call stack的维护是一个非常重要的活动，每次new一个栈帧都需要分配新的内存空间重要才能够保证process运行下去。

另外一个问题是，为什么需要申请memory？

其实如果这个系统中只有一个程序的话，那么它想怎么样使用memory就怎么样使用memory，但是问题是，我们的系统是需要支持多任务的，那它就需要做好不同的process之间的隔离，A process不能够使用B process的东西。所以，所有的process都必须要先想OS申请memory，然后才能够使用，OS会记住memory的所属，这样就能够保证不冲突了。其次是process的运行是需要一定的memory space来存放它的相关的数据的，比如在发生context switch的时候，就需要将它的context相关的数据都保存到它的memory space中来。另外一个就是process的call stack，这是非常重要的一个需要memory space的场所。



Question:

如前所述，栈也是virtual address space的成分之一，每个thread都有各自**独立**的call stack，而所有的thread理论上都是共享process的virtual address space的，那这又是如何实现的呢？

其实最最简单的方式是查看`task_descriptor`的成员变量





## See also

Is kernel data segment in process address space?

[Anatomy of a Program in Memory](https://manybutfinite.com/post/anatomy-of-a-program-in-memory/)

[Does every process have its own page table?](https://stackoverflow.com/questions/4381317/does-every-process-have-its-own-page-table)

[How do I save space with inverted page tables?](https://stackoverflow.com/questions/10772094/how-do-i-save-space-with-inverted-page-tables)

[Page table](https://en.wikipedia.org/wiki/Page_table)

[Why one page table per process](https://stackoverflow.com/questions/8305254/why-one-page-table-per-process)

[What are high memory and low memory on Linux?](https://unix.stackexchange.com/questions/4929/what-are-high-memory-and-low-memory-on-linux)

