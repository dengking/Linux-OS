# [ps (Unix)](https://en.wikipedia.org/wiki/Ps_(Unix))

In most [Unix-like](https://en.wikipedia.org/wiki/Unix-like) [operating systems](https://en.wikipedia.org/wiki/Operating_systems), the **ps** program (short for "**p**rocess **s**tatus") displays the currently-running [processes](https://en.wikipedia.org/wiki/Process_(computing)). A related Unix utility named [top](https://en.wikipedia.org/wiki/Top_(software)) provides a real-time view of the running processes.

In [Windows PowerShell](https://en.wikipedia.org/wiki/Windows_PowerShell), `ps` is a predefined [command alias](https://en.wikipedia.org/wiki/Alias_(command)) for the `Get-Process` cmdlet, which essentially serves the same purpose.

## Examples

For example:

```shell
# ps
  PID TTY          TIME CMD
 7431 pts/0    00:00:00 su
 7434 pts/0    00:00:00 bash
18585 pts/0    00:00:00 ps
```

Users can also utilize the `ps` command in conjunction with the [`grep`](https://en.wikipedia.org/wiki/Grep) command (see the [`pgrep`](https://en.wikipedia.org/wiki/Pgrep) and [`pkill`](https://en.wikipedia.org/wiki/Pgrep) commands) to find information about a single process, such as its id:

```shell
$ # Trying to find the PID of `firefox-bin` which is 2701
$ ps -A | grep firefox-bin
2701 ?        22:16:04 firefox-bin
```

The use of `pgrep` simplifies the syntax and avoids potential [race conditions](https://en.wikipedia.org/wiki/Race_condition):

```shell
$ pgrep -l firefox-bin
2701 firefox-bin
```

To see every process running as root in user format:

```shell
# ps -U root -u
USER   PID  %CPU %MEM    VSZ   RSS TT  STAT STARTED        TIME COMMAND
root     1   0.0  0.0   9436   128  -  ILs  Sun00AM     0:00.12 /sbin/init --
```

## Break Down

| Column Header  |                           Contents                           |
| :------------: | :----------------------------------------------------------: |
|      %CPU      |           How much of the CPU the process is using           |
|      %MEM      |             How much memory the process is using             |
|      ADDR      |                Memory address of the process                 |
|    C or CP     |             CPU usage and scheduling information             |
|    COMMAND*    |       Name of the process, including arguments, if any       |
|       NI       |   [nice](https://en.wikipedia.org/wiki/Nice_(Unix)) value    |
|       F        |                            Flags                             |
|      PID       |                      Process ID number                       |
|      PPID      |          ID number of the process′s parent process           |
|      PRI       |                   Priority of the process                    |
|      RSS       | [Resident set size](https://en.wikipedia.org/wiki/Resident_set_size) |
|   S or STAT    |                     Process status code                      |
| START or STIME |                Time when the process started                 |
|      VSZ       |                     Virtual memory usage                     |
|      TIME      |          The amount of CPU time used by the process          |
|   TT or TTY    |             Terminal associated with the process             |
|  UID or USER   |               Username of the process′s owner                |
|     WCHAN      |    Memory address of the event the process is waiting for    |

\* = Often abbreviated

## Options

`ps` has many options. On [operating systems](https://en.wikipedia.org/wiki/Operating_system) that support the [SUS](https://en.wikipedia.org/wiki/Single_UNIX_Specification) and [POSIX](https://en.wikipedia.org/wiki/POSIX) standards, `ps` commonly runs with the options **-ef**, where "-e" selects **e**very process and "-f" chooses the "**f**ull" output format. Another common option on these systems is **-l**, which specifies the "**l**ong" output format.

Most systems derived from [BSD](https://en.wikipedia.org/wiki/BSD) fail to accept the SUS and POSIX standard options because of historical conflicts. (For example, the "e" or "-e" option will display [environment variables](https://en.wikipedia.org/wiki/Environment_variable).) On such systems, `ps` commonly runs with the non-standard options **aux**, where "a" lists all processes on a [terminal](https://en.wikipedia.org/wiki/Computer_terminal), including those of other users, "x" lists all processes without [controlling terminals](https://en.wikipedia.org/w/index.php?title=Controlling_terminal&action=edit&redlink=1) and "u" adds a column for the controlling user for each process. For maximum compatibility, there is no "-" in front of the "aux". "ps auxww" provides complete information about the process, including all parameters.

## See also

- [Task manager](https://en.wikipedia.org/wiki/Task_manager)
- [`kill`](https://en.wikipedia.org/wiki/Kill_(command)) 
- [List of Unix commands](https://en.wikipedia.org/wiki/List_of_Unix_commands)
- [`nmon`](https://en.wikipedia.org/wiki/Nmon) — a system monitor tool for the AIX and Linux operating systems.
- `pgrep`
- [`pstree`](https://en.wikipedia.org/wiki/Pstree_(Unix)) 
- [`top`](https://en.wikipedia.org/wiki/Top_(Unix)) 
- [`lsof`](https://en.wikipedia.org/wiki/Lsof) 

## External links

- `ps` – Commands & Utilities Reference, [The Single UNIX Specification](https://en.wikipedia.org/wiki/Single_Unix_Specification), Issue 7 from [The Open Group](https://en.wikipedia.org/wiki/The_Open_Group)
- [Show all running processes in Linux using ps command](http://www.cyberciti.biz/faq/show-all-running-processes-in-linux/)
- [In Unix, what do the output fields of the ps command mean?](http://kb.iu.edu/data/afnv.html)