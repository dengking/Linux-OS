# bind 到`0.0.0.0`与bind 到`127.0.0.1`与bind 到另外一个IP

这个问题至今仍然困惑这我。

我使用flask做了一个实验：

我的flask web  server运行在`192.168.71.67`这台机器，我可以以如下三种方式来启动web server：

- `flask run --host=0.0.0.0`

  在这种情况下，我可以通过在我的laptop中的browser来访问到该web  server

- `flask run `

  按照flask的文档描述，这总情况下它是bind到localhost，此时我无法在我的laptop中的browser访问到该web server；但是通过`curl http://127.0.0.1:5000`是可以的

- `flask run --host=192.168.71.67`

  这种情况下只能够通过`curl http://192.168.71.67:5000`访问到

- `flask run --host=192.168.158.94`

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

1. `0.0.0.0` 
2. `127.0.0.1` 
3. 本机的IP，显然这种情况是不好的，因为本机的IP是可能变动的，不如`127.0.0.1`

不可能bind到出这三种情况外的IP，上述例子中的第四种情况就是这样的。





## stackoverflow [What client-side situations need bind()?](https://stackoverflow.com/questions/4118241/what-client-side-situations-need-bind)



## [A](https://stackoverflow.com/a/4118325)

On the client side, you would only use bind if you want to use a specific client-side port, which is rare. Usually on the client, you specify the IP address and port of the server machine, and the OS will pick which port you will use. Generally you don't care, but in some cases, there may be a firewall on the client that only allows outgoing connections on certain port. In that case, you will need to bind to a specific port before the connection attempt will work.