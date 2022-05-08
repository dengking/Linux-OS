# [DAEMON(7)](http://man7.org/linux/man-pages/man7/daemon.7.html)

## DESCRIPTION

A daemon is a service process that runs in the background and supervises the system or provides functionality to other processes. Traditionally, daemons are implemented following a scheme originating in SysV Unix. Modern daemons should follow a simpler yet more powerful scheme (here called "new-style" daemons), as implemented by [systemd(1)](http://man7.org/linux/man-pages/man1/systemd.1.html). This manual page covers both schemes, and in particular includes recommendations for daemons that shall be included in the systemd init system.

### SysV Daemons

When a traditional SysV daemon starts, it should execute the following steps as part of the initialization. Note that these steps are unnecessary for new-style daemons (see below), and should only be implemented if compatibility with SysV is essential.

1. Close all open file descriptors except standard input, output, and error (i.e. the first three file descriptors 0, 1, 2). This ensures that no accidentally passed file descriptor stays around in the **daemon process**. On Linux, this is best implemented by iterating through `/proc/self/fd`, with a fallback of iterating from file descriptor 3 to the value returned by `getrlimit()` for `RLIMIT_NOFILE`.

> NOTE: 文件描述符标志[close-on-exec](http://man7.org/linux/man-pages/man2/fcntl.2.html)

2. Reset all signal handlers to their default. This is best done by iterating through the available signals up to the limit of `_NSIG` and resetting them to `SIG_DFL`.
  
3. Reset the signal mask using sigprocmask().

4. Sanitize the environment block, removing or resetting environment variables that might negatively impact daemon runtime.
  
5. Call `fork()`, to create a background process.

6. In the child, call `setsid()` to detach from any terminal and create an **independent session**.
  
7. In the child, call `fork()` again, to ensure that the daemon can never re-acquire a terminal again.
  
8. Call `exit()` in the first child, so that only the second child (the actual daemon process) stays around. This ensures that the daemon process is re-parented to init/PID 1, as all daemons should be.
  
9. In the daemon process, connect `/dev/null` to standard input, output, and error.
  
10. In the daemon process, reset the `umask` to 0, so that the file modes passed to `open()`, `mkdir()` and suchlike directly control the access mode of the created files and directories.
  
11. In the **daemon process**, change the **current directory** to the root directory (/), in order to avoid that the daemon involuntarily（无意的） blocks mount points from being unmounted.
   
12. In the daemon process, write the daemon `PID` (as returned by `getpid()`) to a `PID` file, for example `/run/foobar.pid` (for a hypothetical daemon "`foobar`") to ensure that the daemon cannot be started more than once. This must be implemented in race-free fashion so that the `PID` file is only updated when it is verified at the same time that the `PID` previously stored in the `PID` file no longer exists or belongs to a foreign process.
   
13. In the daemon process, drop privileges, if possible and applicable.
   
14. From the daemon process, notify the original process started that initialization is complete. This can be implemented via an unnamed pipe or similar communication channel that is created before the first `fork()` and hence available in both the original and the daemon process.
   
15. Call `exit()` in the original process. The process that invoked the daemon must be able to rely on that this exit() happens after initialization is complete and all external communication channels are established and accessible.

The BSD `daemon()` function should not be used, as it implements only a subset of these steps.

A daemon that needs to provide compatibility with SysV systems should implement the scheme pointed out above. However, it is recommended to make this behavior optional and configurable via a command line argument to ease debugging as well as to simplify integration into systems using systemd.