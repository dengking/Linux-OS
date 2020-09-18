# [ps(1) — Linux manual page](https://www.man7.org/linux/man-pages/man1/ps.1.html)

## NAME         

`ps` - report a snapshot of the current processes.

## SYNOPSIS         

`ps [options]`

## DESCRIPTION         

**ps** displays information about a selection of the active processes. If you want a repetitive update of the selection and the displayed information, use [**top**(1)](https://linux.die.net/man/1/top) instead.

This version of **ps** accepts several kinds of options:

- 1UNIX options, which may be grouped and must be preceded by a dash.
- 2 BSD options, which may be grouped and must not be used with a dash.
- 3 GNU long options, which are preceded by two dashes.

> NOTE: 显然`ps`的实现，根据dash个数来区分是哪种option。结合后文来看，1UNIX option是standard。

Options of different types may be freely mixed, but conflicts can appear. There are some synonymous（同义的） options, which are functionally identical, due to the many standards and **ps** implementations that this **ps** is compatible with.

Note that "**ps -aux**" is distinct from "**ps aux**". The POSIX and UNIX standards require that "**ps -aux**" print all processes owned by a **user** named "x", as well as printing all processes that would be selected by the **-a** option. If the user named "x" does not exist, this **ps** may interpret the command as "**ps aux**" instead and print a warning. This behavior is intended to aid in transitioning(过渡) old scripts and habits. It is fragile, subject to change, and thus should not be relied upon.



By default, **ps** selects all processes with the same **effective user ID** (`euid`=`EUID`) as the **current user** and associated with the same **terminal** as the invoker. It displays the process ID (`pid`=`PID`), the terminal associated with the process (`tname`=`TTY`), the cumulated(累计的) CPU time in `[dd-]hh:mm:ss` format (time=TIME), and the executable name (`ucmd`=`CMD`). Output is unsorted by default.

```bash
[tensorflow@localhost ~]$ ps
  PID TTY          TIME CMD
 1741 pts/0    00:00:00 bash
 2109 pts/0    00:00:00 ps
```



The use of BSD-style options will add **process state** (stat=STAT) to the default display and show the command `args` (`args`=COMMAND) instead of the executable name. You can override this with the **PS_FORMAT** environment variable. The use of BSD-style options will also change the **process selection** to include processes on other terminals (TTYs) that are owned by you; alternately, this may be described as setting the selection to be the set of all processes filtered to exclude processes owned by other users or not on a terminal. These effects are not considered when options are described as being "identical" below, so **-M** will be considered identical to **Z** and so on.

Except as described below, **process selection options** are additive. The default selection is discarded, and then the selected processes are added to the set of processes to be displayed. A process will thus be shown if it meets any of the given selection criteria.

## Examples

### All process

To see every process on the system using standard syntax:

```bash
ps -e
ps -ef
ps -eF
ps -ely
```

To see every process on the system using BSD syntax:

```bash
ps ax
ps axu
```

### Process tree

To print a process tree:

```bash
ps -ejH
ps axjf
```

### Threads

To get info about threads:

```bash
ps -eLf
ps axms
```

### Security info

To get security info:

```bash
ps -eo euser,ruser,suser,fuser,f,comm,label
ps axZ
ps -eM
```

### Run as root

To see every process running as root (real & effective ID) in **user format**:

```bash
ps -U root -u root u
```

### User-defined format

To see every process with a user-defined format:

```bash
ps -eo pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:14,comm
ps axo stat,euid,ruid,tty,tpgid,sess,pgrp,ppid,pid,pcpu,comm
ps -eopid,tt,user,fname,tmout,f,wchan
```

### Process ID of

Print only the process IDs of `syslogd`:

```bash
ps -C syslogd -o pid=
```

### Name of

Print only the name of PID 42:

```bash
ps -p 42 -o comm=
```



### `ps -x`



## Process Selection

> NOTE: 使用`ps`的一个非常重要的内容是：process selection

### Simple Process Selection



### Process Selection By List

These options accept a single argument in the form of a blank-separated or comma-separated list. They can be used multiple times. For example: `ps -p "1 2" -p 3,4`

#### `-C cmdlist`

Select by **command name**.

This selects the processes whose **executable name** is given in *cmdlist*.

#### `-G grplist`

Select by **real group ID** (RGID) or name.

This selects the processes whose **real group name** or ID is in the *grplist* list. The **real group ID** identifies the group of the user who created the process, see [**getgid**(2)](https://linux.die.net/man/2/getgid).



## Output Format Control

These options are used to choose the information displayed by **ps**. The output may differ by personality.

### `-F`

extra full format. See the **-f** option, which **-F** implies.

### `-O format`







## Output Modifiers





## Thread Display



## Other Information





## Notes

This **ps** works by reading the virtual files in `/proc`. This **ps** does not need to be `setuid kmem` or have any privileges to run. Do not give this **ps** any special permissions.

> NOTE: 参见`Programming\Process\Proc-filesystem`。



This **ps** needs access to namelist data for proper WCHAN display. For kernels prior to 2.6, the System.map file must be installed.

> NOTE
>
> wikipedia [System.map](https://en.wikipedia.org/wiki/System.map)

### CPU usage 

CPU usage is currently expressed as the percentage of time spent running during the entire lifetime of a process. This is not ideal, and it does not conform to the standards that **ps** otherwise conforms to. CPU usage is unlikely to add up to exactly 100%.

### `SIZE` and `RSS`

The `SIZE` and `RSS` fields don't count some parts of a process including the page tables, kernel stack, struct thread_info, and struct task_struct. This is usually at least 20 KiB of memory that is always resident. SIZE is the virtual size of the process (code+data+stack).

### `<defunct>`

Processes marked `<defunct>` are dead processes (so-called "zombies") that remain because their parent has not destroyed them properly. These processes will be destroyed by **init**(8) if the parent process exits.

If the length of the username is greater than the length of the display column, the numeric user ID is displayed instead.

### `System.map` file

This **ps** needs access to namelist data for proper `WCHAN` display. For kernels prior to 2.6, the `System.map` file must be installed.

> NOTE:
>
> 本段所描述的问题，在stackoverflow [in ps -l, what does wchan=stext mean?](https://stackoverflow.com/questions/404854/in-ps-l-what-does-wchan-stext-mean) 中也对这个问题进行了探讨。
>
> 关于`System.map` file，参见`Kernel\Guide\Debug\System.map`。

## Process Flags

The sum of these values is displayed in the "F" column, which is provided by the **flags** output specifier.

- 1 forked but didn't exec
- 4 used super-user privileges

> NOTE: 没有理解意思

## Process State Codes

> NOTE: Process State 非常重要

Here are the different values that the **s**, **stat** and **state** output specifiers (header "STAT" or "S") will display to describe the state of a process.

### `D`

Uninterruptible sleep (usually IO)

> NOTE: docstore [21.7. Hanging Processes: Detection and Diagnostics ](https://docstore.mik.ua/orelly/weblinux2/modperl/ch21_07.htm)中，有这样的描述:
>
> '`D`' **disk wait** in `ps` report
>
> 所以，我觉得`D`应该代表的就是disk wait。

### `I`

Idle kernel thread

### R

Running or runnable (on run queue)

### S

Interruptible sleep (waiting for an event to complete)

### T

Stopped, either by a job control signal or because it is being traced.

### W

paging (not valid since the 2.6.xx kernel)

### X

dead (should never be seen)

### Z

Defunct ("zombie") process, terminated but not reaped by its parent.



For BSD formats and when the **stat** keyword is used, additional characters may be displayed:

### <

high-priority (not nice to other users)

### N

low-priority (nice to other users)

### L

has pages locked into memory (for real-time and custom IO)

> NOTE: 关于此，参见:
>
> - docstore [21.7.1. Hanging Because of an Operating System Problem](https://docstore.mik.ua/orelly/weblinux2/modperl/ch21_07.htm) 

### s

is a session leader

### `l`

is multi-threaded (using `CLONE_THREAD`, like NPTL pthreads do)

### +

is in the foreground process group



## STANDARD FORMAT SPECIFIERS 



## ENVIRONMENT VARIABLES  



## PERSONALITY     