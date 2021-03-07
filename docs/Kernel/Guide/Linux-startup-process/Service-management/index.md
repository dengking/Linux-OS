# Operating-system service management

对OS的service进行管理，这是每个OS都需要做的非常重要的一个工作。

## wikipedia [Operating system service management](https://en.wikipedia.org/wiki/Operating_system_service_management)

In [computing](https://en.wikipedia.org/wiki/Computing), mechanisms and techniques for managing [services](https://en.wikipedia.org/wiki/Operating_system_services) often differ by [operating system](https://en.wikipedia.org/wiki/Operating_system).

### Apple [macOS](https://en.wikipedia.org/wiki/MacOS)

[launchd](https://en.wikipedia.org/wiki/Launchd) 

### [Many](https://en.wikipedia.org/wiki/Systemd#Adoption_and_reception) Linux distributions

[systemd](https://en.wikipedia.org/wiki/Systemd) 



## 如何确定OS使用的是哪种service management方式？

```shell
ps --pid=1 -l
```

比如

```shell
[dk@localhost ~]$ ps --pid=1 -l
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S     0       1       0  0  80   0 - 61488 -      ?        00:00:02 systemd
```

我的OS中，使用的是`systemd`。



## 如何设置auto boot/开机自启动？

一般来说，通过编写init script即可。各种service management都有着各自的init script。



## Linux 常见服务

cnblogs [LINUX常见服务列表](https://www.cnblogs.com/fanweisheng/p/11109244.html)

csdn [Linux 常见服务](https://blog.csdn.net/sakuragio/article/details/97946933)