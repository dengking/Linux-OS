# SO_REUSEPORT、EPOLLEXCLUSIVE 解决惊群问题

在 [Core functionality](https://nginx.org/en/docs/ngx_core_module.html) # [**accept_mutex**](https://nginx.org/en/docs/ngx_core_module.html#accept_mutex) 

> If `accept_mutex` is enabled, worker processes will accept new connections by turn. Otherwise, all worker processes will be notified about new connections, and if volume of new connections is low, some of the worker processes may just waste system resources.
>
> > There is no need to enable `accept_mutex` on systems that support the [EPOLLEXCLUSIVE](https://nginx.org/en/docs/events.html#epoll) flag (1.11.3) or when using [reuseport](https://nginx.org/en/docs/http/ngx_http_core_module.html#reuseport).
>
> 
>
> > Prior to version 1.11.3, the default value was `on`.

中，发现了它们。

## zhihu [SO_REUSEPORT、EPOLLEXCLUSIVE都用来解决epoll的惊群，侧重点跟区别是什么?](https://www.zhihu.com/question/290390092)

如题，一个多进程共同监听一个socket由内核进行负载均衡，一个则是通过关键字使用了多个线程监听一个epfd使用的是 add_wait_queue_exculsive()，只唤醒一个等待源从而避免惊群。其差异跟用到场景分别是什么？

