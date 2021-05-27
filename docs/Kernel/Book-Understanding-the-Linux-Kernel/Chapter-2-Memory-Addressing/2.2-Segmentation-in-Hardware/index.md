# 2.2. Segmentation in Hardware

Starting with the 80286 model, Intel microprocessors perform **address translation** in two different
ways called ***real mode*** and ***protected mode*** . We'll focus in the next sections on **address translation**
when **protected mode** is enabled. **Real mode** exists mostly to maintain processor compatibility with
older models and to allow the operating system to **bootstrap** (see Appendix A for a short description
of real mode).

## 2.2.1. Segment Selectors and Segmentation Registers

A **logical address** consists of two parts: a **segment identifier** and an **offset** that specifies the relative
address within the segment. The **segment identifier** is a 16-bit field called the ***Segment Selector*** (see
Figure 2-2), while the offset is a 32-bit field. We'll describe the fields of Segment Selectors in the
section "Fast Access to Segment Descriptors" later in this chapter.

***SUMMARY*** : 从上面的介绍来看，地址的长度是：16 + 32 = 48

***SUMMARY*** : 从图中可以看出，Segment Selector除了包含有table index之外，还包含有其他的信息；

To make it easy to retrieve **segment selectors** quickly, the processor provides segmentation registers
whose only purpose is to hold Segment Selectors; these registers are called  `cs` ,  `ss` ,  `ds` ,  `es` ,  `fs` , and
`gs` . Although there are only six of them, a program can reuse the same segmentation register for
different purposes by saving its content in memory and then restoring it later.

Three of the six segmentation registers have specific purposes:

`cs`

The code segment register, which points to a segment containing program instructions

`ss`

The stack segment register, which points to a segment containing the current program stack

`ds`

The data segment register, which points to a segment containing global and static data



The remaining three **segmentation registers** are general purpose and may refer to arbitrary data
segments.

The  `cs` register has another important function: it includes a 2-bit field that specifies the **Current
Privilege Level** (CPL) of the CPU. The value `0` denotes the highest privilege level, while the value `3`
denotes the lowest one. Linux uses only levels 0 and 3, which are respectively called ***Kernel Mode*** and ***User Mode***.

## 2.2.2. Segment Descriptors

Each segment is represented by an 8-byte ***Segment Descriptor*** that describes the segment
characteristics. Segment Descriptors are stored either in the ***Global Descriptor Table (`GDT` )*** or in the
***Local Descriptor Table(`LDT`)***.

Usually only one `GDT` is defined, while each process is permitted to have its own `LDT` if it needs to
create additional segments besides those stored in the `GDT`. The address and size of the `GDT` in
main memory are contained in the  `gdtr` control register, while the address and size of the currently
used `LDT` are contained in the  `ldtr` control register.

Figure 2-3 illustrates the format of a **Segment Descriptor**; the meaning of the various fields is
explained in Table 2-1.

Table 2-1. Segment Descriptor fields

| Field name | Description                                                  |
| ---------- | ------------------------------------------------------------ |
| `Base`     | Contains the **linear address** of the first byte of the segment. |
| `G`        | `Granularity flag`: if it is cleared (equal to 0), the segment size is expressed in bytes;<br/>otherwise, it is expressed in multiples of 4096 bytes. |
| `Limit`    | Holds the offset of the last memory cell in the segment, thus binding the segment length. When  G is set to 0, the size of a segment may vary between 1 byte and 1 MB; otherwise, it may vary between 4 KB and 4 GB. |
| `S`        | `System flag`: if it is cleared, the segment is a system segment that stores critical data structures such as the **Local Descriptor Table**; otherwise, it is a normal code or data segment. |
| `Type`     | Characterizes the segment type and its access rights (see the text that follows this table). |
| `DPL`      | Descriptor Privilege Level: used to restrict accesses to the segment. It represents the<br/>minimal CPU privilege level requested for accessing the segment. Therefore, a segment<br/>with its `DPL` set to 0 is accessible only when the `CPL` is 0 that is, in Kernel Mode while a<br/>segment with its `DPL` set to 3 is accessible with every CPL value. |
| `P`        | Segment-Present flag : is equal to 0 if the segment is not stored currently in main<br/>memory. Linux always sets this flag (bit 47) to 1, because it never swaps out whole<br/>segments to disk. |
|            |                                                              |
|            |                                                              |

