# [`select`](https://www.man7.org/linux/man-pages/man2/select.2.html) VS [`poll`](https://www.man7.org/linux/man-pages/man2/poll.2.html) VS [`epoll`](https://man7.org/linux/man-pages/man7/epoll.7.html) 

## 比较

### 时间

`select` -> `poll` -> `epoll` 

### file descriptor数量限制



### portability 



`poll` is a POSIX standard interface

`epoll` is Linux-specific

## epoll VS poll

[epoll(7)](https://man7.org/linux/man-pages/man7/epoll.7.html)

The epoll API performs a similar task to poll(2): monitoring multiple file descriptors to see if I/O is possible on any of them.  The epoll API can be used either as an edge-triggered or a level-triggered interface and scales well to large numbers of watched file descriptors.

> NOTE:
>
> 上面已经总结了epoll相比于poll的优势:
>
> 1、支持 "edge-triggered"
>
> 2、scales well to large numbers of watched file descriptors

stackoverflow [poll vs. epoll insight [duplicate]](https://stackoverflow.com/questions/8858328/poll-vs-epoll-insight)



## stackoverflow [Why is epoll faster than select?](https://stackoverflow.com/questions/17355593/why-is-epoll-faster-than-select)

