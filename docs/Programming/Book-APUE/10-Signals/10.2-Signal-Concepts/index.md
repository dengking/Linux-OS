# 10.2 Signal Concepts



The **core file** will not be generated if 

(a) the process was **set-user-ID** and the current user is not the owner of the program file, 

(b) the process was **set-group-ID** and the current user is not the group owner of the file, 

(c) the user does not have permission to write in the **current working directory**, 

(d) the file already exists and the user does not have permission to write to it, or 

(e) the file is too big (recall the `RLIMIT_CORE` limit in Section 7.11). 

The permissions of the core file (assuming that the file doesn’t already exist) are usually user-read and user-write, although Mac OS X sets only user-read.

> NOTE: 上面这段话中的the process was set-user-ID是什么意思？是否是在图4-8中的例子；



## SIGKILL 和 SIGTERM的异同

`SIGKILL` ,This signal is one of the two that can’t be caught or ignored. It provides the system administrator with a sure way to kill any process.

`SIGTERM` This is the termination signal sent by the kill(1) command by default. Because it can be caught by applications, using `SIGTERM` gives programs a chance to terminate gracefully by cleaning up before exiting (in contrast to `SIGKILL`, which can’t be caught or ignored).

