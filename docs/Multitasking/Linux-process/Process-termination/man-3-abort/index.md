# abort(3)

## [abort(3)](https://www.man7.org/linux/man-pages/man3/abort.3.html) 



## core by 6) `SIGABRT`

今天编写的程序刚刚开始运行就core了，查看core文件，信息如下：

```bash
[quotepredict@localhost redis_client]$ gdb redis_client_test core.22164 
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-80.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/quotepredict/src/test/QuotePredict/tests/core/redis_client/redis_client_test...done.

warning: core file may not match specified executable file.
[New LWP 22164]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
Core was generated by `./redis_client_test'.
Program terminated with signal 6, Aborted.
#0  0x00007fc50261e1d7 in raise () from /lib64/libc.so.6
Missing separate debuginfos, use: debuginfo-install glibc-2.17-157.el7_3.1.x86_64 libuuid-2.23.2-26.el7.x86_64 zookeeper-3.4.10-1.el7.x86_64
(gdb) where
#0  0x00007fc50261e1d7 in raise () from /lib64/libc.so.6
#1  0x00007fc50261f8c8 in abort () from /lib64/libc.so.6
#2  0x00007fc502f21b05 in __gnu_cxx::__verbose_terminate_handler() () from /usr/anaconda3/lib/libstdc++.so.6
#3  0x00007fc502f1fca6 in ?? () from /usr/anaconda3/lib/libstdc++.so.6
#4  0x00007fc502f1fcd3 in std::terminate() () from /usr/anaconda3/lib/libstdc++.so.6
#5  0x00007fc502f1fef2 in __cxa_throw () from /usr/anaconda3/lib/libstdc++.so.6
#6  0x000000000040a31c in RedisClient (conf=..., this=<optimized out>)
    at ../../../core/redis_client/../../third_party/hiredispool/RedisClient.h:119
#7  RedisIO::RedisClientExtend::RedisClientExtend (this=<optimized out>, conf=...) at ../../../core/redis_client/redis_client.cpp:46
#8  0x000000000040a3d7 in RedisIO::RedisClientExtend::NewRedisClientExtend (host=..., port=port@entry=6379, 
    num_redis_socks=num_redis_socks@entry=1) at ../../../core/redis_client/redis_client.cpp:42
#9  0x0000000000403f7d in main () at redis_client_test.cpp:12
(gdb) 

```

看了代码，原来是程序中主动抛出exception而导致的
```C++
    RedisClient(const REDIS_CONFIG& conf) {
        if (redis_pool_create(&conf, &inst) < 0)
            throw std::runtime_error("Can't create pool");
    }

```


## stackoverflow [Difference between raise(SIGABRT) and abort() methods](https://stackoverflow.com/questions/20212927/difference-between-raisesigabrt-and-abort-methods)



## stackoverflow [When does a process get SIGABRT (signal 6)?](https://stackoverflow.com/questions/3413166/when-does-a-process-get-sigabrt-signal-6)



> NOTE: call不到`nim_api::sdkInit`，所以，跳转到了libdyld.dylib`_dyld_missing_symbol_abort:
