# lsof

Everything in Unix is a file，而lsof能够list open files，所以足见它的重要性。

## wikipedia [lsof](https://en.wikipedia.org/wiki/Lsof)

### Examples

Open files in the system include disk files, [named pipes](https://en.wikipedia.org/wiki/Named_pipe), network [sockets](https://en.wikipedia.org/wiki/Internet_socket) and devices opened by all processes.

The listing of open files can be consulted (suitably filtered if necessary) to identify the process that is using the files.

```shell
# lsof /var
COMMAND     PID     USER   FD   TYPE DEVICE SIZE/OFF   NODE NAME
syslogd     350     root    5w  VREG  222,5        0 440818 /var/adm/messages
syslogd     350     root    6w  VREG  222,5   339098   6248 /var/log/syslog
cron        353     root  cwd   VDIR  222,5      512 254550 /var -- atjobs
```

To view the port associated with a daemon:

```shell
# lsof -i -n -P | grep sendmail
sendmail  31649    root    4u  IPv4 521738       TCP *:25 (LISTEN)
```

From the above one can see that "sendmail" is listening on its standard port of "25".

- `-i`

  Lists IP sockets.

- `-n`

  Do not resolve hostnames (no DNS).

- `-P`

  Do not resolve port names (list port number instead of its name).

One can also list Unix Sockets by using `lsof -U`.



## [lsof(8) - Linux man page](https://linux.die.net/man/8/lsof)

lsof - list open files

> NOTE: 显然，使用这个command，需要对Linux的文件有着非常详细的认识，下面总结了不同类型的file和其对应的option；在原文的Output段中，对文件类型进行了详细的说明，据此可以知道OS所支持的所有的文件类型。

### Options

#### file type

| 文件类型                 | list request option |      |
| ------------------------ | ------------------- | ---- |
| regular file             |                     |      |
| directory                |                     |      |
| block special file       |                     |      |
| character special file   |                     |      |
| executing text reference |                     |      |
| library                  |                     |      |
| Internet socket          | -i                  |      |
| NFS file                 | -N                  |      |
| UNIX domain socket       | -U                  |      |

A specific file or all the files in a file system may be selected by path.

#### user

`-u`

> NOTE: 下面是tecmint [10 lsof Command Examples in Linux](https://www.tecmint.com/10-lsof-command-examples-in-linux/)中给出的简介: display the list of all opened files of user **tecmint**.
>
> ```
> # lsof -u tecmint
> 
> COMMAND  PID    USER   FD   TYPE     DEVICE SIZE/OFF   NODE NAME
> sshd    1838 tecmint  cwd    DIR      253,0     4096      2 /
> sshd    1838 tecmint  rtd    DIR      253,0     4096      2 /
> sshd    1838 tecmint  txt    REG      253,0   532336 188129 /usr/sbin/sshd
> sshd    1838 tecmint  mem    REG      253,0    19784 190237 /lib/libdl-2.12.so
> sshd    1838 tecmint  mem    REG      253,0   122436 190247 /lib/libselinux.so.1
> sshd    1838 tecmint  mem    REG      253,0   255968 190256 /lib/libgssapi_krb5.so.2.2
> sshd    1838 tecmint  mem    REG      253,0   874580 190255 /lib/libkrb5.so.3.3
> ```



#### PID

> NOTE: 下面是tecmint [10 lsof Command Examples in Linux](https://www.tecmint.com/10-lsof-command-examples-in-linux/)中给出的简介:
>
> #### 9. Search by PID
>
> The below example only shows whose **PID** is **1** [**One**].
>
> ```
> # lsof -p 1
> 
> COMMAND PID USER   FD   TYPE     DEVICE SIZE/OFF   NODE NAME
> init      1 root  cwd    DIR      253,0     4096      2 /
> init      1 root  rtd    DIR      253,0     4096      2 /
> init      1 root  txt    REG      253,0   145180 147164 /sbin/init
> init      1 root  mem    REG      253,0  1889704 190149 /lib/libc-2.12.so
> init      1 root  mem    REG      253,0   142472 189970 /lib/ld-2.12.so
> ```

### Output

> NOTE: 
>
> 读懂输出的一个重要前提是清楚输出中各列的含义，原文对此进行了详细说明，但是冗长。下面是tecmint [10 lsof Command Examples in Linux](https://www.tecmint.com/10-lsof-command-examples-in-linux/)中给出的简介
>
> ```
> # lsof
> 
> COMMAND    PID      USER   FD      TYPE     DEVICE  SIZE/OFF       NODE NAME
> init         1      root  cwd      DIR      253,0      4096          2 /
> init         1      root  rtd      DIR      253,0      4096          2 /
> init         1      root  txt      REG      253,0    145180     147164 /sbin/init
> init         1      root  mem      REG      253,0   1889704     190149 /lib/libc-2.12.so
> init         1      root   0u      CHR        1,3       0t0       3764 /dev/null
> init         1      root   1u      CHR        1,3       0t0       3764 /dev/null
> init         1      root   2u      CHR        1,3       0t0       3764 /dev/null
> init         1      root   3r     FIFO        0,8       0t0       8449 pipe
> init         1      root   4w     FIFO       0,8       0t0       8449 pipe
> init         1      root   5r      DIR       0,10         0          1 inotify
> init         1      root   6r      DIR       0,10         0          1 inotify
> init         1      root   7u     unix 0xc1513880       0t0       8450 socket
> ```

#### FD

> NOTE:下面是tecmint [10 lsof Command Examples in Linux](https://www.tecmint.com/10-lsof-command-examples-in-linux/)中给出的简介:
>
> **FD** – stands for File descriptor and may seen some of the values as:
>
> 1. **cwd** current working directory
> 2. **rtd** root directory
> 3. **txt** program text (code and data)
> 4. **mem** memory-mapped file
>
> Also in **FD** column numbers like **1u** is actual file descriptor and followed by u,r,w of it’s mode as:
>
> 1. **r** for read access.
> 2. **w** for write access.
> 3. **u** for read and write access.



#### COMMAND

> NOTE: 即命令

#### TYPE

> NOTE: 文件类型，下面是tecmint [10 lsof Command Examples in Linux](https://www.tecmint.com/10-lsof-command-examples-in-linux/)中给出的简介:
>
> **TYPE** – of files and it’s identification.
>
> 1. **DIR** – Directory
> 2. **REG** – Regular file
> 3. **CHR** – Character special file.
> 4. **FIFO** – First In First Out

is the type of the node associated with the file - e.g., GDIR, GREG, VDIR, VREG, etc.



## Examples

### stackexchange [Kill process running on port 80](https://unix.stackexchange.com/questions/244531/kill-process-running-on-port-80)

[A](https://unix.stackexchange.com/a/244534)

There are several ways to find which running process is using a port.

Using `fuser` it will give the PID(s) of the multiple instances associated with the listening port.

```shell
sudo apt-get install psmisc
sudo fuser 80/tcp

80/tcp:               1858  1867  1868  1869  1871
```

After finding out, you can either stop or kill the process(es).

You can also find the PIDs and more details using lsof

```shell
sudo lsof -i tcp:80

COMMAND  PID     USER   FD   TYPE DEVICE SIZE/OFF NODE NAME  
nginx   1858     root    6u  IPv4   5043      0t0  TCP ruir.mxxx.com:http (LISTEN)  
nginx   1867 www-data    6u  IPv4   5043      0t0  TCP ruir.mxxx.com:http (LISTEN)  
nginx   1868 www-data    6u  IPv4   5043      0t0  TCP ruir.mxxx.com:http (LISTEN)  
nginx   1869 www-data    6u  IPv4   5043      0t0  TCP ruir.mxxx.com:http (LISTEN)  
nginx   1871 www-data    6u  IPv4   5043      0t0  TCP ruir.mxxx.com:http (LISTEN)  
```

To limit to sockets that *listen* on port 80 (as opposed to clients that connect to port 80):

```shell
sudo lsof -i tcp:80 -s tcp:listen
```

To kill them automatically:

```
sudo lsof -t -i tcp:80 -s tcp:listen | sudo xargs kill
```





cyberciti [Linux: Find Out What Is Using TCP Port 80](https://www.cyberciti.biz/faq/find-linux-what-running-on-port-80-command/)