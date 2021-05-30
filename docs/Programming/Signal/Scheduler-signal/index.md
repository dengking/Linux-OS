# Scheduler signal

1、suspend(stop) 和 resume(restart、continue)

2、参见bash [7 Job Control](https://www.gnu.org/software/bash/manual/html_node/Job-Control.html#Job-Control)

## suspend(stop) 

在 [signal(7)](https://www.man7.org/linux/man-pages/man7/signal.7.html) 中，提及了"stop signals"，它应该主要包括:

1、`SIGSTOP` 

2、`SIGTSTP`

### stackoverflow [What is the difference between SIGSTOP and SIGTSTP?](https://stackoverflow.com/questions/11886812/what-is-the-difference-between-sigstop-and-sigtstp)



**A**

Both signals are designed to suspend a process which will be eventually resumed with `SIGCONT`. The main differences between them are:

1、`SIGSTOP` is a signal sent programmatically (eg: `kill -STOP pid` ) while `SIGTSTP` (for ***sig****nal - **t**erminal **stop***) may also be sent through the `tty` driver by a user typing on a keyboard, usually Control-Z.

2、`SIGSTOP` cannot be ignored. `SIGTSTP` might be.



**A**

`/usr/include/x86_64-linux-gnu/bits/signum.h`

```
#define SIGSTOP     19  /* Stop, unblockable (POSIX).  */
#define SIGTSTP     20  /* Keyboard stop (POSIX).  */
```



## resume(restart、continue)

`SIGCONT` signal