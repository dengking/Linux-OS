# 3.2.4. How Processes Are Organized

The `runqueue` lists group all processes in a  `TASK_RUNNING` state. When it comes to grouping processes
in other states, the various states call for different types of treatment, with Linux opting for one of
the choices shown in the following list.

1、Processes in a  `TASK_STOPPED` ,  `EXIT_ZOMBIE` , or  `EXIT_DEAD` state are not linked in specific lists. There is no need to group processes in any of these three states, because stopped, zombie, and dead processes are accessed only via `PID` or via linked lists of the child processes for a particular parent.

2、Processes in a  `TASK_INTERRUPTIBLE` or  `TASK_UNINTERRUPTIBLE` state are subdivided into many classes, each of which corresponds to a specific **event**. In this case, the **process state** does not provide enough information to retrieve the process quickly, so it is necessary to introduce additional lists of processes. These are called ***wait queues*** and are discussed next.



## 3.2.4.1. Wait queues

**Wait queues** have several uses in the kernel, particularly for **interrupt handling**, **process
synchronization**, and **timing**. Because these topics are discussed in later chapters, we'll just say here that a process must often wait for some event to occur, such as for a **disk operation** to terminate, a **system resource** to be released, or a fixed interval of time to elapse. **Wait queues** implement conditional waits on events: a process wishing to wait for a specific event places itself in the proper **wait queue** and relinquishes（让渡） control. Therefore, a **wait queue** represents a set of **sleeping processes**, which are woken up by the **kernel** when some condition becomes true.

