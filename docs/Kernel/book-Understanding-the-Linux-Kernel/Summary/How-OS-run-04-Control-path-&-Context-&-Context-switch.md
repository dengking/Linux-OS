# control path

control path这个概念是我由kernel control path启发而创建的，它表示OS中所有可能的活动/执行，之所以创建这个概念，是因为它具备一些特征可以方便我们来统一地、概括地描述问题。

有如下control path：

- kernel control path
- kernel thread
- process

每个control path都有自己的context，它们都会涉及到context switch，因为OS为了高效，肯定会让多个control path interleave（交错运行），就必然需要维护每个control path的context，context其实是一种separation机制，它能够使一个control path在被suspend后，过后能够被resume，其实这是在[How-OS-run-02-kernel-control-path-and-reentrant-kernel](./How-OS-run-02-kernel-control-path-and-reentrant-kernel.md)中提出的reentrant思想。

显然context包括每个control path的private数据，如下：

- call stack



# context switch

执行context switch的目的：[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)

进程是operating system的概念，它是为了实现[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)，以充分利用hardware，在hardware中，并没有进程的概念。

发生context switch的场景：

## Scheduler触发Process Switch

3.3. Process Switch

kernel substitutes one process for another process

## Interrupt Signals触发Switch

4.1. The Role of Interrupt Signals

> the code executed by an interrupt or by an exception handler is not a process. Rather, it is a kernel control path that runs at the expense of the same process that was running when the interrupt occurred



> As a kernel control path, the interrupt handler is lighter than a process (it has less context and requires less time to set up or tear down).

4.3. Nested Execution of Exception and Interrupt Handlers





思考：发生context switch的时候，要把context置于何处呢？