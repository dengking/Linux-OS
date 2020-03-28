# `LIMITS.CONF(5)`

[LIMITS.CONF(5)](http://man7.org/linux/man-pages/man5/limits.conf.5.html)



比如，在按照一些主要软件的时候，一般以root用户运行`vi /etc/security/limits.conf`，增加如下配置：

```shell
*        soft   nproc      16384

*        hard   nproc      16384

*        soft   nofile     65536

*        hard   nofile     65536

```



修改完毕以后，需重新登录，以便生效。