# Thread control block

1、在context switch的时候，存放thread state data，比如各种register

## wikipedia [Thread control block](https://en.wikipedia.org/wiki/Thread_control_block)

**Thread Control Block** (**TCB**) is a [data structure](https://en.wikipedia.org/wiki/Data_structure) in the [operating system kernel](https://en.wikipedia.org/wiki/Operating_system_kernel) which contains [thread](https://en.wikipedia.org/wiki/Thread_(computing))-specific information needed to manage it. The TCB is "the manifestation of a thread in an operating system."

An example of information contained within a TCB is:

1、Thread Identifier: Unique id (tid) is assigned to every new thread

2、[Stack pointer](https://en.wikipedia.org/wiki/Stack_pointer): Points to thread's stack in the process

> NOTE: 显然，为了支持multi thread，就需要让每个thread有一个自己的call stack

3、[Program counter](https://en.wikipedia.org/wiki/Program_counter): Points to the current program instruction of the thread

4、State of the thread (running, ready, waiting, start, done)

5、Thread's [register](https://en.wikipedia.org/wiki/Processor_register) values

6、Pointer to the [Process control block](https://en.wikipedia.org/wiki/Process_control_block) (PCB) of the process that the thread lives on

The Thread Control Block acts as a library of information about the [threads](https://en.wikipedia.org/wiki/Thread_(computing)) in a system. Specific information is stored in the **thread control block** highlighting important information about each process.

