# 1.6.5. Synchronization and Critical Regions

> NOTE: 虽然本节所描述的是kernel的synchronization，但是其中所描述的方法、思路可以广泛应用于其他领域。

Implementing a **reentrant kernel** requires the use of **synchronization** . If a **kernel control path** is suspended while acting on a kernel data structure, no other **kernel control path** should be allowed to act on the same data structure unless it has been reset to a **consistent state**. Otherwise, the interaction of the two control paths could corrupt the stored information.

For example, suppose a global variable `V` contains the number of available items of some system resource. The first kernel control path, `A`, reads the variable and determines that there is just one available item. At this point, another kernel control path, `B`, is activated and reads the same variable, which still contains the value `1`. Thus, `B` decreases `V` and starts using the resource item. Then `A` resumes the execution; because it has already read the value of `V`, it assumes that it can decrease `V` and take the resource item, which `B` already uses. As a final result, V contains -1, and two kernel control paths use the same resource item with potentially disastrous effects.

When the outcome of a computation depends on how two or more processes are scheduled, the code is incorrect. We say that there is a *race condition*.

In general, safe access to a **global variable** is ensured by using **atomic operations** . In the previous example, data corruption is not possible if the two control paths **read and decrease** `V` with a single, **noninterruptible operation**. However, kernels contain many data structures that cannot be accessed with a single operation. For example, it usually isn't possible to remove an element from a linked list with a single operation, because the kernel needs to access at least two pointers at once. Any section of code that should be finished by each process that begins it before another process can enter it is called a **critical region**. `[*]`

> `[*]` Synchronization problems have been fully described in other works; we refer the interested reader to books on the Unix operating systems (see the Bibliography).

These problems occur not only among **kernel control paths** but also among processes sharing common data. Several synchronization techniques have been adopted. The following section concentrates on how to synchronize **kernel control paths**.

## 1.6.5.1. Kernel preemption disabling

To provide a drastically simple solution to synchronization problems, some traditional Unix kernels are nonpreemptive: when a process executes in Kernel Mode, it cannot be arbitrarily suspended and substituted with another process. Therefore, on a uniprocessor system, all kernel data structures that are not updated by interrupts or exception handlers are safe for the kernel to access.

Of course, a process in Kernel Mode can voluntarily relinquish the CPU, but in this case, it must ensure that all data structures are left in a consistent state. Moreover, when it resumes its execution, it must recheck the value of any previously accessed data structures that could be changed.

A synchronization mechanism applicable to preemptive kernels consists of disabling kernel preemption before entering a critical region and reenabling it right after leaving the region. Nonpreemptability is not enough for multiprocessor systems, because two kernel control paths running on different CPUs can concurrently access the same data structure.

## 1.6.5.2. Interrupt disabling

Another **synchronization mechanism** for **uniprocessor systems** consists of disabling all hardware interrupts before entering a critical region and reenabling them right after leaving it. This mechanism, while simple, is far from optimal. If the critical region is large, interrupts can remain disabled for a relatively long time, potentially causing all hardware activities to freeze.

## 1.6.5.3. Semaphores

A widely used mechanism, effective in both uniprocessor and multiprocessor systems, relies on the use of *semaphores* . A semaphore is simply a counter associated with a data structure; it is checked by all kernel threads before they try to access the data structure. Each semaphore may be viewed as an object composed of:

- An integer variable
- A list of waiting processes
- Two atomic methods:  `down( )` and  `up( )`

The  `down( )` method decreases the value of the semaphore. If the new value is less than 0, the method adds the running process to the `semaphore list` and then blocks (i.e., invokes the **scheduler**). The  `up( )` method increases the value of the semaphore and, if its new value is greater than or equal to 0, reactivates one or more processes in the semaphore list.

Each data structure to be protected has its own semaphore, which is initialized to 1. When a kernel control path wishes to access the data structure, it executes the  `down( )` method on the proper semaphore. If the value of the new semaphore isn't negative, access to the data structure is granted. Otherwise, the process that is executing the kernel control path is added to the semaphore list and blocked. When another process executes the  `up( )` method on that semaphore, one of the processes in the semaphore list is allowed to proceed.

## 1.6.5.4. Spin locks

In multiprocessor systems, semaphores are not always the best solution to the **synchronization** problems. Some kernel data structures should be protected from being concurrently accessed by **kernel control paths** that run on different CPUs. In this case, if the time required to update the data structure is short, a semaphore could be very inefficient. To check a semaphore, the kernel must insert a process in the semaphore list and then suspend it. Because both operations are relatively expensive, in the time it takes to complete them, the other kernel control path could have already released the semaphore.

In these cases, multiprocessor operating systems use **spin locks** . A **spin lock** is very similar to a semaphore, but it has no **process list**; when a process finds the lock closed by another process, it "spins" around repeatedly, executing a tight instruction loop until the lock becomes open.

Of course, **spin locks** are useless in a uniprocessor environment. When a kernel control path tries to access a locked data structure, it starts an endless loop. Therefore, the kernel control path that is updating the protected data structure would not have a chance to continue the execution and release the spin lock. The final result would be that the system hangs.



## 1.6.5.5. Avoiding deadlocks

Processes or kernel control paths that synchronize with other control paths may easily enter a deadlock state. The simplest case of deadlock occurs when process `p1` gains access to data structure `a` and process `p2` gains access to `b`, but `p1` then waits for `b` and `p2` waits for `a`. Other more complex cyclic waits among groups of processes also may occur. Of course, a deadlock condition causes a complete freeze of the affected processes or kernel control paths.

As far as kernel design is concerned, deadlocks become an issue when the number of kernel locks used is high. In this case, it may be quite difficult to ensure that no deadlock state will ever be reached for all possible ways to interleave kernel control paths. Several operating systems, including Linux, avoid this problem by requesting locks in a predefined order.

> tag-Dijkstra-Resource-lock hierarchy-partial order-avoid deadlock-Linux kernel
