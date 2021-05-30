# Restart network service

OS采用的service management方式不同，则重启的方式也不同，下面进行一个总结。

## SysVinit

zhidao.baidu [Linux 启动、关闭、重启网络服务的两种方式](https://zhidao.baidu.com/question/285999187.html)

Linux 启动、关bai闭、重启网络服du务的两种方式：zhi

1、使用service脚本来调度网dao络服务，如：

启动 service network start；

关闭zhuan service network stop；

重启 service network restart；

2、直接执行网络服务的管理脚本，如：

启动 /etc/init.d/network  start；

关闭 /etc/init.d/network  stop；

重启 /etc/init.d/network  restart。



## systemd

```

```



### Centos8

informaticar [Failed to restart network.service: Unit network.service not found (CentOS 8)](https://www.informaticar.net/failed-to-restart-network-service-unit-network-service-not-found-centos-8/)



```SH
sudo ifdown ens3
sudo ifup ens3
```



```shell
sudo systemctl stop NetworkManager.service
sudo systemctl start NetworkManager.service
sudo systemctl restart NetworkManager.service
```



