# fuser 



## [fuser(1) - Linux man page](https://linux.die.net/man/1/fuser)



## wikipedia [fuser (Unix)](https://en.wikipedia.org/wiki/Fuser_(Unix))

The [Unix](https://en.wikipedia.org/wiki/Unix) [command](https://en.wikipedia.org/wiki/Command_(computing)) **fuser** is used to show which [processes](https://en.wikipedia.org/wiki/Process_(computing)) are using a specified [computer file](https://en.wikipedia.org/wiki/Computer_file), [file system](https://en.wikipedia.org/wiki/File_system), or [Unix socket](https://en.wikipedia.org/wiki/Unix_domain_socket).

## Example

### [Find Which Process Accessing a Directory](https://www.tecmint.com/learn-how-to-use-fuser-command-with-examples-in-linux/)

```shell
$ fuser .
OR
$ fuser /home/tecmint
```

Under the **ACCESS** column, you will see access types signified by the following letters:

1. `c` – current directory
2. `e` – an executable file being run
3. `f` – open file, however, **f** is left out in the output
4. `F` – open file for writing, **F** is as well excluded from the output
5. `r` – root directory
6. `m` – mmap’ed file or shared library



### [Find Which Process Accessing A File System](https://www.tecmint.com/learn-how-to-use-fuser-command-with-examples-in-linux/)

Next, you can determine which processes are accessing your `~.bashrc` file like so:

```
$ fuser -v -m .bashrc
```

The option, `-m` NAME or `--mount` **NAME** means name all processes accessing the file **NAME**. In case you a spell out directory as **NAME**, it is spontaneously changed to `NAME/`, to use any file system that is possibly mounted on that directory.

### [How to Kill and Signal Processes Using fuser](https://www.tecmint.com/learn-how-to-use-fuser-command-with-examples-in-linux/)

In this section we shall work through using **fuser** to [kill and send signals to processes](https://www.tecmint.com/find-and-kill-running-processes-pid-in-linux/).

In order to kill a processes accessing a file or socket, employ the `-k` or `--kill` option like so:

```shell
$ sudo fuser -k .
```

To interactively kill a process, where you are that asked to confirm your intention to kill the processes accessing a file or socket, make use of `-i` or `--interactive` option:

```shell
$ sudo fuser -ki .
```

The two previous commands will **kill** all processes accessing your current directory, the default signal sent to the processes is **SIGKILL**, except when **-SIGNAL** is used.

**Suggested Read:** [A Guide to Kill, Pkill and Killall Commands in Linux](https://www.tecmint.com/how-to-kill-a-process-in-linux/)

You can list all the signals using the `-l` or `--list-signals` options as below:

```shell
$ sudo fuser --list-signals 
```

[![List All Kill Process Signals](https://www.tecmint.com/wp-content/uploads/2016/10/List-All-Kill-Signals.png)](https://www.tecmint.com/wp-content/uploads/2016/10/List-All-Kill-Signals.png)List All Kill Process Signals

Therefore, you can send a signal to processes as in the next command, where **SIGNAL** is any of the signals listed in the output above.

```shell
$ sudo fuser -k -SIGNAL
```

For example, this command below sends the **HUP** signal to all processes that have your `/boot` directory open.

```shell
$ sudo fuser -k -HUP /boot 
```

Try to read through the **fuser** man page for advanced usage options, additional and more detailed information.

That is it for now, you can reach us by means of the feedback section below for any assistance that you possibly need or suggestions you wish to make.



### [Check Processes Using TCP/UDP Sockets](https://www.thegeekstuff.com/2012/02/linux-fuser-command/)

Using fuser we can also check the processes using TCP/UDP sockets. Since the above stated socket_serv sample C program executable is running on TCP port 5000, lets use fuser utility on this socket.

```shell
$ fuser -v -n tcp 5000
                       USER        PID ACCESS COMMAND
5000/tcp:            himanshu   4334   F....  socket_serv
```

So we see that fuser gives all detailed information of the process running on TCP port 5000.

Other than the examples above, we can use the ‘-m’ flag with this utility to display processes using a mounted file system like a USB drive.