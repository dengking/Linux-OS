# 3.2.3. Relationships Among Processes

Processes created by a program have a **parent/child relationship**. When a process creates multiple children , these children have **sibling relationships**. Several fields must be introduced in a process descriptor to represent these relationships; they are listed in Table 3-3 with respect to a given process `P`. Processes `0` and `1` are created by the **kernel**; as we'll see later in the chapter, process 1 (`init`) is the ancestor of all other processes.



Table 3-3. Fields of a process descriptor used to express parenthood relationships

| Field name                                                   | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [`real_parent`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L578) | Points to the process descriptor of the process that created `P` or to the descriptor of process 1 (`init`) if the parent process no longer exists. (Therefore, when a user starts a background process and exits the shell, the background process becomes the child of `init`.) |
| [`parent`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L579) | Points to the current parent of `P` (this is the process that must be signaled when the child process terminates); its value usually coincides with that of  `real_parent` . It may occasionally differ, such as when another process issues a  `ptrace( )` system call requesting that it be allowed to monitor `P` (see the section "Execution Tracing" in Chapter 20). |
| [`children`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L584) | The head of the list containing all children created by `P`. |
| [`sibling`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L585) | The pointers to the next and previous elements in the list of the sibling processes, those that have the same parent as `P`. |

Figure 3-4 illustrates the parent and sibling relationships of a group of processes. Process `P0` successively created `P1`, `P2`, and `P3`. Process `P3`, in turn, created process `P4`.



Furthermore, there exist other relationships among processes: a process can be a leader of a **process group** or of a **login session** (see "Process Management" in Chapter 1), it can be a **leader** of a **thread group** (see "Identifying a Process" earlier in this chapter), and it can also **trace** the execution of other processes (see the section "Execution Tracing" in Chapter 20). Table 3-4 lists the fields of the process descriptor that establish these relationships between a process `P` and the other processes.

Table 3-4. The fields of the process descriptor that establish non-parenthood relationships

| Field name                                                   | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [`group_leader`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L585) | Process descriptor pointer of the group leader of `P` > NOTE:  : 是thread group leader |
| [`signal->pgrp`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L632) | `PID` of the group leader of `P`  > NOTE:  : 是process group |
| [`tgid`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L572) | `PID` of the thread group leader of `P`                      |
| [`signal->session`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L306) | `PID` of the login session leader of `P`                     |
| [`ptrace_children`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L558) | The head of a list containing all children of `P` being traced by a debugger |
| [`ptrace_list`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L559) | The pointers to the next and previous elements in the real parent's list of traced processes (used when P is being traced) |

> NOTE:  : [struct signal_struct](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L274) 

> NOTE:  : `pgrp`表示的是process group，`tgid`表示的是thread group ID。

