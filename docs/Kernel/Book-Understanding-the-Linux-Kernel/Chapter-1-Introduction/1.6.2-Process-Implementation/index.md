# 1.6.2. Process Implementation

To let the kernel manage processes, each process is represented by a *process descriptor* that
includes information about the current state of the process.

> NOTE: *process descriptor*在3.2. Process Descriptor中进行专门介绍
>
> 本节中的process所指为lightweight process，而不是标准的[Process (computing)](https://en.wikipedia.org/wiki/Process_(computing))

When the kernel stops the execution of a process, it saves the current contents of several processor
registers in the **process descriptor**. These include:

- The program counter (PC) and stack pointer (SP) registers
- The general purpose registers
- The floating point registers
- The processor control registers (Processor Status Word) containing information about the CPU
  state
- The memory management registers used to keep track of the RAM accessed by the process

> NOTE: See also
>
> - [Program counter](https://en.wikipedia.org/wiki/Program_counter)
> - [Stack register](https://en.wikipedia.org/wiki/Stack_register)
> - [Processor register](https://en.wikipedia.org/wiki/Processor_register)

When the kernel decides to resume executing a process, it uses the proper **process descriptor fields**
to load the CPU registers. Because the stored value of the **program counter** points to the instruction
following the last instruction executed, the process resumes execution at the point where it was
stopped.

When a process is not executing on the CPU, it is waiting for some event. Unix kernels distinguish many **wait states**, which are usually implemented by **queues of process descriptors** ; each (possibly
empty) queue corresponds to the set of processes waiting for a specific event.

> NOTE:  参见3.2.4. How Processes Are Organized

