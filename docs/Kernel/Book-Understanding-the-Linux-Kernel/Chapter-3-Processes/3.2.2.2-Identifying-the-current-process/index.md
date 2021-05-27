# 3.2.2.2. Identifying the current process

The close association between the  `thread_info` structure and the **Kernel Mode stack** just described
offers a key benefit in terms of efficiency: the **kernel** can easily obtain the address of the
`thread_info` structure of the process currently running on a CPU from the value of the  `esp` register.
In fact, if the  `thread_union` structure is 8 KB ($2^{13}$ bytes) long, the kernel masks out the 13 least
significant bits of  `esp` to obtain the base address of the  `thread_info` structure; on the other hand, if
the  `thread_union` structure is 4 KB long, the kernel masks out the 12 least significant bits of  `esp` .
This is done by the  `current_thread_info( )` function, which produces assembly language
instructions like the following:

```assembly
movl $0xffffe000,%ecx /* or 0xfffff000 for 4KB stacks */
andl %esp,%ecx
movl %ecx,p
```

After executing these three instructions,  p contains the  `thread_info` structure pointer of the process
running on the CPU that executes the instruction.

Most often the kernel needs the address of the **process descriptor** rather than the address of the
`thread_info` structure. To get the **process descriptor pointer** of the process currently running on a
CPU, the kernel makes use of the  `current` macro, which is essentially equivalent to
`current_thread_info( )->task` and produces assembly language instructions like the following:

```c
movl $0xffffe000,%ecx /* or 0xfffff000 for 4KB stacks */
andl %esp,%ecx
movl (%ecx),p
```

Because the  `task` field is at offset 0 in the  `thread_info` structure, after executing these three
instructions  `p` contains the **process descriptor pointer** of the process running on the CPU.

The  `current` macro often appears in kernel code as a prefix to fields of the **process descriptor**. For
example,  `current->pid` returns the **process ID** of the process currently running on the CPU.

Another advantage of storing the **process descriptor** with the **stack** emerges on multiprocessor
systems: the correct current process for each hardware processor can be derived just by checking
the stack, as shown previously. Earlier versions of Linux did not store the **kernel stack** and the
**process descriptor** together. Instead, they were forced to introduce a global static variable called
`current` to identify the **process descriptor** of the running process. On multiprocessor systems, it was
necessary to define  current as an array one element for each available CPU.



> NOTE:  : 所有的**process descriptor** 和 **kernel stack** 都是位于kernel中；由kernel来执行调度；当CPU需要执行某个**process descriptor**的时候，它需要读取这个**process descriptor**的一些数据，比如之前保存的register数据等以便resume；从上面的描述可以看出，CPU是根据`esp`的值来获得**process descriptor**的地址，并且，从前面的描述来看，每个`thread_union`都有一个自己的 **kernel stack** ，而从上面的描述来看，是根据`esp`的值来获得**process descriptor**的地址，所以CPU是在某个`thread_union的 **kernel stack**中执行，然后得到对应的**process descriptor**；

> NOTE:  : 因为scheduler在调度一个task开始运行之前会将这个task的所有的register都恢复到CPU中，所以必然会包含`esp`，所以它就可以根据`esp`快速地定位到process descriptor；