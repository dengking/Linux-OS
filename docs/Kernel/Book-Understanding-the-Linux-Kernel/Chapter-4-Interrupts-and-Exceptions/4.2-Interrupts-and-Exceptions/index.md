# 4.2. Interrupts and Exceptions

The Intel documentation classifies interrupts and exceptions as follows:

## Interrupts:

### Maskable interrupts

All Interrupt Requests (IRQs) issued by **I/O devices** give rise to **maskable interrupts** . A **maskable interrupt** can be in two states: masked or unmasked; a masked interrupt is ignored by the **control unit** as long as it remains masked.

### Nonmaskable interrupts

Only a few critical events (such as hardware failures) give rise to **nonmaskable interrupts**. Nonmaskable interrupts are always recognized by the CPU.

## Exceptions:	

> NOTE: 需要注意的是，Intel将exception分为两类：
>
> - Processor-detected exceptions
> - Programmed exceptions

### Processor-detected exceptions

Generated when the CPU detects an anomalous（异常的） condition while executing an instruction. These are further divided into three groups, depending on the value of the  `eip` register that is saved on the **Kernel Mode stack** when the CPU control unit raises the exception.

#### Faults

Can generally be corrected; once corrected, the program is allowed to restart with no loss of continuity. The saved value of  `eip` is the address of the **instruction** that caused the **fault**, and hence that instruction can be resumed when the **exception handler** terminates. As we'll see in the section "Page Fault Exception Handler" in Chapter 9, resuming the same instruction is necessary whenever the **handler** is able to correct the anomalous condition that caused the exception.

> NOTE: 结合缺页中断，这个是非常容易理解的。

#### Traps

Reported immediately following the execution of the **trapping instruction**; after the kernel returns control to the program, it is allowed to continue its execution with no loss of continuity. The saved value of  `eip` is the address of the instruction that should be executed after the one that caused the trap. A trap is triggered only when there is no need to reexecute the instruction that terminated. The main use of **traps** is for **debugging** purposes. The role of the **interrupt signal** in this case is to notify the debugger that a specific instruction has been executed (for instance, a **breakpoint** has been reached within a program). Once the user has examined the data provided by the debugger, she may ask that execution of the debugged program resume, starting from the next instruction.

