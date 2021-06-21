# [select_tut(2)](https://www.man7.org/linux/man-pages/man2/select_tut.2.html) 

## Combining signal and data events

`pselect()` is useful if you are waiting for a signal as well as for file descriptor(s) to become ready for I/O.  Programs that receive signals normally use the signal handler only to raise a global flag.  The global flag will indicate that the event must be processed in the main loop of the program.  A signal will cause the select() (or pselect()) call to return with errno set to EINTR.  This behavior is essential so that signals can be processed in the main loop of the program, otherwise select() would block indefinitely.