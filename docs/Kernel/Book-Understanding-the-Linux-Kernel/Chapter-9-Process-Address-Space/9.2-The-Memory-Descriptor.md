# 9.2. The Memory Descriptor

All information related to the process address space is included in an object called the *memory descriptor* of type  `mm_struct` . This object is referenced by the  `mm` field of the **process descriptor**. The fields of a **memory descriptor** are listed in Table 9-2.

Table 9-2. The fields of the memory descriptor

| Type                      | Field               | Description                                                  | 注释                                                         |
| ------------------------- | ------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `struct vm_area_struct *` | `mmap`              | Pointer to the head of the list of memory region objects     | 参见chapter 9.3. Memory Regions                              |
| `struct rb_root`          | `mm_rb`             | Pointer to the root of the red-black tree of memory region objects |                                                              |
| `struct vm_area_struct *` | `mmap_cache`        | Pointer to the last referenced memory region object          |                                                              |
| `unsigned long (*)( )`    | `get_unmapped_area` | Method that searches an available linear address interval in the process address space |                                                              |
| `void (*)( )`             | `unmap_area`        | Method invoked when releasing a linear address interval      |                                                              |
| `unsigned long`           | `mmap_base`         | Identifies the linear address of the first allocated anonymous memory region or file memory mapping (see the section "Program Segments and Process Memory Regions" in Chapter 20) |                                                              |
| `unsigned long`           | `free_area_cache`   | Address from which the kernel will look for a free interval of linear addresses in the process address space |                                                              |
| `pgd_t *`                 | `pgd`               | Pointer to the Page Global Directory                         | 关于Page Global Directory，参见Section 2.4. Paging in Hardware、Section 2.5. Paging in Linux |
| `atomic_t`                | `mm_users`          | Secondary usage counter                                      |                                                              |
| `atomic_t`                | `mm_count`          | Main usage counter                                           |                                                              |



All **memory descriptors** are stored in a doubly linked list. Each **descriptor** stores the address of the adjacent list items in the  `mmlist` field. The first element of the list is the  `mmlist` field of  `init_mm` , the memory descriptor used by process 0 in the initialization phase. The list is protected against concurrent accesses in multiprocessor systems by the  `mmlist_lock` spin lock.

The  `mm_users` field stores the number of **lightweight processes** that share the  `mm_struct` data structure (see the section "The `clone( )`, `fork( )`, and `vfork( )` System Calls" in Chapter 3). The `mm_count` field is the main usage counter of the **memory descriptor;** all "users" in  `mm_users` count as one unit in  `mm_count` . Every time the  `mm_count` field is decreased, the kernel checks whether it becomes zero; if so, the **memory descriptor** is deallocated because it is no longer in use.