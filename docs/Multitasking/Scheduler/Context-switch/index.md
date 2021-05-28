# Context switch

## wikipedia [Context switch](https://en.wikipedia.org/wiki/Context_switch)

In computing, a **context switch** is the process of storing the state of a [process](https://en.wikipedia.org/wiki/Process_(computing)) or of a [thread](https://en.wikipedia.org/wiki/Thread_(computing)), so that it can be restored and [execution](https://en.wikipedia.org/wiki/Execution_(computing)) resumed from the same point later. This allows multiple processes to share a single [CPU](https://en.wikipedia.org/wiki/CPU), and is an essential feature of a [multitasking operating system](https://en.wikipedia.org/wiki/Multitasking_operating_system).

The precise meaning of the phrase “context switch” varies significantly in usage. In a **multitasking context**, it refers to the process of storing the system state for one task, so that task can be paused and another task resumed. A **context switch** can also occur as the result of an [interrupt](https://en.wikipedia.org/wiki/Interrupt), such as when a task needs to access [disk storage](https://en.wikipedia.org/wiki/Disk_storage), freeing up CPU time for other tasks. Some operating systems also require a context switch to move between [user mode and kernel mode](https://en.wikipedia.org/wiki/User_space) tasks. The process of **context switching** can have a negative impact on system performance, although the size of this effect depends on the nature of the switch being performed.

### Cost

**Context switches** are usually **computationally intensive**（计算密集型的）, and much of the design of operating systems is to optimize the use of **context switches**. Switching from one process to another requires a certain amount of time for doing the administration（管理） – saving and loading **registers** and memory maps, updating various tables and lists, etc. What is actually involved in a context switch varies between these senses and between processors and operating systems. For example, in the [Linux kernel](https://en.wikipedia.org/wiki/Linux_kernel), **context switching** involves switching registers, stack pointer, and [program counter](https://en.wikipedia.org/wiki/Program_counter), but is independent of [address space](https://en.wikipedia.org/wiki/Address_space) switching, though in a process switch an address space switch also happens. Further still, analogous context switching happens between [user threads](https://en.wikipedia.org/wiki/User_thread), notably [green threads](https://en.wikipedia.org/wiki/Green_thread), and is often very light-weight, saving and restoring minimal context. In extreme cases, such as switching between goroutines in [Go](https://en.wikipedia.org/wiki/Go_(programming_language)), a context switch is equivalent to a [coroutine](https://en.wikipedia.org/wiki/Coroutine) yield, which is only marginally（稍微） more expensive than a [subroutine](https://en.wikipedia.org/wiki/Subroutine) call.

> NOTE:
>
> context switch-VS-coroutine yield让渡-VS-function subroutine call

### When to switch

There are three potential triggers for a context switch:

#### Multitasking

Most commonly, within some [scheduling](https://en.wikipedia.org/wiki/Scheduling_(computing)) scheme, one process must be switched out of the CPU so another process can run. This context switch can be triggered by the process making itself unrunnable, such as by waiting for an [I/O](https://en.wikipedia.org/wiki/Input/output) or [synchronization](https://en.wikipedia.org/wiki/Synchronization_(computer_science)) operation to complete. On a [pre-emptive multitasking](https://en.wikipedia.org/wiki/Pre-emptive_multitasking) system, the scheduler may also switch out processes which are still runnable. To prevent other processes from being starved of CPU time, preemptive schedulers often configure a timer interrupt to fire when a process exceeds its [time slice](https://en.wikipedia.org/wiki/Time_slice). This interrupt ensures that the scheduler will gain control to perform a context switch.

#### Interrupt handling

Modern architectures are [interrupt](https://en.wikipedia.org/wiki/Interrupt) driven. This means that if the CPU requests data from a disk, for example, it does not need to [busy-wait](https://en.wikipedia.org/wiki/Busy-wait) until the read is over; it can issue the request and continue with some other execution. When the read is over, the CPU can be *interrupted* and presented with the read. For interrupts, a program called an *interrupt handler* is installed, and it is the interrupt handler that handles the interrupt from the disk.

When an **interrupt** occurs, the hardware automatically switches a part of the context (at least enough to allow the handler to return to the interrupted code). The handler may save additional context, depending on details of the particular hardware and software designs. Often only a minimal part of the context is changed in order to minimize the amount of time spent handling the interrupt. The [kernel](https://en.wikipedia.org/wiki/Kernel_(computing)) does not spawn or schedule a special process to handle interrupts, but instead the handler executes in the (often partial) context established at the beginning of interrupt handling. Once interrupt servicing is complete, the context in effect before the interrupt occurred is restored so that the interrupted process can resume execution in its proper state.

#### User and kernel mode switching

When a transition between [user mode](https://en.wikipedia.org/wiki/User_mode) and [kernel mode](https://en.wikipedia.org/wiki/Kernel_mode) is required in an operating system, a context switch is not necessary; a mode transition is *not* by itself a context switch. However, depending on the operating system, a context switch may also take place at this time.



### Steps

In a switch, the state of process currently executing must be saved somehow, so that when it is rescheduled, this state can be restored.

The process state includes all the registers that the process may be using, especially the [program counter](https://en.wikipedia.org/wiki/Program_counter), plus any other operating system specific data that may be necessary. This is usually stored in a data structure called a *process control block*(PCB) or *switchframe*.

The PCB might be stored on a per-process [stack](https://en.wikipedia.org/wiki/Stack_(data_structure)) in kernel memory (as opposed to the user-mode [call stack](https://en.wikipedia.org/wiki/Call_stack)), or there may be some specific operating system defined data structure for this information. A [handle](https://en.wikipedia.org/wiki/Handle_(computing)) to the PCB is added to a queue of processes that are ready to run, often called the *ready queue*.

Since the operating system has effectively suspended the execution of one process, it can then switch context by choosing a process from the ready queue and restoring its PCB. In doing so, the program counter from the PCB is loaded, and thus execution can continue in the chosen process. Process and thread priority can influence which process is chosen from the ready queue (i.e., it may be a [priority queue](https://en.wikipedia.org/wiki/Priority_queue)).

