# wikipedia [Process state](https://en.wikipedia.org/wiki/Process_state)

In a [multitasking](https://en.wikipedia.org/wiki/Computer_multitasking) [computer](https://en.wikipedia.org/wiki/Computer) system, [processes](https://en.wikipedia.org/wiki/Process_(computing)) may occupy a variety of [states](https://en.wikipedia.org/wiki/State_(computer_science)).  These distinct states may not be recognized as such by the [operating system](https://en.wikipedia.org/wiki/Operating_system) [kernel](https://en.wikipedia.org/wiki/Kernel_(computer_science)). However, they are a useful abstraction for the understanding of processes.

> NOTE：操作系统内核可能并不识别这些状态。

[![img](https://upload.wikimedia.org/wikipedia/commons/thumb/8/83/Process_states.svg/400px-Process_states.svg.png)](https://en.wikipedia.org/wiki/File:Process_states.svg)

The various process states, displayed in a [state diagram](https://en.wikipedia.org/wiki/State_diagram), with arrows indicating possible transitions between states - as can be seen some processes are stored in **main memory** (yellow), and some are stored in **secondary memory** (green).

> NOTE:  : `new`出来的对象是存放在main memory还是存放在secondary memory？

> NOTE:  : main memory，second memory...，显然computer的memory也是分层次的。记得之前总结过，computer science中分层思想。


## Primary process states

The following typical **process states** are possible on computer systems of all kinds.  In most of these states, processes are "stored" on [main memory](https://en.wikipedia.org/wiki/Primary_storage).

### Created

When a process is first created, it occupies the "**created**" or "**new**" state.  In this state, the process awaits admission to the "ready" state.  Admission will be approved or delayed by a long-term, or admission, [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)).  Typically in most [desktop computer](https://en.wikipedia.org/wiki/Desktop_computer) systems, this admission will be approved automatically. However, for [real-time operating systems](https://en.wikipedia.org/wiki/Real-time_operating_system) this admission may be delayed.  In a realtime system, admitting too many processes to the "ready" state may lead to oversaturation(过饱和度) and [overcontention](https://en.wikipedia.org/wiki/Bus_contention)(过度竞争 ) of the system's resources, leading to an inability to meet process deadlines.

### Ready

A "ready" or "waiting" process has been loaded into [main memory](https://en.wikipedia.org/wiki/Primary_storage) and is awaiting execution on a [CPU](https://en.wikipedia.org/wiki/CPU) (to be [context switched](https://en.wikipedia.org/wiki/Context_switch) onto the CPU by the dispatcher, or short-term scheduler).  There may be many "**ready**" processes at any one point of the system's execution—for example, in a **one-processor system**, only one process can be executing at any one time, and all other "concurrently executing" processes will be waiting for execution.

> NOTE:  : ready和waiting是的含义是相同的，在上面的图中，使用的是ready，其实也可以使用waiting的；

A *ready queue* or [run queue](https://en.wikipedia.org/wiki/Run_queue) is used in [computer scheduling](https://en.wikipedia.org/wiki/Scheduling_(computing)).  Modern computers are capable of running many different programs or processes at the same time.  However, the **CPU** is only capable of handling one process at a time(一个CPU/CORE同一时刻只能够执行一个process).  Processes that are ready for the CPU are kept in a [queue](https://en.wikipedia.org/wiki/Queue_(data_structure)) for "ready" processes.  Other processes that are waiting for an **event** to occur, such as loading information from a hard drive or waiting on an internet connection, are not in the **ready queue**.

> NOTE: 进程的执行也是靠even驱动的，所以当这个even没有occur的时候，进程就只能够wait的。

### Running

A process moves into the **running state** when it is chosen for execution. The process's instructions are executed by one of the CPUs (or cores) of the system. There is at most one running process per [CPU](https://en.wikipedia.org/wiki/CPU) or core. A process can run in either of the two modes, namely *kernel mode* or *user mode*.[[1\]](https://en.wikipedia.org/wiki/Process_state#cite_note-1)[[2\]](https://en.wikipedia.org/wiki/Process_state#cite_note-2)

> NOTE: There is at most one running process per [CPU](https://en.wikipedia.org/wiki/CPU) or core.这句话是非常重要的。

#### Kernel mode

1、Processes in kernel mode can access both: kernel and user addresses.

2、Kernel mode allows unrestricted access to hardware including execution of *privileged* instructions.

3、Various instructions (such as [I/O](https://en.wikipedia.org/wiki/I/O) instructions and halt instructions) are *privileged* and can be executed only in kernel mode.

4、A [system call](https://en.wikipedia.org/wiki/System_call) from a user program leads to a switch to **kernel mode**.

#### User mode

1、Processes in **user mode** can access their own instructions and data but not kernel instructions and data (or those of other processes).

2、When the computer system is executing on behalf of a **user application**, the system is in user mode. However, when a user application requests a service from the [operating system](https://en.wikipedia.org/wiki/Operating_system) (via a [system call](https://en.wikipedia.org/wiki/System_call)), the system must transition from **user** to **kernel mode** to fulfill the request.

3、User mode avoids various catastrophic failures:

- There is an isolated [virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space) for each process in **user mode**.
- **User mode** ensures isolated execution of each process so that it does not affect other processes as such.
- No direct access to any hardware device is allowed.

> NOTE: 显然，计算机系统也是按照**隔离原则**来进行设计的。

### Blocked

A process transitions to a [blocked](https://en.wikipedia.org/wiki/Blocking_(computing)) state when it cannot carry on without an external change in state or event occurring. 

For example, a process may block on a call to an I/O device such as a printer, if the printer is not available. 

> NOTE: I/O可能导致进程blocked

Processes also commonly block when they require user input, or require  access to a **critical section** which must be executed atomically. Such **critical sections** are protected using a **synchronization object** such as a **semaphore** or **mutex**.

> NOTE:  : 根据上面的state diagram来看，当一个process被blocked的时候，它**可能**会被swap out到secondary memory，也就是此时它不会被执行了。

> NOTE:  : 在I/O system call中，就有non blocking I/O

> NOTE:  : OS必须要为每个process维护它所等待的event，以便当这个event到来的时候，能够调度这个process让它开始执行；在[Process control block](<https://en.wikipedia.org/wiki/Process_control_block>) 中的**The process scheduling state**中提及，

> Also, in case of a suspended process, event identification data must be recorded for the event the process is waiting for



### Terminated

> Main article: [Zombie process](https://en.wikipedia.org/wiki/Zombie_process)

A process may be [terminated](https://en.wikipedia.org/wiki/Exit_(system_call)), either from the "running" state by completing its execution or by explicitly being killed. In either of these cases, the process moves to the "terminated" state. 

The underlying program is no longer executing, but the process remains in the [process table](https://en.wikipedia.org/wiki/Process_table) as a *zombie process* until its parent process calls the `wait` [system call](https://en.wikipedia.org/wiki/System_call) to read its [exit status](https://en.wikipedia.org/wiki/Exit_status), at which point the process is removed from the **process table**, finally ending the process's lifetime. If the parent fails to call `wait`, this continues to consume the **process table entry** (concretely the [process identifier](https://en.wikipedia.org/wiki/Process_identifier) or PID), and causes a [resource leak](https://en.wikipedia.org/wiki/Resource_leak).

> NOTE:  : 关于`wait` system call，可以参见APUE chapter 8.6

## Additional process states

Two additional states are available for processes in systems that support [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory).  In both of these states, processes are "stored" on **secondary memory** (typically a [hard disk](https://en.wikipedia.org/wiki/Hard_disk)).

> NOTE：computer的memory也是hierarchy的，有main memory，secondary memory。

### Swapped out and waiting

(Also called **suspended and waiting**.) In systems that support **virtual memory**, a process may be swapped out, that is, removed from **main memory** and placed on external storage by the scheduler.  From here the process may be swapped back into the **waiting state**.

### Swapped out and blocked

(Also called **suspended and blocked**.) Processes that are blocked may also be swapped out.  In this event the process is both **swapped out and blocked**, and may be swapped back in again under the same circumstances as a **swapped out and waiting** process (although in this case, the process will move to the blocked state, and may still be waiting for a resource to become available).