> NOTE: see also：[Traps](https://en.wikipedia.org/wiki/Trap_(computing))

#### Aborts

A serious error occurred; the control unit is in trouble, and it may be unable to store in the  `eip` register the precise location of the instruction causing the exception. Aborts are used to report **severe errors**, such as **hardware failures** and invalid or inconsistent values in system tables. The **interrupt signal** sent by the **control unit** is an **emergency signal** used to switch control to the corresponding **abort exception handler**. This handler has no choice but to force the affected process to terminate.



### Programmed exceptions

Occur at the request of the programmer. They are triggered by  `int` or  `int3` instructions; the  `into` (check for overflow) and  `bound` (check on address bound) instructions also give rise to a **programmed exception** when the condition they are checking is not true. **Programmed exceptions** are handled by the **control unit** as **traps**; they are often called ***software interrupts*** . Such exceptions have two common uses: to implement **system calls** and to notify a **debugger** of a specific event (see Chapter 10).

> NOTE: 关于`int`、`int3`、`into`、`bound`，参见工程[Hardware](https://dengking.github.io/Hardware/)的文章[INT](https://dengking.github.io/Hardware/CPU/Intel/X86-instruction/INT/)。



Each interrupt or exception is identified by a number ranging from 0 to 255; Intel calls this 8-bit unsigned number a vector. The vectors of nonmaskable interrupts and exceptions are fixed, while those of maskable interrupts can be altered by programming the **Interrupt Controller** (see the next section).



## 4.2.1. IRQs and Interrupts

> NOTE:
>
> [Interrupt request (PC architecture)](https://en.wikipedia.org/wiki/Interrupt_request_(PC_architecture))
>
> [Programmable interrupt controller](https://en.wikipedia.org/wiki/Programmable_interrupt_controller)
>
> [Interrupt vector table](https://en.wikipedia.org/wiki/Interrupt_vector_table)

## 4.2.2. Exceptions

The 80x86 microprocessors issue roughly 20 different exceptions . `[*]` The kernel must provide a dedicated **exception handler** for each exception type. For some exceptions, the CPU control unit also generates a **hardware error code** and pushes it on the **Kernel Mode stack** before starting the **exception handler**.

>`[*]` The exact number depends on the processor model.

The following list gives the vector, the name, the type, and a brief description of the exceptions found in 80x86 processors. Additional information may be found in the Intel technical documentation.

### 0 - "Divide error" (fault)

Raised when a program issues an integer division by 0.

### 1- "Debug" (trap or fault)

Raised when the  `TF` flag of  `eflags` is set (quite useful to implement single-step execution of a debugged program) or when the address of an instruction or operand falls within the range of an active debug register (see the section "Hardware Context" in Chapter 3).

> NOTE: 关于`TF`， 参见参见工程[Hardware](https://dengking.github.io/Hardware/)的文章[FLAGS-register](https://dengking.github.io/Hardware/CPU/Intel/Register/FLAGS-register/)。

### 2 - Not used

Reserved for nonmaskable interrupts (those that use the NMI pin).

### 3 - "Breakpoint" (trap)

Caused by an  `int3` (breakpoint) instruction (usually inserted by a debugger).

> NOTE: 关于`int3`，参见参见工程[Hardware](https://dengking.github.io/Hardware/)的文章[INT](https://dengking.github.io/Hardware/CPU/Intel/X86-instruction/INT/)。

### 4 - "Overflow" (trap)

An  `into` (check for overflow) instruction has been executed while the  OF (overflow) flag of `eflags` is set.

> NOTE: 关于`into`，参见参见工程[Hardware](https://dengking.github.io/Hardware/)的文章[INT](https://dengking.github.io/Hardware/CPU/Intel/X86-instruction/INT/)。

### 5 - "Bounds check" (fault)

A  `bound` (check on address bound) instruction is executed with the operand outside of the valid address bounds.

> NOTE: 关于`bound`，参见工程[Hardware](https://dengking.github.io/Hardware/)的文章[Bound](https://dengking.github.io/Hardware/CPU/Intel/X86-instruction/Bound/)。

### 6 - "Invalid opcode" (fault)

The CPU execution unit has detected an invalid opcode (the part of the machine instruction that determines the operation performed).

### 7 - "Device not available" (fault)

An ESCAPE, MMX, or SSE/SSE2 instruction has been executed with the  TS flag of  `cr0` set (see the section "Saving and Loading the FPU, MMX, and XMM Registers" in Chapter 3).

### 9 - "Coprocessor segment overrun" (abort)

Problems with the external mathematical coprocessor (applies only to old 80386 microprocessors).

### 10 - "Invalid TSS" (fault)

The CPU has attempted a context switch to a process having an invalid Task State Segment.

### 11 - "Segment not present" (fault)

A reference was made to a segment not present in memory (one in which the  `Segment-Present` flag of the Segment Descriptor was cleared).

### 12 - "Stack segment fault" (fault)

The instruction attempted to exceed the stack segment limit, or the segment identified by  `ss` is not present in memory.

### 13 - "General protection" (fault)

One of the protection rules in the protected mode of the 80x86 has been violated.

### 14 - "Page Fault" (fault)

The addressed page is not present in memory, the corresponding Page Table entry is null, or a violation of the paging protection mechanism has occurred.

### 15 - Reserved by Intel

### 16 - "Floating-point error" (fault)

The floating-point unit integrated into the CPU chip has signaled an error condition, such as numeric overflow or division by 0. [`*`]
[`*`] The 80 x 86 microprocessors also generate this exception when performing a signed division whose result cannot be stored as a signed integer (for instance, a division between -2,147,483,648 and -1).

### 17 - "Alignment check" (fault)

The address of an operand is not correctly aligned (for instance, the address of a long integer is not a multiple of 4).

### 18 - "Machine check" (abort)

A machine-check mechanism has detected a CPU or bus error. 

### 19 - "SIMD floating point exception" (fault)

The SSE or SSE2 unit integrated in the CPU chip has signaled an error condition on a floating-point operation.

The values from 20 to 31 are reserved by Intel for future development. As illustrated in Table 4-1, each **exception** is handled by a specific **exception handler** (see the section "Exception Handling" later in this chapter), which usually sends a Unix signal to the process that caused the exception.

Table 4-1. Signals sent by the exception handlers

| #    | Exception                   | Exception handler                | Signal  |
| ---- | --------------------------- | -------------------------------- | ------- |
| 0    | Divide error                | `divide_error( )`                | SIGFPE  |
| 1    | Debug                       | `debug( )`                       | SIGTRAP |
| 2    | NMI                         | `nmi( )`                         | None    |
| 3    | Breakpoint                  | `int3( )`                        | SIGTRAP |
| 4    | Overflow                    | `overflow( )`                    | SIGSEGV |
| 5    | Bounds check                | `bounds( )`                      | SIGSEGV |
| 6    | Invalid opcode              | `invalid_op( )`                  | SIGILL  |
| 7    | Device not available        | `device_not_available( )`        | None    |
| 8    | Double fault                | `doublefault_fn( )`              | None    |
| 9    | Coprocessor segment overrun | `coprocessor_segment_overrun( )` | SIGFPE  |
| 10   | Invalid TSS                 | `invalid_TSS( )`                 | SIGSEGV |
| 11   | Segment not present         | `segment_not_present( )`         | SIGBUS  |
| 12   | Stack segment fault         | `stack_segment( )`               | SIGBUS  |
| 13   | General protection          | `general_protection( )`          | SIGSEGV |
| 14   | Page Fault                  | `page_fault( )`                  | SIGSEGV |
| 15   | Intel-reserved              | None                             | None    |
| 16   | Floating-point error        | `coprocessor_error( )`           | SIGFPE  |
| 17   | Alignment check             | `alignment_check( )`             | SIGBUS  |
| 18   | Machine check               | `machine_check( )`               | None    |
| 19   | SIMD floating point         | `simd_coprocessor_error( )`      | SIGFPE  |

## 4.2.3. Interrupt Descriptor Table

>  NOTE:
>
> [Interrupt descriptor table](https://en.wikipedia.org/wiki/Interrupt_descriptor_table)

A system table called Interrupt Descriptor Table (IDT ) associates each interrupt or exception vector with the address of the corresponding interrupt or exception handler. The IDT must be properly initialized before the kernel enables interrupts.

## 4.2.4. Hardware Handling of Interrupts and Exceptions

We now describe how the CPU **control unit** handles interrupts and exceptions. We assume that the kernel has been initialized, and thus the CPU is operating in **Protected Mode**.

After executing an instruction, the  `cs` and  `eip` pair of registers contain the logical address of the next instruction to be executed. Before dealing with that instruction, the control unit checks whether an interrupt or an exception occurred while the **control unit** executed the previous instruction. If one occurred, the **control unit** does the following:

1、 Determines the vector i (0 <= i <= 255) associated with the interrupt or the exception、 
2、 Reads the `i` th entry of the IDT referred by the  `idtr` register (we assume in the following description that the entry contains an interrupt or a trap gate)、
3、 Gets the base address of the GDT from the  `gdtr` register and looks in the GDT to read the Segment Descriptor identified by the selector in the IDT entry、 This descriptor specifies the base address of the segment that includes the interrupt or exception handler、
4、 Makes sure the interrupt was issued by an authorized source、 First, it compares the Current Privilege Level (CPL), which is stored in the two least significant bits of the  `cs` register, with the Descriptor Privilege Level (DPL ) of the Segment Descriptor included in the GDT、 Raises a "General protection " exception if the CPL is lower than the DPL, because the **interrupt handler** cannot have a lower privilege than the program that caused the interrupt、 For **programmed exceptions**, makes a further security check: compares the CPL with the DPL of the gate descriptor included in the IDT and raises a "General protection" exception if the DPL is lower than the CPL、 This last check makes it possible to prevent access by user applications to specific trap or interrupt gates、
5、 Checks whether a change of privilege level is taking place that is, if CPL is different from the selected Segment Descriptor's DPL、 If so, the control unit must start using the stack that is associated with the new privilege level、 It does this by performing the following steps:
   - Reads the  `tr` register to access the TSS segment of the running process、 
   - Loads the  `ss` and  `esp` registers with the proper values for the **stack segment** and **stack pointer** associated with the new privilege level、 These values are found in the TSS (see the section "Task State Segment" in Chapter 3)、
   - In the new stack, it saves the previous values of  `ss` and  `esp` , which define the logical address of the stack associated with the old privilege level、

6、 If a fault has occurred, it loads  `cs` and  `eip` with the logical address of the instruction that caused the exception so that it can be executed again、
  
7、 Saves the contents of  `eflags` ,  `cs` , and  `eip` in the stack、 
8、 If the exception carries a hardware error code, it saves it on the stack、 
9、 Loads  `cs` and  `eip` , respectively, with the Segment Selector and the Offset fields of the Gate Descriptor stored in the i th entry of the IDT、 These values define the logical address of the first  instruction of the interrupt or exception handler、

The last step performed by the **control unit** is equivalent to a jump to the interrupt or exception handler. In other words, the instruction processed by the **control unit** after dealing with the interrupt signal is the first instruction of the selected handler.

After the interrupt or exception is processed, the corresponding handler must relinquish control to the interrupted process by issuing the  `iret` instruction, which forces the control unit to:

1、 Load the  `cs` ,  `eip` , and  `eflags` registers with the values saved on the stack、 If a hardware error code has been pushed in the stack on top of the  `eip` contents, it must be popped before executing  `iret` 、    
2、 Check whether the CPL of the handler is equal to the value contained in the two least significant bits of  `cs` (this means the interrupted process was running at the same privilege level as the handler)、 If so,  `iret` concludes execution; otherwise, go to the next step、
3、 Load the  `ss` and  `esp` registers from the stack and return to the stack associated with the old privilege level、
4、 Examine the contents of the  `ds` ,  `es` ,  `fs` , and  `gs` segment registers; if any of them contains a selector that refers to a Segment Descriptor whose DPL value is lower than CPL, clear the corresponding segment register. The control unit does this to forbid User Mode programs that run with a CPL equal to 3 from using segment registers previously used by kernel routines (with a DPL equal to 0). If these registers were not cleared, malicious User Mode programs could exploit them in order to access the kernel address space.