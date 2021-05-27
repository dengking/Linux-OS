# 3.2.2.5. The lists of `TASK_RUNNING` processes

When looking for a new process to run on a CPU, the kernel has to consider only the runnable processes (that is, the processes in the  `TASK_RUNNING` state).

Earlier Linux versions put all runnable processes in the same list called *`runqueue`*. Because it would be too costly to maintain the list ordered according to process priorities, the earlier schedulers were compelled to scan the whole list in order to select the "best" runnable process.

Linux 2.6 implements the `runqueue` differently. The aim is to allow the scheduler to select the best runnable process in constant time, independently of the number of runnable processes. We'll defer to Chapter 7 a detailed description of this new kind of `runqueue`, and we'll provide here only some basic information.

The trick used to achieve the scheduler speedup consists of splitting the `runqueue` in many lists of runnable processes, one list per **process priority**. Each  `task_struct` descriptor includes a  `run_list`
field of type  `list_head` . If the **process priority** is equal to `k` (a value ranging between 0 and 139), the `run_list` field links the **process descriptor** into the list of runnable processes having priority `k`. Furthermore, on a multiprocessor system, each CPU has its own `runqueue`, that is, its own set of lists of processes. This is a classic example of making a data structures more complex to improve performance: to make scheduler operations more efficient, the `runqueue` list has been split into 140 different lists!

As we'll see, the kernel must preserve a lot of data for every `runqueue` in the system; however, the main data structures of a `runqueue` are the lists of process descriptors belonging to the `runqueue`; all these lists are implemented by a single  `prio_array_t` data structure, whose fields are shown in Table 3-2.

> NOTE: bootlin [prio_array](https://elixir.bootlin.com/linux/v2.6.11/source/kernel/sched.c#L185)

The  `enqueue_task(p,array)` function inserts a process descriptor into a `runqueue` list; its code is essentially equivalent to:

```c
list_add_tail(&p->run_list, &array->queue[p->prio]);
__set_bit(p->prio, array->bitmap);
array->nr_active++;
p->array = array;
```

The  `prio` field of the process descriptor stores the dynamic priority of the process, while the  `array` field is a pointer to the  `prio_array_t` data structure of its current `runqueue`. Similarly, the `dequeue_task(p,array)` function removes a process descriptor from a `runqueue` list.