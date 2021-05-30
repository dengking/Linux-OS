# wikipedia [Signal (IPC)](https://en.wikipedia.org/wiki/Signal_(IPC))

> NOTE: 
>
> 它将signal看做是一种IPC

**Signals** are a limited form of [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication) (IPC), typically used in [Unix](https://en.wikipedia.org/wiki/Unix), [Unix-like](https://en.wikipedia.org/wiki/Unix-like), and other [POSIX](https://en.wikipedia.org/wiki/POSIX)-compliant operating systems. A signal is an [asynchronous](https://en.wiktionary.org/wiki/asynchronous) notification sent to a [process](https://en.wikipedia.org/wiki/Process_(computing)) or to a specific [thread](https://en.wikipedia.org/wiki/Thread_(computer_science)) within the same process in order to notify it of an event that occurred. Signals originated in 1970s [Bell Labs](https://en.wikipedia.org/wiki/Bell_Labs) Unix and have been more recently specified in the [POSIX](https://en.wikipedia.org/wiki/POSIX) standard.

When a signal is sent, the operating system interrupts the target process' normal [flow of execution](https://en.wikipedia.org/wiki/Control_flow) to deliver the signal. Execution can be interrupted during any [non-atomic instruction](https://en.wikipedia.org/wiki/Atomic_operation). If the process has previously registered a **signal handler**, that routine is executed. Otherwise, the default signal handler is executed.

> NOTE:
>
> **signal handler**，就涉及到reentrancy了

Embedded programs may find signals useful for interprocess communications, as the computational and memory footprint for signals is small.

Signals are similar to [interrupts](https://en.wikipedia.org/wiki/Interrupt), the difference being that interrupts are mediated by the processor and handled by the [kernel](https://en.wikipedia.org/wiki/Kernel_(operating_system)) while signals are mediated by the kernel (possibly via system calls) and handled by processes. The kernel may pass an **interrupt** as a **signal** to the process that caused it (typical examples are [SIGSEGV](https://en.wikipedia.org/wiki/SIGSEGV), [SIGBUS](https://en.wikipedia.org/wiki/SIGBUS), [SIGILL](https://en.wikipedia.org/wiki/Signal_(IPC)#SIGILL) and [SIGFPE](https://en.wikipedia.org/wiki/Signal_(IPC)#SIGFPE)).

