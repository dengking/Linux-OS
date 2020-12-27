# 关于本章

本章讨论和stack和heap。

## stackoverflow [What and where are the stack and heap?](https://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap)



[A](https://stackoverflow.com/a/80113)

The stack is the memory set aside as scratch space for a thread of execution. When a function is called, a block is reserved on the top of the stack for local variables and some bookkeeping data. When that function returns, the block becomes unused and can be used the next time a function is called. The stack is always reserved in a LIFO (last in first out) order; the most recently reserved block is always the next block to be freed. This makes it really simple to keep track of the stack; freeing a block from the stack is nothing more than adjusting one pointer.

The heap is memory set aside for dynamic allocation. Unlike the stack, there's no enforced pattern to the allocation and deallocation of blocks from the heap; you can allocate a block at any time and free it at any time. This makes it much more complex to keep track of which parts of the heap are allocated or free at any given time; there are many custom heap allocators available to tune(协调) heap performance for different usage patterns.

Each thread gets a stack, while there's typically only one heap for the application (although it isn't uncommon to have multiple heaps for different types of allocation).

To answer your questions directly:

> *To what extent are they controlled by the OS or language runtime?*

The OS allocates the stack for each system-level thread when the thread is created. Typically the OS is called by the language runtime to allocate the heap for the application.

> *What is their scope?*

The stack is attached to a thread, so when the thread exits the stack is reclaimed. The heap is typically allocated at application startup by the runtime, and is reclaimed when the application (technically process) exits.

> *What determines the size of each of them?*

The size of the stack is set when a thread is created. The size of the heap is set on application startup, but can grow as space is needed (the allocator requests more memory from the operating system).

> *What makes one faster?*

The stack is faster because the access pattern makes it trivial to allocate and deallocate memory from it (a pointer/integer is simply incremented or decremented), while the heap has much more complex bookkeeping involved in an allocation or deallocation. Also, each byte in the stack tends to be reused very frequently which means it tends to be mapped to the processor's cache, making it very fast. Another performance hit for the heap is that the heap, being mostly a global resource, typically has to be **multi-threading safe**, i.e. each allocation and deallocation needs to be - typically - synchronized with "all" other heap accesses in the program.

> NOTE: 上述是`Stack-VS-heap/Operation-on-stack-VS-on-heap`。

A clear demonstration: ![img](https://i.stack.imgur.com/i6k0Z.png)
Image source: [vikashazrati.wordpress.com](http://vikashazrati.wordpress.com/2007/10/01/quicktip-java-basics-stack-and-heap/)



## programmerinterview [What’s the difference between a stack and a heap?](http://www.programmerinterview.com/data-structures/difference-between-stack-and-heap/)