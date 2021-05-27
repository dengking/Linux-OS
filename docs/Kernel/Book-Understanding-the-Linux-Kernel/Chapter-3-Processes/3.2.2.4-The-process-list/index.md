# 3.2.2.4. The process list

The first example of a doubly linked list we will examine is the *process list*, a list that links together
all existing process descriptors. Each  `task_struct` structure includes a  `tasks` field of type  `list_head`
whose  `prev` and  `next` fields point, respectively, to the previous and to the next  `task_struct` element.



The **head** of the **process list** is the  `init_task task_struct` descriptor; it is the **process descriptor** of
the so-called *process 0* or *swapper* (see the section "Kernel Threads" later in this chapter). The
`tasks->prev` field of  `init_task` points to the  `tasks` field of the process descriptor inserted last in the
list.

The  `SET_LINKS` and  `REMOVE_LINKS` macros are used to insert and to remove a process descriptor in the
**process list**, respectively. These macros also take care of the parenthood relationship of the process
(see the section "How Processes Are Organized" later in this chapter).



Another useful macro, called  `for_each_process` , scans the whole process list. It is defined as:

```assembly
#define for_each_process(p) \
for (p=&init_task; (p=list_entry((p)->tasks.next, \
struct task_struct, tasks) \
) != &init_task; )
```

The macro is the loop control statement after which the kernel programmer supplies the loop. Notice
how the  `init_task` process descriptor just plays the role of **list header**. The macro starts by moving
past  `init_task` to the next task and continues until it reaches  `init_task` again (thanks to the
**circularity** of the list). At each iteration, the variable passed as the argument of the macro contains
the address of the currently scanned process descriptor, as returned by the  `list_entry` macro.

> NOTE: 在multiprocessor中，是否是每个processor都有一个process list，还是说所有的process descriptor都放在一个process list中？

