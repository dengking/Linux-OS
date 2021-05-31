# Multiplexing

本文讨论"Multiplexing"的含义，它是由: "multi+plexing" 组成

## wikipedia [Multiplexing](https://en.wikipedia.org/wiki/Multiplexing) 

> NOTE: 
>
> 1、"Multiplexing"的意思是"多路复用"
>
> 2、在现实application中，都需要有reverse operation: **demultiplexing**，**demultiplexing**其实非常类似于dispatch，关于此的文章有:
>
> a、zhihu [如何深刻理解reactor和proactor？](https://www.zhihu.com/question/26943938) # [A](https://www.zhihu.com/question/26943938/answer/68773398)
>
> 



In [telecommunications](https://en.wikipedia.org/wiki/Telecommunications) and [computer networks](https://en.wikipedia.org/wiki/Computer_networks), **multiplexing** (sometimes contracted to **muxing**) is a method by which multiple analog or digital signals are combined into one signal over a [shared medium](https://en.wikipedia.org/wiki/Shared_medium)（将多个模拟信号或电子信号合并为一个，通过一个共享的媒介进行发送）. The aim is to share a scarce resource（稀缺资源）. For example, in telecommunications, several [telephone calls](https://en.wikipedia.org/wiki/Telephone_call) may be carried using one wire. Multiplexing originated in [telegraphy](https://en.wikipedia.org/wiki/Multiplexing#Telegraphy) in the 1870s, and is now widely applied in communications. In [telephony](https://en.wikipedia.org/wiki/Multiplexing#Telephony), [George Owen Squier](https://en.wikipedia.org/wiki/George_Owen_Squier) is credited with the development of **telephone carrier multiplexing**（电话运营商多路复用） in 1910.

### Multiplexing  and demultiplexing

The multiplexed signal is transmitted over a **communication channel** such as a cable. The multiplexing divides the capacity of the **communication channel** into several **logical channels**, one for each **message signal** or **data stream** to be transferred. A reverse process, known as **demultiplexing**, extracts the original channels on the receiver end.

> NOTE: 
>
> 1、上面这段话非常重要，它对于理解Multiplexing 的本质有着帮助
>
> 2、physical and logical :
>
> physical: **communication channel** 
>
> logical:  **logical channels**

A device that performs the multiplexing is called a [multiplexer](https://en.wikipedia.org/wiki/Multiplexer) (MUX), and a device that performs the reverse process is called a [demultiplexer](https://en.wikipedia.org/wiki/Demultiplexer) (DEMUX or DMX).

[Inverse multiplexing](https://en.wikipedia.org/wiki/Inverse_multiplexing) (IMUX) has the opposite aim as multiplexing, namely to break one data stream into several streams, transfer them simultaneously over several communication channels, and recreate the original data stream.

### I/O multiplexing

In [computing](https://en.wikipedia.org/wiki/Computing), **I/O multiplexing** can also be used to refer to the concept of processing multiple [input/output](https://en.wikipedia.org/wiki/Input/output) [events](https://en.wikipedia.org/wiki/Event_(computing)) from a single [event loop](https://en.wikipedia.org/wiki/Event_loop), with system calls like [poll](https://en.wikipedia.org/wiki/Poll_(Unix))[[1\]](https://en.wikipedia.org/wiki/Multiplexing#cite_note-1) and [select (Unix)](https://en.wikipedia.org/wiki/Select_(Unix)).[[2\]](https://en.wikipedia.org/wiki/Multiplexing#cite_note-2)



> NOTE: 如何来理解multiplexing？multiplexing的关键在于many和one，下面是一些例子: 
>
> 1、在[telecommunications](https://en.wikipedia.org/wiki/Telecommunications)中multiple是multiple analog or digital signals ，one是 combined into one signal over a [shared medium](https://en.wikipedia.org/wiki/Shared_medium) 。
>
> many logical and one physical ；
>
> 2、在 [computing](https://en.wikipedia.org/wiki/Computing)的 **I/O multiplexing**中multiple是multiple [input/output](https://en.wikipedia.org/wiki/Input/output) [events](https://en.wikipedia.org/wiki/Event_(computing)) 而one则是a single [event loop](https://en.wikipedia.org/wiki/Event_loop) object；
>
> many IO event and one event loop object；
>
> 显然multiplexing的目标在于实现性能的提升，资源的节省；

### Types



#### Space-division multiplexing

#### Frequency-division multiplexing

#### Time-division multiplexing

> NOTE: 
>
> 1、下面的OS timesharing就属于这种范畴

#### Polarization-division multiplexing

#### Orbital angular momentum multiplexing

#### Code-division multiplexing



## Examples

### rabbitmq [AMQP 0-9-1 Model Explained](https://www.rabbitmq.com/tutorials/amqp-concepts.html)

其中的channel和connection就是multiplexing；

### OS time sharing

在《`Understanding.The.Linux.kernel.3rd.Edition`》中有这样的话：

> Linux scheduling is based on the ***time sharing*** technique: several processes run in "time multiplexing" because the CPU time is divided into ***slices***, one for each runnable process. [`*`] Of course, a single processor can run only one process at any given instant. If a currently running process is not terminated when its ***time slice*** or ***quantum*** expires, a **process switch** may take place. Time sharing relies on **timer interrupts** and is thus transparent to processes. No additional code needs to be inserted in the programs to ensure CPU time sharing.

可以看到，time sharing也是一种multiplex技术，它共享的是CPU。