**Wait queues** are implemented as **doubly linked lists** whose elements include pointers to **process
descriptors**. Each **wait queue** is identified by a ***wait queue head***, a data structure of type [`wait_queue_head_t`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/wait.h#L55) :

```c

struct __wait_queue_head {
	spinlock_t lock;
	struct list_head task_list;
};
typedef struct __wait_queue_head wait_queue_head_t;
```

Because **wait queues** are modified by **interrupt handlers** as well as by major kernel functions, the doubly linked lists must be protected from concurrent accesses, which could induce unpredictable results (see Chapter 5). Synchronization is achieved by the  `lock` spin lock in the wait queue head. The  `task_list` field is the head of the list of waiting processes.

> NOTE:  : 在1.6.3. Reentrant Kernels中有这样的一段描述，非常有价值：

> All Unix kernels are reentrant. This means that several processes may be executing in Kernel Mode at the same time. Of course, on uniprocessor systems, only one process can progress, but many can be blocked in Kernel Mode when waiting for the CPU or the completion of some I/O operation. For instance, after issuing a read to a disk on behalf of a process, the kernel lets the disk controller handle it and resumes executing other processes. An interrupt notifies the kernel when the device has satisfied the read, so the former process can resume the execution.

Elements of a wait queue list are of type  [`wait_queue_t`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/wait.h#L29) :

```c
struct __wait_queue {
    unsigned int flags;
    struct task_struct * task;
    wait_queue_func_t func;
    struct list_head task_list;
};
typedef struct __wait_queue wait_queue_t;
```

Each element in the **wait queue list** represents a **sleeping process**, which is waiting for some event to occur; its descriptor address is stored in the  `task` field. The  `task_list` field contains the pointers that link this element to the list of processes waiting for the same event.

However, it is not always convenient to wake up ***all*** sleeping processes in a wait queue. For instance, if two or more processes are waiting for exclusive access to some resource to be released, it makes sense to wake up just one process in the **wait queue**. This process takes the resource, while the other processes continue to sleep. (This avoids a problem known as the "[thundering herd](https://en.wikipedia.org/wiki/Thundering_herd_problem)," with which multiple processes are wakened only to race for a resource that can be accessed by one of them, with the result that remaining processes must once more be put back to sleep.)

Thus, there are two kinds of sleeping processes: ***exclusive processes*** (denoted by the value `1` in the `flags` field of the corresponding wait queue element) are selectively woken up by the **kernel**, while ***nonexclusive processes*** (denoted by the value `0` in the  `flags` field) are always woken up by the kernel when the event occurs. A process waiting for a resource that can be granted to just one process at a time is a typical **exclusive process**. Processes waiting for an event that may concern any of them are **nonexclusive**. Consider, for instance, a group of processes that are waiting for the termination of a group of disk block transfers: as soon as the transfers complete, all waiting processes must be woken up. As we'll see next, the  `func` field of a **wait queue** element is used to specify how the processes sleeping in the wait queue should be woken up.

## 3.2.4.2. Handling wait queues

A new wait queue head may be defined by using the  `DECLARE_WAIT_QUEUE_HEAD(name)` macro, which statically declares a new wait queue head variable called  `name` and initializes its  `lock` and  `task_list`
fields. The  `init_waitqueue_head( )` function may be used to initialize a wait queue head variable that was allocated dynamically.

The  `init_waitqueue_entry(q,p )` function initializes a  `wait_queue_t` structure  `q` as follows:
```c
q->flags = 0;
q->task = p;
q->func = default_wake_function;
```

The nonexclusive process  `p` will be awakened by  `default_wake_function( )` , which is a simple wrapper for the  `try_to_wake_up( )` function discussed in Chapter 7.



Alternatively, the  `DEFINE_WAIT` macro declares a new  `wait_queue_t` variable and initializes it with the descriptor of the process currently executing on the CPU and the address of the `autoremove_wake_function( )` wake-up function. This function invokes  `default_wake_function( )` to
awaken the sleeping process, and then removes the **wait queue element** from the **wait queue list**. Finally, a kernel developer can define a custom awakening function by initializing the **wait queue element** with the  `init_waitqueue_func_entry( )` function.

Once an element is defined, it must be inserted into a **wait queue**. The  `add_wait_queue( )` function inserts a nonexclusive process in the first position of a wait queue list. The `add_wait_queue_exclusive( )` function inserts an exclusive process in the last position of a wait queue list. The  `remove_wait_queue( )` function removes a process from a wait queue list. The `waitqueue_active( )` function checks whether a given wait queue list is empty.

A process wishing to wait for a specific condition can invoke any of the functions shown in the following list.

1、The  `sleep_on( )` function operates on the current process:

```c
void sleep_on(wait_queue_head_t *wq)
{
    wait_queue_t wait;
    init_waitqueue_entry(&wait, current);
    current->state = TASK_UNINTERRUPTIBLE;
    add_wait_queue(wq,&wait); /* wq points to the wait queue head */
    schedule( );
    remove_wait_queue(wq, &wait);
}
```

The function sets the state of the current process to  `TASK_UNINTERRUPTIBLE` and inserts it into the specified wait queue. Then it invokes the scheduler, which resumes the execution of another process. When the sleeping process is awakened, the scheduler resumes execution of the  `sleep_on( )` function, which removes the process from the wait queue.

> NOTE:  :Wait queues implement conditional waits on events: a process wishing to wait for a specific event places itself in the proper wait queue and relinquishes control.显然，上述代码中的`schedule( )`就表示relinquishes control，显然，这就是发生在chapter 3.3中介绍的Process Switch；显然，当这个process再次被唤醒的时候，它就需要接着它上次被终止的地方继续运行，即从`remove_wait_queue(wq, &wait);`开始运行。

2、The  `interruptible_sleep_on( )` function is identical to  `sleep_on( )` , except that it sets the state of the current process to  `TASK_INTERRUPTIBLE` instead of setting it to `TASK_UNINTERRUPTIBLE` , so that the process also can be woken up by receiving a signal.

3、The  `sleep_on_timeout( )` and  `interruptible_sleep_on_timeout( )` functions are similar to the previous ones, but they also allow the caller to define a time interval after which the process will be woken up by the kernel. To do this, they invoke the  `schedule_timeout( )` function instead of  `schedule( )` (see the section "An Application of Dynamic Timers: the `nanosleep( )` System Call" in Chapter 6).

4、The  `prepare_to_wait( )` ,  `prepare_to_wait_exclusive( )` , and  `finish_wait( )` functions, introduced in Linux 2.6, offer yet another way to put the current process to sleep in a wait queue. Typically, they are used as follows:

```c
DEFINE_WAIT(wait);
prepare_to_wait_exclusive(&wq, &wait, TASK_INTERRUPTIBLE);
/* wq is the head of the wait queue */
...
if (!condition)
	schedule();
finish_wait(&wq, &wait);
```

The  `prepare_to_wait( )` and  `prepare_to_wait_exclusive( )` functions set the **process state** to the value passed as the third parameter, then set the exclusive flag in the wait queue element respectively to 0 (nonexclusive) or 1 (exclusive), and finally insert the wait queue element  `wait` into the list of the wait queue head  `wq` .

As soon as the process is awakened, it executes the  `finish_wait( )` function, which sets again the process state to  `TASK_RUNNING` (just in case the awaking condition becomes true before invoking  `schedule( )` ), and removes the wait queue element from the wait queue list (unless this has already been done by the wake-up function).

1、The  `wait_event` and  `wait_event_interruptible` macros put the calling process to sleep on a wait queue until a given condition is verified. For instance, the  `wait_event(wq,condition)` macro essentially yields the following fragment:

```c
DEFINE_WAIT(_ _wait);
for (;;) {
    prepare_to_wait(&wq, &_ _wait, TASK_UNINTERRUPTIBLE);
    if (condition)
    	break;
    schedule( );
}
finish_wait(&wq, &_ _wait);
```

> NOTE:  : 阻塞的系统调用也会导致kernel进行schedule。

> NOTE:  : 为什么要加上`for`？

A few comments on the functions mentioned in the above list: the  `sleep_on( )`-like functions cannot be used in the common situation where one has to test a condition and atomically put the process to sleep  hen the condition is not verified; therefore, because they are a well-known source of race conditions, their use is discouraged（[Time-of-check to time-of-use](https://en.wikipedia.org/wiki/Time-of-check_to_time-of-use)）. Moreover, in order to insert an **exclusive process** into a **wait queue**, the kernel must make use of the  `prepare_to_wait_exclusive( )` function (or just invoke `add_wait_queue_exclusive( )` directly); any other helper function inserts the process as nonexclusive. Finally, unless  `DEFINE_WAIT` or  `finish_wait( )` are used, the kernel must remove the wait queue element from the list after the waiting process has been awakened.

The kernel **awakens** processes in the **wait queues**, putting them in the  `TASK_RUNNING` state, by means of one of the following macros:  `wake_up` ,  `wake_up_nr` ,  `wake_up_all` ,  `wake_up_interruptible` , `wake_up_interruptible_nr` ,  `wake_up_interruptible_all` ,  `wake_up_interruptible_sync` , and `wake_up_locked` . One can understand what each of these nine macros does from its name:

1、All macros take into consideration sleeping processes in the  `TASK_INTERRUPTIBLE` state; if the macro name does not include the string "interruptible," sleeping processes in the `TASK_UNINTERRUPTIBLE` state also are considered.

> NOTE:  : 没有搞清楚上面这段话的含义

2、All macros wake all **nonexclusive processes** having the required state (see the previous bullet item).

3、The macros whose name include the string "`nr`" wake a given number of **exclusive processes** having the required state; this number is a parameter of the macro. The macros whose names include the string "`all`" wake all **exclusive processes** having the required state. Finally, the macros whose names don't include "`nr`" or "`all`" wake exactly one exclusive process that has the required state.

4、The macros whose names don't include the string "`sync`" check whether the priority of any of the woken processes is higher than that of the processes currently running in the systems and invoke  `schedule( )` if necessary. These checks are not made by the macro whose name includes the string "`sync`"; as a result, execution of a high priority process might be slightly delayed.

5、The  `wake_up_locked` macro is similar to  `wake_up` , except that it is called when the spin lock in `wait_queue_head_t` is already held.



For instance, the  `wake_up` macro is essentially equivalent to the following code fragment:

```c
void wake_up(wait_queue_head_t *q)
{
    struct list_head *tmp;
    wait_queue_t *curr;
    list_for_each(tmp, &q->task_list) {
        curr = list_entry(tmp, wait_queue_t, task_list);
        if (curr->func(curr, TASK_INTERRUPTIBLE|TASK_UNINTERRUPTIBLE, 0, NULL) && curr->flags)
        	break;
    }
}
```

The  `list_for_each` macro scans all items in the  `q->task_list` doubly linked list, that is, all processes in the **wait queue**. For each item, the  `list_entry` macro computes the address of the corresponding `wait_queue_t` variable. The  `func` field of this variable stores the address of the wake-up function, which tries to wake up the process identified by the  `task` field of the wait queue element. If a process has been effectively awakened (the function returned 1) and if the process is exclusive ( `curr->flags` equal to 1), the loop terminates. Because all nonexclusive processes are always at the beginning of the doubly linked list and all exclusive processes are at the end, the function always wakes the nonexclusive processes and then wakes one exclusive process, if any exists. [`*`]

> [`*`] By the way, it is rather uncommon that a wait queue includes both exclusive and nonexclusive processes. 



