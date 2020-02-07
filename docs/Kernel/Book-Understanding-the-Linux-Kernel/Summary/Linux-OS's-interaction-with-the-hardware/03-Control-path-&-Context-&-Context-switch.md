# Control path

Control path这个概念是我由kernel control path启发而创建的，它表示OS中所有可能的活动/执行流程，之所以创建这个概念，是因为它可以方便我们来统一地、概括地描述问题（一个抽象过程）。

OS中有如下control path：

- kernel control path
- kernel thread
- task（process/thread，现代OS需要支持[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)）

Control path的执行都可能会被interrupted：

- 一旦发生了hardware interrupt，OS kernel会立即去响应，从而interrupt（suspend）当前执行的kernel control path，转去执行新的kernel control path。即原kernel control path会被interrupted。

- task是现代OS为支持[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)而创建的，它由[scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing))进行调度执行的，目前linux采取的调度策略是[Preemptive multitasking](https://en.wikipedia.org/wiki/Preemption_(computing))，这种策略的本质是：

  > It is normally carried out by a [privileged](https://en.wikipedia.org/wiki/Protection_ring) task or part of the system known as a preemptive [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)), which has the power to **preempt**, or interrupt, and later resume, other tasks in the system.

  即它可能会interrupt（suspend）正在执行的task，然后转去执行另外一个task。

显然这是OS为了高效，让多个control path interleave（交错运行），为了实现[Reentrancy](https://en.wikipedia.org/wiki/Reentrancy_(computing)) ，每个control path都要有自己private的context、address space，这其实是一个separation机制。它能够使一个control path在被suspend后，过后能够被resume，其实这是在[How-OS-run-02-kernel-control-path-and-reentrant-kernel](./How-OS-run-02-kernel-control-path-and-reentrant-kernel.md)中提出的reentrant思想。

当它们被interrupted的时候，都会涉及到context switch，因为OS为了高效，肯定会让多个control path interleave（交错运行），就必然需要维护每个control path的context，context其实是一种separation机制，



显然context包括每个control path的private数据，如下：

- call stack



## context switch

执行context switch的目的：[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)

进程是operating system的概念，它是为了实现[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)，以充分利用hardware，在hardware中，并没有进程的概念。

发生context switch的场景：

### Scheduler触发Process Switch

3.3. Process Switch

kernel substitutes one process for another process

### Interrupt Signals触发Switch

4.1. The Role of Interrupt Signals

> the code executed by an interrupt or by an exception handler is not a process. Rather, it is a kernel control path that runs at the expense of the same process that was running when the interrupt occurred



> As a kernel control path, the interrupt handler is lighter than a process (it has less context and requires less time to set up or tear down).

4.3. Nested Execution of Exception and Interrupt Handlers





思考：发生context switch的时候，要把context置于何处呢？