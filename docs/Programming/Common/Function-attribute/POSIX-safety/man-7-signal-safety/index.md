# [SIGNAL-SAFETY(7)](http://man7.org/linux/man-pages/man7/signal-safety.7.html)

signal-safety - async-signal-safe functions



An **async-signal-safe** function is one that can be safely called from within a **signal handler**.  Many functions are not **async-signal-safe**.  In particular, **nonreentrant functions** are generally unsafe to call from a **signal handler**.



When performing buffered I/O on a file, the stdio functions must maintain a **statically allocated data buffer** along with associated **counters** and **indexes** (or pointers) that record the amount of data and the current position in the buffer.  Suppose that the main program is in the middle of a call to a stdio function such as `printf(3)` where the buffer and associated variables have been partially updated.  If, at that moment, the program is interrupted by a **signal handler** that also calls `printf(3)`, then the second call to `printf(3)` will operate on inconsistent data, with unpredictable results.
