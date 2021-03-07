# systemd

目前centos使用的就是`systemd`。

## wikipedia [systemd](https://en.wikipedia.org/wiki/Systemd)

**systemd** is a [software suite](https://en.wikipedia.org/wiki/Software_suite) that provides an array of system components for [Linux](https://en.wikipedia.org/wiki/Linux) operating systems.

> NOTE: 
> 1、它是一套软件



## Official site [systemd](https://systemd.io/)

> NOTE: 
>
> 1、内容并不完全

## freedesktop [systemd System and Service Manager](https://freedesktop.org/wiki/Software/systemd/)

## What is this?

`systemd` is a suite of basic building blocks for a Linux system. It provides a system and service manager that runs as PID 1 and starts the rest of the system. 

> NOTE: 
>
> ```shell
> ps --pid=1 -l
> F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
> 4 S     0       1       0  0  80   0 - 61488 -      ?        00:00:02 systemd
> ```
>
> 

`systemd` provides aggressive parallelization capabilities, uses socket and D-Bus activation for starting services, offers on-demand starting of daemons, keeps track of processes using **Linux control groups**, maintains mount(安装) and automount points, and implements an elaborate(精心制作的) transactional dependency-based service control logic. 

> NOTE: 
>
> 1、上面描述的是systemd的特性、它的一些实现方式
>
> 2、"keeps track of processes using **Linux control groups**" 中的"**Linux control groups**"要如何理解？参见 `Virtualization\Linux-control-groups` 章节



`systemd` supports SysV and LSB init scripts and works as a replacement for sysvinit. Other parts include a logging daemon, utilities to control basic system configuration like the hostname, date, locale, maintain a list of logged-in users and running containers and virtual machines, system accounts, runtime directories and settings, and daemons to manage simple network configuration, network time synchronization, log forwarding, and name resolution. See the introductory [blog story](http://0pointer.de/blog/projects/systemd.html) and [three](http://0pointer.de/blog/projects/systemd-update.html) [status](http://0pointer.de/blog/projects/systemd-update-2.html) [updates](http://0pointer.de/blog/projects/systemd-update-3.html) for a longer introduction. Also see the [Wikipedia article](http://en.wikipedia.org/wiki/Systemd).

## freedesktop [systemd man page](https://www.freedesktop.org/software/systemd/man/)

> NOTE: 
>
> 1、这是需要阅读的



## 使用指南

### 查看哪些服务是开机自动启动

csdn [Linux查看哪些服务是开机自动启动的](https://blog.csdn.net/chscomfaner/article/details/105560722)

服务如果需要自动启动，需要在`/etc/systemd/system/multi-user.target.wants/***.service`添加链接文件到`/usr/lib/systemd/system/***.service`

如果去除自动启动，移除此文件即可。`/etc/systemd/system/multi-user.target.wants/***.service`

```shell
ll /etc/systemd/system/multi-user.target.wants/
```

csdn [Linux查看设置开机启动的服务列表](https://blog.csdn.net/qq_44667896/article/details/104774374)

```shell
systemctl list-units --type=service
```

> NOTE: 
>
> 下面是我的系统中的样例输出

| UNIT                               | LOAD   | active | SUB     | DESCRIPTION                  |
| ---------------------------------- | ------ | ------ | ------- | ---------------------------- |
| mcelog.service                     | loaded | active | running | Machine Check Exception Log> |
| ModemManager.service               | loaded | active | running | Modem Manager                |
| NetworkManager-dispatcher.service  | loaded | active | running | Network Manager Script Disp> |
| NetworkManager-wait-online.service | loaded | active | exited  | Network Manager Wait Online  |
| NetworkManager.service             | loaded | active | running | Network Manager              |
| nis-domainname.service             | loaded | active | exited  | Read and set NIS domainname> |
| packagekit.service                 | loaded | active | running | PackageKit Daemon            |
| plymouth-quit-wait.service         | loaded | active | exited  | Hold until boot process fin> |
| plymouth-read-write.service        | loaded | active | exited  | Tell Plymouth To Write Out > |
| plymouth-start.service             | loaded | active | exited  | Show Plymouth Boot Screen    |
| polkit.service                     | loaded | active | running | Authorization Manager        |
| rhsmcertd.service                  | loaded | active | running | Enable periodic update of e> |
| rngd-wake-threshold.service        | loaded | active | exited  | Hardware RNG Entropy Gather> |
| rngd.service                       | loaded | active | running | Hardware RNG Entropy Gather> |
| rpc-statd-notify.service           | loaded | active | exited  | Notify NFS peers of a resta> |
| rpcbind.service                    | loaded | active | running | RPC Bind                     |
| rsyslog.service                    | loaded | active | running | System Logging Service       |
| rtkit-daemon.service               | loaded | active | running | RealtimeKit Scheduling Poli> |
| smartd.service                     | loaded | active | running | Self Monitoring and Reporti> |
| sshd.service                       | loaded | active | running | OpenSSH server daemon        |
| sssd-kcm.service                   | loaded | active | running | SSSD Kerberos Cache Manager  |
| sssd.service                       | loaded | active | running | System Security Services Da> |
| systemd-journal-flush.service      | loaded | active | exited  | Flush Journal to Persistent> |
| systemd-journald.service           | loaded | active | running | Journal Service              |
| systemd-logind.service             | loaded | active | running | Login Service                |

### 设置开机自启动

csdn [centos7设置NetworkManager开机自启动](https://blog.csdn.net/weixin_39333120/article/details/103868942)

启动：`systemctl start NetworkManger`
关闭：`systemctl stop NetworkManager`
开机启动：`systemctl enable NetworkManager`
查看是否开机启动：`systemctl is-enabled NetworkManager`
禁用开机启动：`systemctl disable NetworkManager`

## `systemctl`

### redhat [Getting started with systemctl](https://www.redhat.com/sysadmin/getting-started-systemctl)

Here is a syntax example:

```shell
systemctl subcommand argument
```

#### Service status

```shell
# systemctl status sshd
```

#### Starting and stopping services

```shell
# systemctl restart sshd
# systemctl stop sshd
# systemctl start sshd
# systemctl kill sshd
```

#### Enable and disable services

Previously, you used the `chkconfig` command to define the service's startup setting for each runlevel. Here is an example:

```shell
# chkconfig --level 35 sshd on
```

This command enables `sshd` to start up in runlevels 3 and 5.

With `systemctl`, configuring the default startup setting is the work of the `enable` and `disable` subcommands. The syntax is the same as with the `start`, `stop`, and `restart` subcommands. For example, to set SSH to start when the server boots, enter:

```shell
# systemctl enable sshd
```

Likewise, to configure SSH *not* to start during bootup, type:

```shell
# systemctl disable sshd
```

#### Use start and enable together

```shell
# systemctl start sshd

# systemctl enable sshd
```

### geeksforgeeks [systemctl in Unix](https://www.geeksforgeeks.org/systemctl-in-unix/)



## TODO

1、where dose systemd log？