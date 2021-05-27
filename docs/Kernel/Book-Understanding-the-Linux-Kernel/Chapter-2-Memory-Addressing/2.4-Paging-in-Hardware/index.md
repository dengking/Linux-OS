# 2.4. Paging in Hardware

The **paging unit** translates **linear addresses** into **physical ones**. One key task in the unit is to check the requested access type against the **access rights** of the **linear address**. If the memory access is not valid, it generates a **Page Fault exception** (see Chapter 4 and Chapter 8).

For the sake of efficiency, **linear addresses** are grouped in fixed-length intervals called ***pages*** ; contiguous linear addresses within a page are mapped into contiguous physical addresses. In this way, the **kernel** can specify the **physical address** and the **access rights** of **a page** instead of those of all the **linear addresses** included in it. Following the usual convention, we shall use the term "page" to refer both to a set of linear addresses and to the data contained in this group of addresses.

The paging unit thinks of all RAM as partitioned into fixed-length ***page frames*** (sometimes referred to as ***physical pages*** ). Each **page frame** contains a page that is, the length of a **page frame** coincides with that of a **page**. A **page frame** is a constituent of main memory, and hence it is a storage area. It is important to distinguish a **page** from a **page frame**; the former is just a block of data, which may be stored in any **page frame** or on **disk**.

The data structures that map linear to physical addresses are called ***page tables*** ; they are stored in main memory and must be properly initialized by the kernel before enabling the **paging unit**.

> NOTE: 有必要梳理一下paging unit和page tables之间的关系：两者组合起来实现将linear address转换为physical address，paging unit需要依赖于page tables中的数据。

Starting with the 80386, all 80 x 86 processors support **paging**; it is enabled by setting the  `PG` flag of a control register named  `cr0` . When  PG = 0 , **linear addresses** are interpreted as **physical addresses**.

## 2.4.1. Regular Paging

Starting with the 80386, the paging unit of Intel processors handles 4 KB pages.

The 32 bits of a linear address are divided into three fields:

***Directory***

The most significant 10 bits

***Table***

The intermediate 10 bits

***Offset***

The least significant 12 bits



The translation of **linear addresses** is accomplished in two steps, each based on a type of **translation table**. The first **translation table** is called the **Page Directory**, and the second is called the **Page Table**. [`*`]

> [`*`] In the discussion that follows, the lowercase "page table" term denotes any page storing the mapping between linear and physical addresses, while the capitalized "Page Table" term denotes a page in the last level of page tables.

**The aim of this two-level scheme is to reduce the amount of RAM required for per-process Page Tables**. If a simple one-level Page Table was used, then it would require up to 220 entries (i.e., at 4 bytes per entry, 4 MB of RAM) to represent the Page Table for each process (if the process used a full 4 GB linear address space), even though a process does not use all addresses in that range. The two-level scheme reduces the memory by requiring Page Tables only for those virtual memory regions actually used by a process.

Each active process must have a **Page Directory** assigned to it. However, there is no need to allocate RAM for all **Page Tables** of a process at once; it is more efficient to allocate RAM for a Page Table only when the process effectively needs it.

> NOTE:  综合上面的内容可以知道，page table的实现可以与两种方案：
>
> - 使用线性结构，也就是上面所说的one-level page table
> - 使用multi-level结构，multi-level结构其实本质上是Tree结构，上述two-level scheme所对应的page table的结构就是一个two-level结构，参见Figure 2-7。它的Tree结构是这样的：`cr3`相当于root节点，这个root节点只有一个子节点Page Directory，Page Directory共有$2^{10}$个entry，每个entry指向一个Page Table，即Page Directory共有$2^{10}$个子节点，子节点的类型是Page Table。每个Page Table有$2^{10}$个page，即Page Table有$2^{10}$个子节点，子节点的类型是page，page没有子节点，所以它是leaf。在multi-level结构的page table中进行映射的过程相当于从root节点沿着内节点到leaf。
>
> 
>
> 每个process有一个**Page Directory** ，而不是**Page Directory** 中的一条记录；为什么two-level scheme能够减少需要的RAM，参见下面内容：
>
> - [Multilevel Paging in Operating System](https://www.geeksforgeeks.org/multilevel-paging-in-operating-system/)
>
> - https://www.clear.rice.edu/comp425/slides/L31.pdf
>
> - [How does multi-level page table save memory space?](https://stackoverflow.com/questions/29467510/how-does-multi-level-page-table-save-memory-space)

The **physical address** of the **Page Directory** in use is stored in a control register named  `cr3` . The **Directory** field within the **linear address** determines the entry in the **Page Directory** that points to the proper **Page Table**. The address's **Table** field, in turn, determines the entry in the **Page Table** that contains the **physical address** of the **page frame** containing the page. The Offset field determines the relative position within the page frame (see Figure 2-7). Because it is 12 bits long, each page consists of 4096 bytes of data.

![](./Figure-2-7-Paging-by-80x86-processors.jpg)

Both the Directory and the Table fields are 10 bits long, so **Page Directories** and **Page Tables** can include up to 1,024（$2^{10}=1024$） entries. It follows that a Page Directory can address up to $1024 * 1024 * 4096=2^{32}$ memory cells, as you'd expect in 32-bit addresses.

The entries of **Page Directories** and **Page Tables** have the same structure. Each entry includes the following fields:

*`Present` flag*

If it is set, the referred-to page (or Page Table) is contained in main memory; if the flag is 0, the page is not contained in main memory and the **remaining entry bits** may be used by the operating system for its own purposes. If the entry of a **Page Table** or **Page Directory** needed to perform an **address translation** has the  **Present flag** cleared, the **paging unit** stores the **linear address** in a control register named  `cr2` and generates exception 14: the Page Fault exception. (We will see in Chapter 17 how Linux uses this field.)

> NOTE: 产生了Page Fault exception后，就需要将demand page swap到memory中

*Field containing the 20 most significant bits of a page frame physical address*

*`Accessed` flag*



*`Dirty` flag*



## 2.4.2. Extended Paging

Starting with the Pentium model, 80 x 86 microprocessors introduce extended paging , which allows page frames to be 4 MB instead of 4 KB in size (see Figure 2-8). Extended paging is used to translate large contiguous linear address ranges into corresponding physical ones; in these cases, the kernel can do without intermediate Page Tables and thus save memory and preserve TLB entries (see the section "Translation Lookaside Buffers (TLB)").

![](./Figure-2-8-Extended-paging.jpg)

## 2.4.3. Hardware Protection Scheme



## 2.4.4. An Example of Regular Paging



## 2.4.5. The Physical Address Extension (PAE) Paging Mechanism



## 2.4.6. Paging for 64-bit Architectures



## 2.4.7. Hardware Cache



## 2.4.8. Translation Lookaside Buffers (TLB)