There are several types of segments, and thus several types of **Segment Descriptors**. The following
list shows the types that are widely used in Linux.

***Code Segment Descriptor***

Indicates that the Segment Descriptor refers to a code segment; it may be included either in
the `GDT` or in the `LDT`. The descriptor has the  S flag set (non-system segment).

***Data Segment Descriptor***

Indicates that the Segment Descriptor refers to a **data segment**; it may be included either in the `GDT` or in the `LDT`. The descriptor has the  `S` flag set. **Stack segments** are implemented by means of generic data segments.

***Task State Segment Descriptor (TSSD)***

Indicates that the Segment Descriptor refers to a Task State Segment (TSS) that is, a segment used to save the contents of the processor registers (see the section "Task State Segment" in Chapter 3); it can appear only in the GDT. The corresponding  Type field has the value 11 or 9, depending on whether the corresponding process is currently executing on a CPU. The  S flag of such descriptors is set to 0.

***SUMMARY*** : 需要注意的是，没有stack segment descriptor；根据第2.3章的内容来看，这是因为stack segment是 inside data segment的；

## 2.2.3. Fast Access to Segment Descriptors

We recall that logical addresses consist of a 16-bit Segment Selector and a 32-bit Offset, and that
segmentation registers store only the Segment Selector.

To speed up the translation of **logical addresses** into **linear addresses**, the 80 x 86 processor
provides an additional nonprogrammable register that is, a register that cannot be set by a
programmer for each of the six programmable segmentation registers. Each nonprogrammable
register contains the 8-byte **Segment Descriptor** (described in the previous section) specified by the
**Segment Selector** contained in the corresponding **segmentation register**. Every time a **Segment
Selector** is loaded in a **segmentation register**, the corresponding **Segment Descriptor** is loaded from
memory into the matching nonprogrammable CPU register. From then on, translations of logical
addresses referring to that segment can be performed without accessing the `GDT` or `LDT` stored in
main memory; the processor can refer only directly to the CPU register containing the Segment
Descriptor. Accesses to the `GDT` or `LDT` are necessary only when the contents of the segmentation
registers change (see Figure 2-4).

Any Segment Selector includes three fields that are described in Table 2-2.

Table 2-2. Segment Selector fields

| Field name | Description                                                  |
| ---------- | ------------------------------------------------------------ |
| `index`    | Identifies the Segment Descriptor entry contained in the `GDT` or in the `LDT` (described further in the text following this table). |
| `TI`       | Table Indicator : specifies whether the Segment Descriptor is included in the `GDT` (TI = 0) or in the `LDT` (TI = 1). |
| `RPL`      | Requestor Privilege Level : specifies the Current Privilege Level of the CPU when the corresponding Segment Selector is loaded into the  cs register; it also may be used to selectively weaken the processor privilege level when accessing data segments (see Intel documentation for details). |

Because a Segment Descriptor is 8 bytes long, its relative address inside the `GDT` or the `LDT` is
obtained by multiplying the 13-bit index field of the Segment Selector by 8. For instance, if the `GDT` is at  `0x00020000` (the value stored in the  `gdtr` register) and the index specified by the Segment
Selector is 2, the address of the corresponding Segment Descriptor is  `0x00020000 +  (2 x  8)` , or
`0x00020010` .



## 2.2.4. Segmentation Unit

Figure 2-5 shows in detail how a **logical address** is translated into a corresponding **linear address**. The **segmentation unit** performs the following operations:

- Examines the  `TI` field of the **Segment Selector** to determine which **Descriptor Table** stores the
  **Segment Descriptor**. This field indicates that the Descriptor is either in the `GDT` (in which case
  the segmentation unit gets the base linear address of the `GDT` from the  `gdtr` register) or in the
  active `LDT` (in which case the segmentation unit gets the base linear address of that `LDT` from
  the  `ldtr` register).
- Computes the address of the **Segment Descriptor** from the  index field of the Segment Selector.
  The  index field is multiplied by 8 (the size of a Segment Descriptor), and the result is added to
  the content of the  `gdtr` or  `ldtr` register.
- Adds the **offset** of the **logical address** to the  Base field of the Segment Descriptor, thus
  obtaining the linear address.

Notice that, thanks to the nonprogrammable registers associated with the segmentation registers,
the first two operations need to be performed only when a segmentation register has been changed.

