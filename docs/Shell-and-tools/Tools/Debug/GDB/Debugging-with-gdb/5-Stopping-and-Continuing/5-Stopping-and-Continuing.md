# [5 Stopping and Continuing](https://sourceware.org/gdb/current/onlinedocs/gdb/Stopping.html#Stopping)

## 5.1 Breakpoints, Watchpoints, and Catchpoints



| 名称       | 说明                                                         | command |      |      |
| ---------- | ------------------------------------------------------------ | ------- | ---- | ---- |
| breakpoint | A **breakpoint** makes your program stop whenever a certain point(location) in the program is reached. | `break` |      |      |
| watchpoint | A **watchpoint** is a special breakpoint that stops your program when the value of an expression changes. | `watch` |      |      |
| catchpoint | A catchpoint is another special breakpoint that stops your program when a certain kind of event occurs, such as the throwing of a C++ exception or the loading of a library. | `catch` |      |      |

查

`info break`

删

5.1.4 Deleting Breakpoints节

### 5.1.1 Setting Breakpoints

| ccomand             | 说明                                                         |                           |
| ------------------- | ------------------------------------------------------------ | ------------------------- |
| `break location`    |                                                              |                           |
| `break`             | When called without any arguments, break sets a breakpoint at the next instruction to be executed in the selected stack frame |                           |
| `break ... if cond` | Set a breakpoint with condition `cond`;                      | 具体用法参见下面的example |
| `tbreak args`       | Set a breakpoint enabled only for one stop                   | temporary breakpoint      |
| `hbreak args`       | Set a hardware-assisted breakpoint.                          |                           |
| `thbreak args`      | Set a hardware-assisted breakpoint enabled only for one stop. |                           |
| `rbreak regex`      | Set breakpoints on all functions matching the regular expression regex. |                           |
| `rbreak file:regex` | If `rbreak` is called with a filename qualification, it limits the search for functions matching the given regular expression to the specified file. |                           |

#### Example

**`break ... if cond`** 

