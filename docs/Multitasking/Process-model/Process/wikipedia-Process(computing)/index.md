# wikipedia [Process (computing)](https://en.wikipedia.org/wiki/Process_(computing))

In computing, a **process** is the [instance](https://en.wikipedia.org/wiki/Instance_(computer_science)) of a [computer program](https://en.wikipedia.org/wiki/Computer_program) that is being executed. It contains the program code and its activity. Depending on the [operating system](https://en.wikipedia.org/wiki/Operating_system) (OS), a process may be made up of multiple [threads of execution](https://en.wikipedia.org/wiki/Thread_(computing)) that execute instructions [concurrently](https://en.wikipedia.org/wiki/Concurrency_(computer_science)).

> NOTE: 上面这段话描述了process和thread之间的关系。



While a computer program is a passive collection of [instructions](https://en.wikipedia.org/wiki/Instruction_set), a process is the actual execution of those instructions. Several processes may be associated with the same program; for example, opening up several instances of the same program often results in more than one process being executed.

> NOTE: 
>
> the above paragraph summarize the difference between **process** and **program**.

[Multitasking](https://en.wikipedia.org/wiki/Computer_multitasking) is a method to allow multiple processes to share [processors](https://en.wikipedia.org/wiki/Central_processing_unit) (CPUs) and other **system resources**. Each CPU (core) executes a single [task](https://en.wikipedia.org/wiki/Task_(computing)) at a time. However, multitasking allows each processor to [switch](https://en.wikipedia.org/wiki/Context_switch) between tasks that are being executed without having to wait for each task to finish. Depending on the operating system implementation, **switches** could be performed when tasks perform [input/output](https://en.wikipedia.org/wiki/Input/output) operations, when a task indicates that it can be switched, or on hardware [interrupts](https://en.wikipedia.org/wiki/Interrupt).

> NOTE: 
>
> 关于system resource，可以参考下面的[Representation](#Representation) 章节，也可以参考[这篇文章](https://en.wikipedia.org/wiki/System_resource) 。既然process会使用system resource，那么process就有manage 这些system resource的责任；

A common form of multitasking is [time-sharing](https://en.wikipedia.org/wiki/Time-sharing). Time-sharing is a method to allow high responsiveness for interactive user applications. In time-sharing systems, [context switches](https://en.wikipedia.org/wiki/Context_switch) are performed rapidly, which makes it seem like multiple processes are being executed simultaneously on the same processor. This seeming execution of multiple processes simultaneously is called [concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science)).

> NOTE: tag-OS scheduler-time sharing time slice-quantum分时-preemption抢夺-context switch

For security and reliability, most modern [operating systems](https://en.wikipedia.org/wiki/Operating_system) prevent direct [communication](https://en.wikipedia.org/wiki/Inter-process_communication) between independent processes, providing strictly mediated(间接地) and controlled inter-process communication functionality.

## Representation

In general, a computer system process consists of (or is said to *own*) the following resources:

1、An *image* of the executable [machine code](https://en.wikipedia.org/wiki/Machine_code) associated with a program.

2、Memory (typically some region of [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory)); which includes the executable code, process-specific data (input and output), a [call stack](https://en.wikipedia.org/wiki/Call_stack) (to keep track of active [subroutines](https://en.wikipedia.org/wiki/Subroutine) and/or other events), and a [heap](https://en.wikipedia.org/wiki/Memory_management#Dynamic_memory_allocation) to hold intermediate computation data generated during run time.

3、Operating system descriptors of resources that are allocated to the process, such as [file descriptors](https://en.wikipedia.org/wiki/File_descriptor)([Unix](https://en.wikipedia.org/wiki/Unix) terminology) or [handles](https://en.wikipedia.org/wiki/Handle_(computing)) ([Windows](https://en.wikipedia.org/wiki/Microsoft_Windows)), and data sources and sinks.

> NOTE: 
>
> 参见APUE 3.10 File Sharing，其中介绍了table of open file descriptors

4、[Security](https://en.wikipedia.org/wiki/Computer_security) attributes, such as the process owner and the process' set of permissions (allowable operations).

5、[Processor](https://en.wikipedia.org/wiki/Central_processing_unit) state ([context](https://en.wikipedia.org/wiki/Context_(computing))), such as the content of [registers](https://en.wikipedia.org/wiki/Processor_register) and physical memory addressing. The *state* is typically stored in computer registers when the process is executing, and in memory otherwise.[[1\]](https://en.wikipedia.org/wiki/Process_(computing)#cite_note-OSC_Chap4-1)

The operating system holds most of this information about active processes in data structures called [process control blocks](https://en.wikipedia.org/wiki/Process_control_block). Any subset of the resources, typically at least the **processor state**, may be associated with each of the process' [threads](https://en.wikipedia.org/wiki/Thread_(computer_science)) in operating systems that support threads or *child* (*daughter*) processes.

> NOTE: process control blocks也称为**Entry of the Process Table**，在APUE的3.10节中对其进行了介绍；

The operating system keeps its processes separate and allocates the resources they need, so that they are less likely to interfere with each other and cause system failures (e.g., [deadlock](https://en.wikipedia.org/wiki/Deadlock) or [thrashing](https://en.wikipedia.org/wiki/Thrashing_(computer_science))). The operating system may also provide mechanisms for [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication) to enable processes to interact in safe and predictable ways.

> NOTE: 既然process会占用system resource，所以manage这些resource是process的职责之一；参见这篇文章:[Resource management](https://en.wikipedia.org/wiki/Resource_management_(computing)) ，在本目录下，添加了resource management目录，存放和process resource management相关的内容；





## TODO

在[User space](https://en.wikipedia.org/wiki/User_space)中对也对进程进行了一些介绍，感觉是非常好的。



