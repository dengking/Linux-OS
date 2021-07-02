# jvns [Async IO on Linux: select, poll, and epoll](https://jvns.ca/blog/2017/06/03/async-io-on-linux--select--poll--and-epoll/)





### performance: select & poll vs epoll

In the book there’s a table comparing the performance for 100,000 monitoring operations:

```
# operations  |  poll  |  select   | epoll
10            |   0.61 |    0.73   | 0.41
100           |   2.9  |    3.0    | 0.42
1000          |  35    |   35      | 0.53
10000         | 990    |  930      | 0.66
```

