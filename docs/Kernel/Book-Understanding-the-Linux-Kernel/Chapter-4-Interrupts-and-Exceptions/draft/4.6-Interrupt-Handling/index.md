# 4.6. Interrupt Handling

As we explained earlier, most **exceptions** are handled simply by sending a **Unix signal** to the process that caused the exception. The action to be taken is thus deferred until the process receives the signal; as a result, the kernel is able to process the **exception** quickly.

This approach does not hold for **interrupts**, because they frequently arrive long after the process to which they are related (for instance, a process that requested a data transfer) has been **suspended** and a completely unrelated process is running. So it would make no sense to send a **Unix signal** to the **current process**.

**Interrupt handling** depends on the type of interrupt. For our purposes, we'll distinguish three main classes of interrupts:

***I/O interrupts***

An **I/O device** requires attention; the corresponding **interrupt handler** must query the device to determine the proper course of action. We cover this type of interrupt in the later section "I/O Interrupt Handling."

***Timer interrupts***

Some timer, either a local **APIC timer** or an **external timer**, has issued an interrupt; this kind of **interrupt** tells the **kernel** that a fixed-time interval has elapsed. These **interrupts** are handled mostly as I/O interrupts; we discuss the peculiar characteristics of timer interrupts in Chapter 6.

***Interprocessor interrupts***

A CPU issued an interrupt to another CPU of a multiprocessor system. We cover such interrupts in the later section "Interprocessor Interrupt Handling."

## 4.6.1. I/O Interrupt Handling

In general, an **I/O interrupt handler** must be flexible enough to service several devices at the same time. In the PCI bus architecture, for instance, several devices may share the same **IRQ line**. This means that the **interrupt vector** alone does not tell the whole story. In the example shown in Table 4-3, the same vector 43 is assigned to the USB port and to the sound card. However, some hardware devices found in older PC architectures (such as ISA) do not reliably operate if their **IRQ line** is shared with other devices.

**Interrupt handler flexibility** is achieved in two distinct ways, as discussed in the following list.



### 4.6.1.1. Interrupt vectors



### 4.6.1.2. IRQ data structures



### 4.6.1.3. IRQ distribution in multiprocessor systems



### 4.6.1.4. Multiple Kernel Mode stacks

As mentioned in the section "Identifying a Process" in Chapter 3, the  `thread_info` descriptor of each process is coupled with a Kernel Mode stack in a  `thread_union` data structure composed by one or two page frames, according to an option selected when the kernel has been compiled. If the size of the  `thread_union` structure is 8 KB, the Kernel Mode stack of the current process is used for every type of **kernel control path**: **exceptions**, **interrupts**, and **deferrable functions** (see the later section "Softirqs and Tasklets"). Conversely, if the size of the  `thread_union` structure is 4 KB, the kernel makes use of three types of Kernel Mode stacks:

- The exception stack is used when handling exceptions (including system calls). This is the stack contained in the per-process  `thread_union` data structure, thus the kernel makes use of a different exception stack for each process in the system.
- The *hard IRQ stack* is used when handling interrupts. There is one hard IRQ stack for each CPU in the system, and each stack is contained in a single page frame.
- The *soft IRQ stack* is used when handling deferrable functions (softirqs or tasklets; see the later section "Softirqs and Tasklets"). There is one soft IRQ stack for each CPU in the system, and each stack is contained in a single page frame.

All hard IRQ stacks are contained in the  `hardirq_stack` array, while all soft IRQ stacks are contained in the  `softirq_stack` array. Each array element is a union of type  `irq_ctx` that span a single page. At the bottom of this page is stored a  thread_info structure, while the spare memory locations are used for the stack; remember that each stack grows towards lower addresses. Thus, hard IRQ stacks and soft IRQ stacks are very similar to the exception stacks described in the section "Identifying a  Process" in Chapter 3; the only difference is that the  tHRead_info structure coupled with each stack is associated with a CPU rather than a process.

The  `hardirq_ctx` and  `softirq_ctx` arrays allow the kernel to quickly determine the hard IRQ stack and soft IRQ stack of a given CPU, respectively: they contain pointers to the corresponding  `irq_ctx` elements.



### 4.6.1.5. Saving the registers for the interrupt handler

When a CPU receives an interrupt, it starts executing the code at the address found in the corresponding gate of the IDT (see the earlier section "Hardware Handling of Interrupts and Exceptions").

As with other context switches, the need to save registers leaves the kernel developer with a somewhat messy coding job, because the registers have to be saved and restored using assembly language code. However, within those operations, the processor is expected to call and return from a C function. In this section, we describe the assembly language task of handling registers; in the next, we show some of the acrobatics（技巧） required in the C function that is subsequently invoked.

Saving registers is the first task of the **interrupt handler**. As already mentioned, the address of the **interrupt handler** for IRQ n is initially stored in the  `interrupt[n] entry` and then copied into the interrupt gate included in the proper IDT entry.

The  `interrupt` array is built through a few assembly language instructions in the `arch/i386/kernel/entry.S` file. The array includes  `NR_IRQS` elements, where the  `NR_IRQS` macro yields either the number 224 if the kernel supports a recent I/O APIC chip, [`*`] or the number 16 if the kernel uses the older 8259A PIC chips. The element at index n in the array stores the address of the following two assembly language instructions:

> [`*`] 256 vectors is an architectural limit for the 80x86 architecture. 32 of them are used or reserved for the CPU, so the usable vector space consists of 224 vectors.

```assembly
pushl $n-256
jmp common_interrupt
```

The result is to save on the stack the IRQ number associated with the interrupt minus 256. The kernel represents all IRQs through negative numbers, because it reserves positive interrupt numbers to identify **system calls** (see Chapter 10). The same code for all **interrupt handlers** can then be executed while referring to this number. The common code starts at label  `common_interrupt` and consists of the following assembly language macros and instructions:

```assembly
common_interrupt:
SAVE_ALL
movl %esp,%eax
call do_IRQ
jmp ret_from_intr
```

The  `SAVE_ALL` macro expands to the following fragment:

```assembly
cld
push %es
push %ds
pushl %eax
pushl %ebp
pushl %edi
pushl %esi
pushl %edx
pushl %ecx
pushl %ebx
movl $ _ _USER_DS,%edx
movl %edx,%ds
movl %edx,%es
```

`SAVE_ALL` saves all the CPU registers that may be used by the interrupt handler on the stack, except for  `eflags` ,  `cs` ,  `eip` ,  `ss` , and  `esp` , which are already saved automatically by the control unit (see the 
earlier section "Hardware Handling of Interrupts and Exceptions"). The macro then loads the selector of the user data segment into  `ds` and  `es` .

After saving the registers, the address of the current top stack location is saved in the  `eax` register; then, the interrupt handler invokes the  `do_IRQ( )` function. When the  `ret` instruction of  `do_IRQ( )` is executed (when that function terminates) control is transferred to  `ret_from_intr( )` (see the later
section "Returning from Interrupts and Exceptions").

### 4.6.1.6. The `do_IRQ( )` function



### 4.6.1.7. The `__do_IRQ( )` function



### 4.6.1.8. Reviving a lost interrupt



### 4.6.1.9. Interrupt service routines



### 4.6.1.10. Dynamic allocation of IRQ lines