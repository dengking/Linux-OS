# Process control block

## wikipedia [Process control block](https://en.wikipedia.org/wiki/Process_control_block)



**Process Control Block** (**PCB**, also called **Task Controlling Block**,[[1\]](https://en.wikipedia.org/wiki/Process_control_block#cite_note-OSConcepts-1) **Entry of the Process Table**,[[2\]](https://en.wikipedia.org/wiki/Process_control_block#cite_note-2) **Task Struct**, or **Switchframe**) is a data structure in the [operating system](https://en.wikipedia.org/wiki/Operating_system) [kernel](https://en.wikipedia.org/wiki/Kernel_(computer_science)) containing the information needed to manage the scheduling of a particular process. The PCB is "the manifestation(表示) of a process in an operating system."[[3\]](https://en.wikipedia.org/wiki/Process_control_block#cite_note-3)

### Role

The role of the PCBs is central in **process management**: they are accessed and/or modified by most OS utilities, including those involved with **scheduling**, **memory** and **I/O resource access** and **performance monitoring**. It can be said that the set of the PCBs defines the current state of the operating system. Data structuring for processes is often done in terms of PCBs. For example, pointers to other PCBs inside a PCB allow the creation of those queues of processes in various scheduling [states](https://en.wikipedia.org/wiki/Process_state)("ready", "blocked", etc.) that was previously mentioned.



### Structure

In modern sophisticated multitasking systems, the **PCB** stores many different items of data, all needed for correct and efficient **process management**.[[1\]](https://en.wikipedia.org/wiki/Process_control_block#cite_note-OSConcepts-1) Though the details of these structures are obviously system-dependent, we can identify some very **common** parts, and classify them in three main categories:

1、Process identification data

2、Process state data

3、Process control data

The approach commonly followed to represent this information is to create and update **status tables** for each relevant entity, like memory, I/O devices, files and processes.

> NOTE: 翻译如下: 表示此信息的常用方法是为每个相关实体创建和更新状态表，如内存，I / O设备，文件和进程。

**Memory tables**, for example, may contain information about the allocation of main and secondary (virtual) memory for each process, authorization attributes for accessing memory areas shared among different processes, etc. **I/O tables** may have entries stating the availability of a device or its assignment to a process, the status of I/O operations being executed, the location of memory buffers used for them, etc.

> NOTE : 
>
> 1、关于 **I/O tables** ，参见:
>
> a、APUE 3.10 File Sharing，其中介绍了table of open file descriptors；
>
> b、在Wikipedia的[File descriptor](https://en.wikipedia.org/wiki/File_descriptor) 也提及了**file descriptor table**的概念；

> NOTE : 
>
> 在[The Life of a Process](https://opensourceforu.com/2016/03/the-life-of-a-process/)中，从内核实现的角度描述了上面这些内容是如何实现的，在youdao `Unix-process-lifetime.md`中收录了这篇文章；

*Process identification data* always include a unique identifier for the process (almost invariably（总是） an integer number) and, in a multiuser-multitasking system, data like the identifier of the **parent process**, **user identifier**, **user group identifier**, etc. The process id is particularly relevant, since it is often used to cross-reference the OS **tables** defined above, e.g. allowing to identify which process is using which I/O devices, or memory areas.

> NOTE : 在OS的实现中，可以看到有很多的实现都是使用table的；

*Process state data* are those pieces of information that define the status of a process when it is suspended, allowing the OS to restart it later and still execute correctly. This always includes the content of the **CPU general-purpose registers**, the **CPU process status word**, **stack and frame pointers** etc. During [context switch](https://en.wikipedia.org/wiki/Context_switch), the running process is stopped and another process is given a chance to run. The kernel must stop the execution of the running process, copy out the values in hardware registers to its **PCB**, and update the hardware registers with the values from the **PCB** of the new process.

> NOTE : 上面这段话是解释地非常好的，它从PCB的角度来分析了context switch中所涉及的使用PBC中包含的process state data来更新hardware，这样获得了CPU的process就知道了后续应该如何执行；

*Process control information* is used by the OS to manage the process itself. This includes:

1、**The process scheduling state:** The state of the process in terms of "ready", "suspended", etc., and other scheduling information as well, like priority value, the amount of time elapsed since the process gained control of the CPU or since it was suspended. Also, in case of a suspended process, **event identification data** must be recorded for the event the process is waiting for.

> NOTE :  **event identification data**是非常重要的，它记录了process所等待的event；显然，在这种情况下，process处于waiting状态；在[**Processes**](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/3_Processes.html)中描述，每个device都有一个**device queues**，显然这个device queue是这个device来进行维护的，当它完成用户请求的操作偶，它就可以通过它的device queue来知道哪些process正等待着它；那PCB中，需要维护它所等待的event吗？按照上面的描述PCB是需要维护的；

2、**Process structuring information:** process's children id's, or the id's of other processes related to the current one in some functional way, which may be represented as a queue, a ring or other data structures.

3、**Interprocess communication information:** various **flags**, **signals** and **messages** associated with the communication among independent processes may be stored in the PCB.

4、**Process Privileges** in terms of allowed/disallowed access to system resources.

5、**Process State:** State may enter into new, ready, running, waiting, dead depending on **CPU scheduling**.

> NOTE : [Process state](https://en.wikipedia.org/wiki/Process_state) 

6、**Process Number (PID):** A unique identification number for each process in the operating system (also known as [Process ID](https://en.wikipedia.org/wiki/Process_identifier)).

7、**Program** **Counter (PC):** A pointer to the address of the next instruction to be executed for this process.

8、**CPU Registers:** Indicates various register set of CPU where process need to be stored for execution for running state.

9、**CPU Scheduling Information:** indicates the information of a process with which it uses the CPU time through scheduling.

10、**Memory Management Information:** includes the information of page table, memory limits, Segment table depending on memory used by the operating system.

11、**Accounting Information:** Includes the amount of [CPU](https://en.wikipedia.org/wiki/Central_processing_unit) used for process execution, time limits, execution ID etc.

12、**I/O Status Information:** Includes a list of **I/O devices** allocated to the process.



### Location

Since PCB contains the critical information for the process, it must be kept in an area of memory protected from normal user access. In some operating systems the PCB is placed in the beginning of the kernel [stack](https://en.wikipedia.org/wiki/Call_stack) of the process as it is a convenient protected location.[[4\]](https://en.wikipedia.org/wiki/Process_control_block#cite_note-4)



> NOTE : 显然Wikipedia中，关于process control block的描述是非常不好的，下面是一篇补充文章

## exposnitc.github [Process Table (Process Control Block)](https://exposnitc.github.io/os_design-files/process_table.html)





## `task_struct`

在linux OS中，使用`task_struct`来定义PCB，所以要想完全搞清楚PCB，可以直接阅读它的源代码：

<https://github.com/torvalds/linux/blob/master/include/linux/sched.h>



在[The Life of a Process](https://opensourceforu.com/2016/03/the-life-of-a-process/)中对PCB也有一个比较好的介绍；