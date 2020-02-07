# Chapter 9. Process Address Space

As seen in the previous chapter, a kernel function gets dynamic memory in a fairly straightforward manner by invoking one of a variety of functions:  `__get_free_pages( )` or  `alloc_pages( )` to get **pages** from the zoned page frame allocator,  `kmem_cache_alloc( )` or  `kmalloc( )` to use the slab allocator for specialized or general-purpose objects, and  `vmalloc( )` or  `vmalloc_32( )` to get a noncontiguous memory area. If the request can be satisfied, each of these functions returns a **page descriptor address** or a linear address identifying the beginning of the allocated dynamic memory area.

> NOTE: 普通的process是不会接触到page descriptor的

These simple approaches work for two reasons:

- The kernel is the highest-priority component of the operating system. If a kernel function makes a request for **dynamic memory**, it must have a valid reason to issue that request, and there is no point in trying to defer it.
- The kernel trusts itself. All kernel functions are assumed to be error-free, so the kernel does not need to insert any protection against programming errors.

When allocating memory to User Mode processes, the situation is entirely different:

- Process requests for **dynamic memory** are considered non-urgent. When a process's executable file is loaded, for instance, it is unlikely that the process will address all the pages of code in the near future. Similarly, when a process invokes  `malloc( )` to get additional dynamic memory, it doesn't mean the process will soon access all the additional memory obtained. Thus, as a general rule, the kernel tries to defer allocating dynamic memory to User Mode processes.
- Because user programs cannot be trusted, the kernel must be prepared to catch all addressing errors caused by processes in User Mode.

As this chapter describes, the kernel succeeds in deferring the allocation of **dynamic memory** to processes by using a new kind of resource. When a **User Mode process** asks for **dynamic memory**, it doesn't get additional **page frames**; instead, it gets the right to use a new range of **linear addresses**, which become part of its **address space**. This interval is called a "**memory region**."

In the next section, we discuss how the process views **dynamic memory**. We then describe the basic components of the **process address space** in the section "Memory Regions." Next, we examine in detail the role played by the **Page Fault exception handler** in deferring the allocation of **page frames** to processes and illustrate how the kernel **creates** and **deletes** whole **process address spaces**. Last, we discuss the APIs and system calls related to **address space management**.