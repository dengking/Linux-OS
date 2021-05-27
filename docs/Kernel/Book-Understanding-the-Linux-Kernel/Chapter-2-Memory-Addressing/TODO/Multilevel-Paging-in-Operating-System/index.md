# Multilevel Paging in Operating System

Prerequisite – [Paging](https://www.geeksforgeeks.org/operating-system-paging/)

**Multilevel Paging** is a paging scheme which consist of two or more levels of page tables in a hierarchical manner. It is also known as hierarchical paging. The entries of the level 1 page table are pointers to a level 2 page table and entries of the level 2 page tables are pointers to a level 3 page table and so on. The entries of the last level page table are stores actual frame information. Level 1 contain single page table and address of that table is stored in PTBR (Page Table Base Register).

Virtual address:



![img](https://media.geeksforgeeks.org/wp-content/uploads/20190608174849/virtual2.png)



In multilevel paging whatever may be levels of paging all the page tables will be stored in main memory.So it requires more than one memory access to get the physical address of page frame. One access for each level needed. Each page table entry **except** the last level page table entry contains base address of the next level page table.



![img](https://media.geeksforgeeks.org/wp-content/uploads/20190608174704/multilevel.png)

Reference to actual page frame:

- Reference to PTE in level 1 page table = PTBR value + Level 1 offset present in virtual address.
- Reference to PTE in level 2 page table = Base address (present in Level 1 PTE) + Level 2 offset (present in VA).
- Reference to PTE in level 3 page table= Base address (present in Level 2 PTE) + Level 3 offset (present in VA).
- Actual page frame address = PTE (present in level 3).

Generally the page table size will be equal to the size of page.

**Assumptions:**
Byte addressable memory, and `n` is the number of bits used to represent virtual address.

**Important formula:**

```
Number of entries in page table: 
= (virtual address space size) / (page size) 
= Number of pages

Virtual address space size: 
= 2^{n} B 

Size of page table: 
<>= (number of entries in page table)*(size of PTE) 
```

If page table size > desired size then create 1 more level.

**Disadvantage:**

Extra memory references to access **address translation tables** can slow programs down by a factor of two or more. Use translation look aside buffer (TLB) to speed up address translation by storing page table entries.

**Example:**
Q. Consider a virtual memory system with physical memory of 8GB, a page size of 8KB and 46 bit virtual address. *Assume every page table exactly fits into a single page*. If page table entry size is 4B then how many levels of page tables would be required.

**Explanation:**

```
Page size = 8KB = 2^{13} B
Virtual address space size = 2^{46} B
PTE = 4B = 2^2 B

Number of pages or number of entries in page table, 
= (virtual address space size) / (page size) 
= 2^{46} B/2^{13} B 
= 2^{33}
```

Size of page table,

```
= (number of entries in page table)*(size of PTE) 
= 2^{33} * 2^2 B 
= 2^{35} B 
```

To create one more level,

```
Size of page table > page size

Number of page tables in last level, 
= 2^{35} B / 2^{13} B 
= 2^{22} 
```

