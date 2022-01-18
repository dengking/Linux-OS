# Tracepoints



## gdb onlinedocs [13 Tracepoints](https://sourceware.org/gdb/current/onlinedocs/gdb/Tracepoints.html#Tracepoints)

In some applications, it is not feasible for the debugger to interrupt the program’s execution long enough for the developer to learn anything helpful about its behavior. If the program’s correctness depends on its real-time behavior, delays introduced by a debugger might cause the program to change its behavior drastically, or perhaps fail, even when the code itself is correct. It is useful to be able to observe the program’s behavior without interrupting it.

> NOTE: 上面这段话已经说明了tracepoint和breakpoints（breakpoint、watchpoint、catchpoint）之间的差异所在



TO READ

- suchakra.wordpress [Fast Tracing with GDB](https://suchakra.wordpress.com/2016/06/29/fast-tracing-with-gdb/)