

# 1.6.6. Signals and Interprocess Communication

Unix signals provide a mechanism for notifying processes of system events. Each event has its own signal number, which is usually referred to by a symbolic constant such as  `SIGTERM` . There are two kinds of system events:

*Asynchronous notifications*

For instance, a user can send the interrupt signal  `SIGINT` to a foreground process by pressing the interrupt keycode (usually Ctrl-C) at the terminal.

*Synchronous notifications*

For instance, the kernel sends the signal  `SIGSEGV` to a process when it accesses a memory location at an invalid address.