> NOTE:  : [How does Linux tell threads apart from child processes?](https://unix.stackexchange.com/questions/434092/how-does-linux-tell-threads-apart-from-child-processes)



## 3.2.3.1. The `pidhash` table and chained lists

In several circumstances, the kernel must be able to derive the **process descriptor pointer** corresponding to a `PID`. This occurs, for instance, in servicing the  `kill( )` system call. When process `P1` wishes to send a signal to another process, `P2`, it invokes the  `kill( )` system call specifying the `PID` of `P2` as the parameter. The kernel derives the **process descriptor pointer** from the `PID` and then extracts the pointer to the data structure that records the pending signals from `P2`'s process descriptor.

Scanning the process list sequentially and checking the  `pid` fields of the **process descriptors** is feasible but rather inefficient. To speed up the search, four hash tables have been introduced. Why multiple hash tables? Simply because the **process descriptor** includes fields that represent different types of `PID` (see Table 3-5), and each type of `PID` requires its own hash table.

Table 3-5. The four hash tables and corresponding fields in the **process descriptor**

| Hash table type | Field name | Description                          |
| --------------- | ---------- | ------------------------------------ |
| `PIDTYPE_PID`   | `pid`      | `PID` of the process                 |
| `PIDTYPE_TGID`  | `tgid`     | `PID` of thread group leader process |
| `PIDTYPE_PGID`  | `pgrp`     | `PID` of the group leader process    |
| `PIDTYPE_SID`   | `session`  | `PID` of the session leader process  |

The four **hash tables** are dynamically allocated during the **kernel initialization phase**, and their addresses are stored in the  `pid_hash` array. The size of a single **hash table** depends on the amount of available RAM; for example, for systems having 512 MB of RAM, each **hash table** is stored in four page frames and includes 2,048 entries.

> NOTE:  : `pid_hash`在[/](https://elixir.bootlin.com/linux/v2.6.11/source)[kernel](https://elixir.bootlin.com/linux/v2.6.11/source/kernel)/[pid.c](https://elixir.bootlin.com/linux/v2.6.11/source/kernel/pid.c) 中定义，定义如下：

```c
static struct hlist_head *pid_hash[PIDTYPE_MAX];
```

`hlist_head`在[/](https://elixir.bootlin.com/linux/v2.6.11/source)[include](https://elixir.bootlin.com/linux/v2.6.11/source/include)/[linux](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux)/[list.h](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/list.h#L491)中定义；

> NOTE:  :2018表示的是hash table的长度，所以hash函数需要将`pid`映射到`[0-2017]`范围内；

The `PID` is transformed into a **table index** using the  [`pid_hashfn`](https://elixir.bootlin.com/linux/v2.6.11/source/kernel/pid.c#L30) macro, which expands to:

```c
#define pid_hashfn(x) hash_long((unsigned long) x, pidhash_shift)
```

The  `pidhash_shift` variable stores the length in bits of a **table index** (11, in our example). The `hash_long( )` function is used by many hash functions; on a 32-bit architecture it is essentially equivalent to:

```c
unsigned long hash_long(unsigned long val, unsigned int bits)
{
unsigned long hash = val * 0x9e370001UL;
return hash >> (32 - bits);
}
```

Because in our example  `pidhash_shift` is equal to 11,  `pid_hashfn` yields values ranging between 0
and $2^{11} - 1 = 2047$.

> The Magic Constant
>
> You might wonder where the `0x9e370001` constant (= 2,654,404,609) comes from. This hash function is based on a multiplication of the index by a suitable large number, so that the result overflows and the value remaining in the 32-bit variable can be considered as the result of a modulus operation. Knuth suggested that good results are obtained when the large multiplier is a prime approximately in golden ratio to 2 32 (32 bit being the size of the 80x86's registers). Now, 2,654,404,609 is a prime near to
> that can also be easily multiplied by additions and bit shifts, because it is equal to

> NOTE:  : 参见 [魔数常量](https://www.cnblogs.com/hoys/archive/2012/03/03/2378411.html)  [The Magic Constant](https://webstersprodigy.net/2007/08/08/the-magic-constant/)

As every basic computer science course explains, a hash function does not always ensure a one-to-one correspondence between `PID`s and table indexes. Two different `PID`s that hash into the same table index are said to be ***colliding***.

Linux uses ***chaining*** to handle colliding `PID`s; each **table entry** is the **head** of a doubly linked list of colliding **process descriptors**. Figure 3-5 illustrates a `PID` hash table with two lists. The processes having `PID`s 2,890 and 29,384 hash into the 200th element of the table, while the process having `PID` 29,385 hashes into the 1,466 th element of the table.

Hashing with chaining is preferable to a linear transformation from `PID`s to table indexes because at any given instance, the number of processes in the system is usually far below 32,768 (the maximum number of allowed `PID`s). It would be a waste of storage to define a table consisting of 32,768 entries, if, at any given instance, most such entries are unused.

The data structures used in the **`PID` hash tables** are quite sophisticated, because they must keep track of the relationships between the processes. As an example, suppose that the kernel must retrieve all processes belonging to a given **thread group**, that is, all processes whose  `tgid` field is equal to a given number. Looking in the **hash table** for the given **thread group number** returns just one **process descriptor**, that is, the descriptor of the **thread group leader**. To quickly retrieve the other processes in the group, the kernel must maintain a list of processes for each **thread group**. The same situation arises when looking for the processes belonging to a given **login session** or belonging to a given **process group**.

The **`PID` hash table**s' data structures solve all these problems, because they allow the definition of a list of processes for any `PID` number included in a **hash table**. The core data structure is an array of four  `pid` structures embedded in the  [`pids`](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/sched.h#L589) field of the **process descriptor**; the fields of the  `pid` structure are shown in Table 3-6.

Table 3-6. The fields of the `pid` data structures

| Type                | Name        | Description                                                  |
| ------------------- | ----------- | ------------------------------------------------------------ |
| int                 | `nr`        | The `PID` number                                             |
| `struct hlist_node` | `pid_chain` | The links to the next and previous elements in the **hash chain list** |
| `struct list_head`  | `pid_list`  | The head of the **per-`PID` list**                           |

> NOTE:  : **per-`PID` list**其实就是thread group

> NOTE:  : [hlist_node](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/list.h#L495) 

> NOTE:  : [/](https://elixir.bootlin.com/linux/v2.6.11/source)[include](https://elixir.bootlin.com/linux/v2.6.11/source/include)/[linux](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux)/[pid.h](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/pid.h)

Figure 3-6 shows an example based on the  `PIDTYPE_TGID` hash table. The second entry of the `pid_hash` array stores the address of the **hash table**, that is, the array of  `hlist_head` structures representing the heads of the chain lists. In the chain list rooted at the 71 st entry of the hash table, there are two process descriptors corresponding to the `PID` numbers 246 and 4,351 (double-arrow lines represent a couple of forward and backward pointers). The `PID` numbers are stored in the  `nr` field of the  `pid` structure embedded in the **process descriptor** (by the way, because the **thread group number** coincides with the `PID` of its leader, these numbers also are stored in the  `pid` field of the **process descriptors**). Let us consider the **per-`PID` list** of the thread group 4,351: the head of the list is stored in the  `pid_list` field of the process descriptor included in the hash table, while the links to the next and previous elements of the **per-`PID` list** also are stored in the  `pid_list` field of each list element.

The following functions and macros are used to handle the `PID` hash tables:

```c
do_each_task_pid(nr, type, task);
```

> NOTE:  : `type`在[/](https://elixir.bootlin.com/linux/v2.6.11/source)[include](https://elixir.bootlin.com/linux/v2.6.11/source/include)/[linux](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux)/[pid.h](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/pid.h)中定义


```c
while_each_task_pid(nr, type, task);
```

Mark `begin` and `end` of a do-while loop that iterates over the **per-`PID` list** associated with the `PID` number  `nr` of type  `type` ; in any iteration,  `task` points to the **process descriptor** of the currently scanned element.

```c
find_task_by_pid_type(type, nr)
```

Looks for the process having `PID`  `nr` in the hash table of type  `type` . The function returns a **process descriptor pointer** if a match is found, otherwise it returns  `NULL` .

```c
find_task_by_pid(nr)
```

Same as  `find_task_by_pid_type(PIDTYPE_PID, nr)` .

```c
attach_pid(task, type, nr)
```

Inserts the **process descriptor** pointed to by  `task` in the `PID` hash table of type  `type` according to the `PID` number  `nr` ; if a process descriptor having `PID  nr` is already in the hash table, the function simply inserts  `task` in the **per-`PID` list** of the already present process.

```c
detach_pid(task, type)
```

Removes the **process descriptor** pointed to by  task from the **per-`PID` list** of type  type to which the descriptor belongs. If the **per-`PID` list** does not become empty, the function terminates. Otherwise, the function removes the **process descriptor** from the hash table of type  `type` ; finally, if the `PID` number does not occur in any other hash table, the function clears the corresponding bit in the `PID` bitmap, so that the number can be recycled.

```c
next_thread(task)
```

Returns the **process descriptor** address of the lightweight process that follows  `task` in the **hash
table** list of type  `PIDTYPE_TGID` . Because the hash table list is circular, when applied to a conventional process the macro returns the descriptor address of the process itself.

