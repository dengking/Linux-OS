# `ipcs`

## csdn [ipcs命令详解——共享内存、消息队列、信号量定位利器](https://blog.csdn.net/dalongyes/article/details/50616162)



## 清空信号量

切换到安装用户，比如trade用户，运行如下命令，清空原有的信号量：

```shell
ipcs -s|grep `whoami`|awk -v user=`whoami` '{system("ipcrm -s" $2);printf("remove %s for %s\n",$2,user)}'
```