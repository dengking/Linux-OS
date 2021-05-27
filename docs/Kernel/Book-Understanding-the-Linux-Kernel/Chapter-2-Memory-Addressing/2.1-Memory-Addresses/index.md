# 2.1. Memory Addresses

Programmers casually refer to a ***memory address*** as the way to access the contents of a memory cell. But when dealing with 80 x 86 microprocessors, we have to distinguish three kinds of addresses:

## ***Logical address***

Included in the machine language instructions to specify the address of an operand or of an instruction. This type of address embodies the well-known 80 x 86 segmented architecture that forces MS-DOS and Windows programmers to divide their programs into segments . Each **logical address** consists of a **segment** and an **offset** (or displacement) that denotes the distance from the start of the segment to the actual address.

## ***Linear address*** (also known as ***virtual address***)

A single 32-bit unsigned integer that can be used to address up to 4 GB that is, up to 4,294,967,296 memory cells. Linear addresses are usually represented in hexadecimal notation; their values range from  `0x00000000` to  `0xffffffff` .

> NOTE: 每个process都一个独立的[Virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space)，从上面这段话是否可以推断出每个process的virtual address space的address value range是否一致；参见这篇文章[In virtual memory, can two different processes have the same address?](https://stackoverflow.com/questions/3552633/in-virtual-memory-can-two-different-processes-have-the-same-address)

## ***Physical address***

Used to address memory cells in memory chips. They correspond to the **electrical signals** sent along the address pins of the microprocessor to the **memory bus**. Physical addresses are represented as 32-bit or 36-bit unsigned integers.

The **Memory Management Unit** (`MMU`) transforms a **logical address** into a **linear address** by means of a hardware circuit called a **segmentation unit** ; subsequently, a second hardware circuit called a **paging unit** transforms the **linear address** into a **physical address** (see Figure 2-1).

![Figure 2-1. Logical address translation](./Figure-2-1-Logical-address-translation.jpg)





In multiprocessor systems, all CPUs usually share the same memory; this means that RAM chips may be accessed **concurrently** by independent CPUs. Because read or write operations on a RAM chip must be performed serially, a hardware circuit called a ***memory arbiter*** is inserted between the bus and every RAM chip. Its role is to grant access to a CPU if the chip is free and to delay it if the chip is busy servicing a request by another processor. Even uniprocessor systems use **memory arbiters** , because they include specialized processors called ***DMA controllers*** that operate concurrently with the CPU (see the section "Direct Memory Access (DMA)" in Chapter 13). In the case of multiprocessor systems, the structure of the arbiter is more complex because it has more input ports. The dual Pentium, for instance, maintains a two-port arbiter at each chip entrance and requires that the two CPUs exchange synchronization messages before attempting to use the common bus. From the programming point of view, the arbiter is hidden because it is managed by hardware circuits.