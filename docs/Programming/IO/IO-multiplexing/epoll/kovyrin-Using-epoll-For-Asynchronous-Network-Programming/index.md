# [Using epoll() For Asynchronous Network Programming](https://kovyrin.net/2006/04/13/epoll-asynchronous-network-programming/)

General way to implement tcp servers is “one thread/process per connection”. But on high loads this approach can be not so efficient and we need to use another patterns of connection handling. In this article I will describe how to implement tcp-server with synchronous connections handling using `epoll()` system call of Linux 2.6. kernel.



`epoll` is a new system call introduced in Linux 2.6. It is designed to replace the deprecated `select` (and also `poll`). Unlike these earlier system calls, which are O(n), `epoll` is an O(1) algorithm – this means that it scales well as the number of watched file descriptors increase. `select` uses a **linear search** through the list of watched file descriptors, which causes its `O(n)` behaviour, whereas `epoll` uses **callbacks** in the kernel file structure.

Another fundamental difference of `epoll` is that it can be used in an **edge-triggered**, as opposed to **level-triggered**, fashion. This means that you receive “hints” when the kernel believes the file descriptor has become ready for I/O, as opposed to being told “I/O can be carried out on this file descriptor”. This has a couple of minor advantages: kernel space doesn’t need to keep track of the state of the file descriptor, although it might just push that problem into user space, and user space programs can be more flexible (e.g. the readiness change notification can just be ignored).

To use `epoll` method you need to make following steps in your application:



### Create specific **file descriptor** for `epoll` calls:

```C
epfd = epoll_create(EPOLL_QUEUE_LEN);
```

where `EPOLL_QUEUE_LEN` is the maximum number of connection descriptors you expect to manage at one time. The return value is a file descriptor that will be used in `epoll` calls later. This descriptor can be closed with `close()` when you do not longer need it.



## After first step you can add your descriptors to `epoll` with following call:

```C
  static struct epoll_event ev;
  int client_sock;
  ...
  ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
  ev.data.fd = client_sock;
  int res = epoll_ctl(epfd, EPOLL_CTL_ADD, client_sock, &ev);
```

where `ev` is `epoll` event configuration sctucture, `EPOLL_CTL_ADD` – predefined command constant to add sockets to `epoll`. Detailed description of `epoll_ctl` flags can be found in `epoll_ctl(2)` man page. When `client_sock` descriptor will be closed, it will be automatically deleted from `epoll` descriptor.



## When all your descriptors will be added to `epoll`, your process can idle and wait to something to do with epoll’ed sockets:

```C
  while (1) {
    // wait for something to do...
    int nfds = epoll_wait(epfd, events, 
                                MAX_EPOLL_EVENTS_PER_RUN, 
                                EPOLL_RUN_TIMEOUT);
    if (nfds < 0) die("Error in epoll_wait!");
  
    // for each ready socket
    for(int i = 0; i < nfds; i++) {
      int fd = events[i].data.fd;
      handle_io_on_socket(fd);
    }
  }
```