stackoverflow [GDB: break if variable equal value](https://stackoverflow.com/questions/14390256/gdb-break-if-variable-equal-value)的[回答](https://stackoverflow.com/a/14390740) 给出了它的用法：

in addition to a **watchpoint** nested inside a breakpoint you can also set a single breakpoint on the 'filename:line_number' and use a condition. I find it sometimes easier.

```c
(gdb) break iter.c:6 if i == 5
Breakpoint 2 at 0x4004dc: file iter.c, line 6.
(gdb) c
Continuing.
0
1
2
3
4

Breakpoint 2, main () at iter.c:6
6           printf("%d\n", i);
```

If like me you get tired of line numbers changing, you can add a label then set the breakpoint on the label like so:

```c
#include <stdio.h>
main()
{ 
     int i = 0;
     for(i=0;i<7;++i) {
       looping:
        printf("%d\n", i);
     }
     return 0;
}

(gdb) break main:looping if i == 5
```

### 5.1.2 Setting Watchpoints





#### Example

stackoverflow [GDB: break if variable equal value](https://stackoverflow.com/questions/14390256/gdb-break-if-variable-equal-value):

```c
#include <stdio.h>
main()
{ 
     int i = 0;
     for(i=0;i<7;++i)
        printf("%d\n", i);

     return 0;
}
```

[A](https://stackoverflow.com/a/14390352)

You can use a watchpoint for this (A breakpoint on data instead of code).

You can start by using `watch i`.
Then set a condition for it using `condition <breakpoint num> i == 5`

You can get the breakpoint number by using `info watch`



### 5.1.3 Setting Catchpoints

```shell
catch event
```

| event                                                 | 命令格式             | 语言 | 说明                                                      |
| ----------------------------------------------------- | -------------------- | ---- | --------------------------------------------------------- |
| throw、rethrow、catch                                 | `cat event [regexp]` | C++  | The throwing, re-throwing, or catching of a C++ exception |
| exception                                             |                      | Ada  | An Ada exception being raised                             |
| exception unhandled                                   |                      | Ada  |                                                           |
| assert                                                |                      | Ada  |                                                           |
| exec                                                  |                      |      |                                                           |
| `syscall [name|number|group:groupname |g:groupname ]` |                      |      | A call to or return from a system call, a.k.a. syscall.   |
| fork                                                  |                      |      | A call to fork.                                           |
| vfork                                                 |                      |      | A call to vfork.                                          |
| `load [regexp]`、`unload [regexp]`                    |                      |      | The loading or unloading of a shared library              |
| `signal [signal... | all ]`                           |                      |      | The delivery of a signal.                                 |

#### Example

##### 找出抛出异常的语句

```C++
$ gdb a.out
(gdb) catch throw
Function "__cxa_throw" not defined.
Catchpoint 1 (throw)
(gdb) r
[New Thread 0x7ffff7ff0700 (LWP 3121)]
[New Thread 0x7ffff5f53700 (LWP 3122)]
tcp://127.0.0.1:8001
[New Thread 0x7ffff5752700 (LWP 3123)]
[New Thread 0x7ffff4f51700 (LWP 3124)]
[New Thread 0x7ffff4daf700 (LWP 3125)]
[Switching to Thread 0x7ffff5752700 (LWP 3123)]
Catchpoint 1 (exception thrown), 0x00007ffff6eb2920 in __cxa_throw () from /usr/lib64/libstdc++.so.6
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64
(gdb) bt
#0  0x00007ffff6eb2920 in __cxa_throw () from /usr/lib64/libstdc++.so.6
#1  0x00007ffff72f060e in CppSQLite3DB::open (this=<optimized out>, szFile=<optimized out>) at ./cpp_sqlite3/CppSQLite3.cpp:1216
#2  0x00007ffff7297651 in CHSInsTradeApiCacheService_ust::ApiPushCacheInit (this=0x63a760, 
    cacheFileName=cacheFileName@entry=0x7ffff573e400 "./log/STOCKOPT_HSINSAPI_20200730_1082", svrMaxSerialno=1998)
    at trade_api_cache.cpp:250

```

通过`bt`来查看stack frame，frame `#1`指示了抛出exception的语句；

##### `catch syscall`

```shell
(gdb) catch syscall
Catchpoint 1 (syscall)
(gdb) r
Starting program: /tmp/catch-syscall
Catchpoint 1 (call to syscall ’close’), \
0xffffe424 in __kernel_vsyscall ()
(gdb) c
Continuing.
Catchpoint 1 (returned from syscall ’close’), \
0xffffe424 in __kernel_vsyscall ()
(gdb)
```

##### `catch syscall chroot`

```
(gdb) catch syscall chroot
Catchpoint 1 (syscall ’chroot’ [61])
(gdb) r
Starting program: /tmp/catch-syscall
Catchpoint 1 (call to syscall ’chroot’), \
0xffffe424 in __kernel_vsyscall ()
(gdb) c
Continuing.
Catchpoint 1 (returned from syscall ’chroot’), \
0xffffe424 in __kernel_vsyscall ()
(gdb)
```

### 5.1.4 Deleting Breakpoints

#### `clear`

### 5.1.6 Break Conditions

The simplest sort of breakpoint breaks every time your program reaches a specified place. You can also specify a ***condition*** for a breakpoint. A condition is just a Boolean expression in your programming language (see Section 10.1 [Expressions], page 117). A breakpoint with a condition evaluates the expression each time your program reaches it, and your program stops only if the condition is ***true***.

#### Break Condition VS assertion

...

#### Break Condition VS watchpoint

...



Break conditions can be specified when a breakpoint is set, by using ‘if’ in the arguments to the break command. See Section 5.1.1 [Setting Breakpoints], page 46. They can also be changed at any time with the condition command.

You can also use the if keyword with the watch command. The catch command does not recognize the if keyword; condition is the only way to impose a further condition on a catchpoint.

#### `condition bnum expression`

Specify expression as the break condition for breakpoint, watchpoint, or catchpoint number `bnum`. 

#### `condition bnum`

Remove the condition from breakpoint number `bnum`.



#### Example: specify a condition on an existing breakpoint

文章fayewilliams [GDB Conditional Breakpoints](https://www.fayewilliams.com/2011/07/13/gdb-conditional-breakpoints/)中给出了一些例子：

example: specify a condition on an existing breakpoint by using the breakpoint number as a reference

You can also specify a condition on an existing breakpoint by using the breakpoint number as a reference:

```
cond 3 i == 99
```

```
cond 3
```



#### Example: break if variable equal value

[GDB Conditional Breakpoints](https://www.fayewilliams.com/2011/07/13/gdb-conditional-breakpoints/)中给出的例子：

```shell
b Message.cpp:112 if i == 99
```

我的实践:

```shell
b CHQImpl::DealMessage
info locals
cond 1 nFuncNo=107
```

上述表达的是：当函数`CHQImpl::DealMessage`的临时变量`nFuncNo`的值为`107`时，则break。

[GDB: break if variable equal value](https://stackoverflow.com/questions/14390256/gdb-break-if-variable-equal-value)中给出的例子：

I like to make GDB set a break point when a variable equal some value I set, I tried this example:

```c
#include <stdio.h>
main()
{ 
     int i = 0;
     for(i=0;i<7;++i)
        printf("%d\n", i);

     return 0;
}
```

[A](https://stackoverflow.com/a/14390740):

```shell
(gdb) break iter.c:6 if i == 5
Breakpoint 2 at 0x4004dc: file iter.c, line 6.
(gdb) c
Continuing.
0
1
2
3
4

Breakpoint 2, main () at iter.c:6
6           printf("%d\n", i);
```

If like me you get tired of line numbers changing, you can add a label then set the breakpoint on the label like so:

```c
#include <stdio.h>
main()
{ 
     int i = 0;
     for(i=0;i<7;++i) {
       looping:
        printf("%d\n", i);
     }
     return 0;
}

(gdb) break main:looping if i == 5
```



#### Example: 更加复杂的条件

[GDB Conditional Breakpoints](https://www.fayewilliams.com/2011/07/13/gdb-conditional-breakpoints/)中给出的例子：

Pretty much anything you like! Just write the condition exactly as if you were testing for it in your code, e.g.:

```shell
(gdb) cond 1 strcmp(message,"earthquake") == 0
//stop if the array message is equal to 'earthquake'
```



```shell
(gdb) cond 2 *p == 'r'
//stop if the char* pointer p points to the letter 'r'
```



```
(gdb) cond 3 num < 0.75
//stop while the float num is less than 0.75
```



### 5.1.7 Breakpoint Command Lists

> NOTE: 这是automatic gdb debug的基础。

You can give any **breakpoint** (or **watchpoint** or **catchpoint**) a series of commands to execute when your program stops due to that **breakpoint**. For example, you might want to print the values of certain expressions, or enable other breakpoints.

```
commands [range...]
... command-list ...
end
```



#### Example: print variable

For example, here is how you could use breakpoint commands to print the value of `x` at entry to `foo` whenever `x` is positive.

```shell
break foo if x>0
commands
silent
printf "x is %d\n",x
cont
end
```



#### Example:  compensate for one bug

One application for breakpoint commands is to compensate(偿还) for one bug so you can test for another. 

Put a breakpoint just after the erroneous line of code, give it a condition to detect the case in which something erroneous has been done, and give it commands to assign correct values to any variables that need them. End with the continue command so that your program does not stop, and start with the silent command so that no output is produced. Here is an example:

```
break 403
commands
silent
set x = y + 4
cont
end
```





## [5.2 Continuing and Stepping](https://sourceware.org/gdb/current/onlinedocs/gdb/Continuing-and-Stepping.html#Continuing-and-Stepping)



### step vs next

单步执行:

| `step`         | `next`         |
| -------------- | -------------- |
| step会进入函数 | next不进入函数 |
| 逐语句         | 逐过程         |

### 单位

- 以function为单位 `next`

- 以statement/source line为单位 `step`

- 以instruction为单位 `stepi`、`nexti`

  > NOTE: 主要用于debug assembly，关于debug assembly，参见`Shell-and-tools\Tools\Debug\GDB\Guide\Debug-assembly.md`

