# `INADDR_ANY`、local_host

## csdn [socket开发中INADDR_ANY"的含义是什么？](https://blog.csdn.net/jeffasd/article/details/51461568)

"将`sin_addr`设置为`INADDR_ANY`"的含义是什么？

`INADDR_ANY`转换过来就是`0.0.0.0`，泛指本机的意思，也就是表示本机的所有IP，因为有些机子不止一块网卡，多网卡的情况下，这个就表示所有网卡ip地址的意思。

比如一台电脑有3块网卡，分别连接三个网络，那么这台电脑就有3个ip地址了，如果某个应用程序需要监听某个端口，那他要监听哪个网卡地址的端口呢？

如果绑定某个具体的ip地址，你只能监听你所设置的ip地址所在的网卡的端口，其它两块网卡无法监听端口，如果我需要三个网卡都监听，那就需要绑定3个ip，也就等于需要管理3个套接字进行数据交换，这样岂不是很繁琐？

所以出现`INADDR_ANY`，你只需绑定`INADDR_ANY`，管理一个套接字就行，不管数据是从哪个网卡过来的，只要是绑定的端口号过来的数据，都可以接收到。


## bind 到`0.0.0.0`与bind 到`127.0.0.1`与bind 到另外一个IP



我使用flask做了一个实验：

我的flask web  server运行在`192.168.71.67`这台机器，我可以以如下三种方式来启动web server：

1、`flask run --host=0.0.0.0`

在这种情况下，我可以通过在我的laptop中的browser来访问到该web  server

2、`flask run `

按照flask的文档描述，这总情况下它是bind到localhost，此时我无法在我的laptop中的browser访问到该web server；但是通过`curl http://127.0.0.1:5000`是可以的

3、`flask run --host=192.168.71.67`

这种情况下只能够通过`curl http://192.168.71.67:5000`访问到

4、`flask run --host=192.168.158.94`

指定的IP地址为我的laptop的IP，此时无法启动web server，报了如下错误：

```
Traceback (most recent call last):
  File "/usr/anaconda3/bin/flask", line 11, in <module>
    sys.exit(main())
  File "/usr/anaconda3/lib/python3.6/site-packages/flask/cli.py", line 894, in main
    cli.main(args=args, prog_name=name)
  File "/usr/anaconda3/lib/python3.6/site-packages/flask/cli.py", line 557, in main
    return super(FlaskGroup, self).main(*args, **kwargs)
  File "/usr/anaconda3/lib/python3.6/site-packages/click/core.py", line 697, in main
    rv = self.invoke(ctx)
  File "/usr/anaconda3/lib/python3.6/site-packages/click/core.py", line 1066, in invoke
    return _process_result(sub_ctx.command.invoke(sub_ctx))
  File "/usr/anaconda3/lib/python3.6/site-packages/click/core.py", line 895, in invoke
    return ctx.invoke(self.callback, **ctx.params)
  File "/usr/anaconda3/lib/python3.6/site-packages/click/core.py", line 535, in invoke
    return callback(*args, **kwargs)
  File "/usr/anaconda3/lib/python3.6/site-packages/click/decorators.py", line 64, in new_func
    return ctx.invoke(f, obj, *args[1:], **kwargs)
  File "/usr/anaconda3/lib/python3.6/site-packages/click/core.py", line 535, in invoke
    return callback(*args, **kwargs)
  File "/usr/anaconda3/lib/python3.6/site-packages/flask/cli.py", line 771, in run_command
    threaded=with_threads, ssl_context=cert)
  File "/usr/anaconda3/lib/python3.6/site-packages/werkzeug/serving.py", line 795, in run_simple
    s.bind(get_sockaddr(hostname, port, address_family))
OSError: [Errno 99] Cannot assign requested address
```



通过上述例子可以总结如下：

bind函数的IP只能够是：

1、`0.0.0.0` 

2、`127.0.0.1` 

3、本机的IP，显然这种情况是不好的，因为本机的IP是可能变动的，不如`127.0.0.1`

不可能bind到出这三种情况外的IP，上述例子中的第四种情况就是这样的。



## TODO

stackoverflow [Understanding INADDR_ANY for socket programming](https://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming)
