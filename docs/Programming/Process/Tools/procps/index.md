# 关于本章

本章描述procps。

## procps

gitlab [procps](https://gitlab.com/procps-ng/procps) 

| command | introduction                                                 |
| ------- | ------------------------------------------------------------ |
| free    | Report the amount of free and used memory in the system      |
| kill    | Send a signal to a process based on PID                      |
| pgrep   | List processes based on name or other attributes             |
| pkill   | Send a signal to a process based on name or other attributes |
| pmap    | Report memory map of a process                               |
| ps      | Report information of processes                              |
| pwdx    | Report current directory of a process                        |
| skill   | Obsolete version of pgrep/pkill                              |
| slabtop | Display kernel slab cache information in real time           |
| snice   | Renice a process                                             |
| sysctl  | Read or Write kernel parameters at run                       |
| tload   | Graphical representation of system load average              |
| top     | Dynamic real                                                 |
| uptime  | Display how long the system has been running                 |
| vmstat  | Report virtual memory statistics                             |
| w       | Report logged in users and what they are doing               |
| watch   | Execute a program periodically, showing output fullscreen    |



## [What is the difference between ps and top command?](https://unix.stackexchange.com/questions/62176/what-is-the-difference-between-ps-and-top-command)



### [A](https://unix.stackexchange.com/a/62186)

`top` is mostly used interactively (try reading man page or pressing "h" while `top` is running) and `ps` is designed for non-interactive use (scripts, extracting some information with shell pipelines etc.)



### [A](https://unix.stackexchange.com/a/62190)

`top` allows you display of process statistics continuously until stopped vs. `ps` which gives you a single snapshot.



### [A](https://unix.stackexchange.com/a/497650)

For CPU usage, `ps` displays average CPU usage over the lifetime of the process as it is instantaneous and would always be 0% or 100%. `top` gives a more instantaneous look at it from averaging over recent polls.

More information here: [Top and ps not showing the same cpu result](https://unix.stackexchange.com/questions/58539/top-and-ps-not-showing-the-same-cpu-result)