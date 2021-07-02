# Termination Signals

## gnu libc [gnu libc Termination Signals](https://www.gnu.org/software/libc/manual/html_node/Termination-Signals.html)

These signals are all used to tell a process to **terminate**, in one way or another. They have different names because they’re used for slightly different purposes, and programs might want to handle them differently.

### **SIGTERM**

The `SIGTERM` signal is a generic signal used to cause program termination. Unlike `SIGKILL`, this signal can be blocked, handled, and ignored. It is the normal way to politely ask a program to terminate.

The shell command `kill` generates `SIGTERM` by default.

### SIGINT

The `SIGINT` (“program interrupt”) signal is sent when the user types the INTR character (normally C-c). See [Special Characters](https://www.gnu.org/software/libc/manual/html_node/Special-Characters.html), for information about terminal driver support for C-c.



### SIGQUIT

The `SIGQUIT` signal is similar to `SIGINT`, except that it’s controlled by a different key—the QUIT character, usually `C-\—`and produces a core dump when it terminates the process, just like a program error signal. You can think of this as a program error condition “detected” by the user.

See [Program Error Signals](https://www.gnu.org/software/libc/manual/html_node/Program-Error-Signals.html), for information about core dumps. See [Special Characters](https://www.gnu.org/software/libc/manual/html_node/Special-Characters.html), for information about terminal driver support.

Certain kinds of cleanups are best omitted in handling `SIGQUIT`. For example, if the program creates temporary files, it should handle the other termination requests by deleting the temporary files. But it is better for `SIGQUIT` not to delete them, so that the user can examine them in conjunction with the core dump.

### SIGKILL

The `SIGKILL` signal is used to cause immediate program termination. It cannot be handled or ignored, and is therefore always fatal. It is also not possible to block this signal.

This signal is usually generated only by explicit request. Since it cannot be handled, you should generate it only as a last resort, after first trying a less drastic method such as C-c or `SIGTERM`. If a process does not respond to any other termination signals, sending it a `SIGKILL` signal will almost always cause it to go away.

In fact, if `SIGKILL` fails to terminate a process, that by itself constitutes an operating system bug which you should report.

The system will generate `SIGKILL` for a process itself under some unusual conditions where the program cannot possibly continue to run (even to run a signal handler).



### SIGHUP

The `SIGHUP` (“hang-up”) signal is used to report that the user’s terminal is disconnected, perhaps because a network or telephone connection was broken. For more information about this, see [Control Modes](https://www.gnu.org/software/libc/manual/html_node/Control-Modes.html).

This signal is also used to report the termination of the controlling process on a terminal to jobs associated with that session; this termination effectively disconnects all processes in the session from the controlling terminal. For more information, see [Termination Internals](https://www.gnu.org/software/libc/manual/html_node/Termination-Internals.html).

## See also

### 《`APUE-10.2 Signal Concepts.md`》

在《`APUE-10.2 Signal Concepts.md`》中总结了`SIGKILL` 和 `SIGTERM`的异同

major [SIGTERM vs. SIGKILL](https://major.io/2010/03/18/sigterm-vs-sigkill/)

[Redis Signals Handling](https://redis.io/topics/signals)是了解一些信号的非常好的example

在celery中也涉及了[Process Signals](https://docs.celeryproject.org/en/latest/userguide/workers.html#id4)

`ctr-c` 也会终止一个process，并且即使此时的process中的某个thread处于sleeping状态，也依然会将此process给干掉



