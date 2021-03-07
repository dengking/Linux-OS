# init.d Linux Service Management

## geeksforgeeks [What is init.d in Linux Service Management?](https://www.geeksforgeeks.org/what-is-init-d-in-linux-service-management/)

In Linux there are several services that can be started and stopped manually in the system, some of there services are ssh, HTTP, tor, apache, etc. To start and run these services we used to simply type

```shell
service "service name" start/stop/status/restart
```

In this simple manner, we are using service management in Linux but what actually happens and how it actually works in the background.

### What is init.d?

All these service works on several scripts and these scripts are stored in **/etc/init.d** location, this init.d is deamon which is the first process of the Linux system. Then other processes, services, daemons, and threats are started by init. So *init.d* is a configuration database for the init process. Now let’s check some daemon scripts by printing some processes, a daemon script holds functions like start, stop, status and restart. Let’s check ssh as an example.

```shell
cat /etc/init.d/ssh
```

**Output:**

![daemon script of ssh command](https://media.geeksforgeeks.org/wp-content/uploads/20200327141507/sshex.png)



### How to Use init.d in Service Management?

We used to type simple command *service ssh start*. But now, in this case, we will do it the other way which is also simple.

```
/etc/init.d/ssh start
```

and the same way you can stop

```
/etc/init.d/ssh stop
```

![stopping ssh process management](https://media.geeksforgeeks.org/wp-content/uploads/20200327142659/init.d.png)



## poftut [What Is init.d and How To Use For Service Management In Linux](https://www.poftut.com/what-is-init-d-and-how-to-use-for-service-management-in-linux/)

## 总结

通过上述文章可知:

1、init.d 的command是 `service`

2、它的配置位置是: `/etc/init.d/`