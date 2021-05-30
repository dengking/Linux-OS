# Centos设置network manager开机自启动

## csdn [centos7设置NetworkManager开机自启动](https://blog.csdn.net/weixin_39333120/article/details/103868942)

启动：`systemctl start NetworkManger`
关闭：`systemctl stop NetworkManager`
开机启动：`systemctl enable NetworkManager`
查看是否开机启动：`systemctl is-enabled NetworkManager`
禁用开机启动：`systemctl disable NetworkManager`

## csdn [CentOS7的网卡开机自启动](https://blog.csdn.net/chuan_day/article/details/70828859)



```C++
# vi /etc/sysconfig/network-scripts/ifcfg-ens33
```



```shell
TYPE=Ethernet
BOOTPROTO=none
DEFROUTE=yes
IPV4_FAILURE_FATAL=no
IPV6INIT=yes
IPV6_AUTOCONF=yes
IPV6_DEFROUTE=yes
IPV6_FAILURE_FATAL=no
IPV6_ADDR_GEN_MODE=stable-privacy
NAME=ens33
UUID=3c881316-6e92-40c1-9f99-7820a4e27ae6
DEVICE=ens33
ONBOOT=yes
DNS1=192.168.0.1
IPADDR=192.168.0.53
PREFIX=24
GATEWAY=192.168.0.1
IPV6_PEERDNS=yes
IPV6_PEERROUTES=yes
IPV6_PRIVACY=no
```



将其中`ONBOOT`参数的值改为`yes`，即可了。