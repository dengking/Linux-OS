# [5 Stopping and Continuing](https://sourceware.org/gdb/current/onlinedocs/gdb/Stopping.html#Stopping)

## 5.1 Breakpoints, Watchpoints, and Catchpoints

增

|            | command |      |      |
| ---------- | ------- | ---- | ---- |
| breakpoint | `break` |      |      |
| watchpoint | `watch` |      |      |
| catchpoint | `catch` |      |      |

查

`info break`

删

5.1.4 Deleting Breakpoints节

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

## [5.2 Continuing and Stepping](https://sourceware.org/gdb/current/onlinedocs/gdb/Continuing-and-Stepping.html#Continuing-and-Stepping)



### step vs next

单步执行:

| `step`         | `next`         |
| -------------- | -------------- |
| step会进入函数 | next不进入函数 |
| 逐语句         | 逐过程         |
|                |                |

