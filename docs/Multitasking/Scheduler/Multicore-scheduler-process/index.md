# Multicore、scheduler、process

多核的CPU,每个核所对应的是process还是thread？？

根据`lscpu`的输出中的`Thread(s) per core`推测，感觉是每个core对应一个process

```bash
[anaconda@dk ~]$ lscpu
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                4
On-line CPU(s) list:   0-3
Thread(s) per core:    1
Core(s) per socket:    4

```

关于这个问题，我使用"For multi-core cpu,what every core correspond to? process or thread"进行bing与Google，以下是我觉得比较好的回答，值的深入研究一下。

## stackoverflow [How do SMP cores, processes, and threads work together exactly?](https://stackoverflow.com/questions/2986931/how-do-smp-cores-processes-and-threads-work-together-exactly)

On a single core CPU, each process runs in the OS, and the CPU jumps around from one process to another to best utilize itself（切换）. A process can have many threads, in which case the CPU runs through these threads when it is running on the respective process.

Now, on a multiple core CPU:

1、Do the cores run in every process together, or can the cores run separately in different processes at one particular point of time? For instance, you have program A running two threads. Can a dual core CPU run both threads of this program? I think the answer should be yes if we are using something like [OpenMP](http://en.wikipedia.org/wiki/OpenMP). But while the cores are running in **this OpenMP-embedded process**, can one of the cores simply switch to other process?

2、For programs that are created for single core, when running at 100%, why is the CPU utilization of each core distributed? (e.g. A dual core CPU of 80% and 20%. The utilization percentage of all cores always add up to 100% for this case.) Do the cores try to help each other by running each thread, of each process, in some ways?

#### A

**Cores** (or CPUs) are the physical elements of your computer that execute code. Usually, each core has all necessary elements to perform computations, register files, interrupt lines etc.

> NOTE: 
>
> 每个core都具有完备的运行一个thread的条件

Most **operating systems** represent applications as **processes**. This means that the application has its own **address space** (== view of memory), where the OS makes sure that this view and its content are isolated from other applications.

> NOTE: 
>
> 每个process都有自己的address space，这是一种隔离

A process consists of one or more **threads**, which carry out the ***real work of an application*** by executing machine code on a CPU. The operating system determines, which **thread** executes on which **CPU** (by using clever heuristics(启发) to improve load balance(负载均衡), energy consumption etc.). If your application consists only of a single thread, then your whole multi-CPU-system won't help you much as it will still only use one CPU for your application. (However, overall performance may still improve as the OS will run other applications on the other CPUs so they don't **intermingle**（混合，交融，交织） with the first one).

> NOTE: 
>
> 在multicore CPU上，OS scheduler是非常复杂的

Now to your specific questions:

1) The OS usually allows you to at least give **hints** about on which core you want to execute certain threads. What OpenMP does is to generate code that spawns a certain amount of threads to distribute shared computational work from loops of your program in multiple threads. It can use the OS's hint mechanism (see: **thread affinity**) to do so. However, OpenMP applications will still run concurrently to others and thus the OS is free to interrupt（中断） one of the threads and schedule other (potentially unrelated) work on a CPU. In reality, there are many different **scheduling schemes** you might want to apply depending on your situation, but this is highly specific and most of the time you should be able to trust your OS doing the right thing for you.

> NOTE: 
>
> 1、control theory
>
> 2、"What OpenMP does is to generate code that spawns a certain amount of threads to distribute shared computational work from loops of your program in multiple threads"
>
> 通过这段话，可以看出OpenMP的implementation

2) Even if you are running a single-threaded application on a multi-core CPU, you notice other CPUs doing work as well. This comes 

a) from the OS doing its job in the meantime and 

b) from the fact that your application is never running alone -- each running system consists of a whole bunch of concurrently executing tasks. Check Windows' task manager (or *ps/top* on Linux) to check what is running.

## stackoverflow [What does multicore assembly language look like?](https://stackoverflow.com/questions/980999/what-does-multicore-assembly-language-look-like) 



## Book-Understanding-the-Linux-Kernel

在下面章节中对这个topic也有讨论:

`Chapter-3-Processes\3.2.2.4-The-process-list`

每个processor都有一个process list

`Chapter-1-Introduction\1.1-Linux-Versus-Other-Unix-Like-Kernels`
