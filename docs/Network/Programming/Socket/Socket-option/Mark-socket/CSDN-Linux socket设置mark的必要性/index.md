# csdn [Linux socket设置mark的必要性](https://blog.csdn.net/dog250/article/details/7664062)

Linux的Netfilter钩子点的位置会导致一些奇怪的问题，比如本机发出的包无法使用基于mark的策略路由，这是因为mark一般是在Netfilter中进行的，而Linux的路由处在OUTPUT钩子点之前，因此这是一个顺序倒置的问题，如何来解决呢？只能在路由之前打上mark，而我们知道，对于外部进入的包，mark是在PREROUTING进行的，因此对于外部进入的包，策略路由是好使的，对于本机发出的包，路由之前只能是socket层了，那为何不能在传输层做呢？因为一来传输层比较杂，二来很多协议直接走到IP层，比如OSPF之类的，三来很多传输层协议也需要路由查找，比如TCP在`connect`的时候就需要查找路由以确定源IP地址(如果没有bind的话)。

幸运的是，Linux的`socket`支持`SO_MARK`这样一个option，可以很方便的使用：

```c++
mark = 100;
setsockopt(client_socket, SOL_SOCKET, SO_MARK, &mark, sizeof(mark));
```

