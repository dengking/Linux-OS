# uwsgi [Serializing accept(), AKA Thundering Herd, AKA the Zeeg Problem](https://uwsgi-docs.readthedocs.io/en/latest/articles/SerializingAccept.html)

One of the historical problems in the UNIX world is the “thundering herd”.

What is it?

Take a process binding to a networking address (it could be `AF_INET`, `AF_UNIX` or whatever you want) and then forking itself:

```c++
int s = socket(...)
bind(s, ...)
listen(s, ...)
fork()
```

After having forked itself a bunch of times, each process will generally start blocking on `accept()`

```c++
for(;;) {
    int client = accept(...);
    if (client < 0) continue;
    ...
}
```

The funny problem is that on older/classic UNIX, `accept()` is woken up in each process blocked on it whenever a connection is attempted on the socket.

Only one of those processes will be able to truly accept the connection, the others will get a boring `EAGAIN`.

This behaviour (for various reasons) is **amplified**(放大) when instead of processes you use threads (so, you have multiple threads blocked on `accept()`).

The de facto solution was placing a lock before the `accept()` call to serialize its usage:

```c++
for(;;) {
    lock();
    int client = accept(...);
    unlock();
    if (client < 0) continue;
    ...
}
```

For threads, dealing with locks is generally easier but for processes you have to fight with system-specific solutions or fall back to the venerable SysV ipc subsystem (more on this later).

In modern times, the vast majority of UNIX systems have evolved, and now the kernel ensures (more or less) only one process/thread is woken up on a connection event.

Ok, problem solved, what we are talking about?

## select()/poll()/kqueue()/epoll()/…

Evolution has a price, so after a while the standard loop engine of a uWSGI process/thread moved from:

```c++
for(;;) {
    int client = accept(s, ...);
    if (client < 0) continue;
    ...
}
```

to a more complex:

```c++
for(;;) {
    int interesting_fd = wait_for_fds();
    if (fd_need_accept(interesting_fd)) {
        int client = accept(interesting_fd, ...);
        if (client < 0) continue;
    }
    else if (fd_is_a_signal(interesting_fd)) {
        manage_uwsgi_signal(interesting_fd);
    }
    ...
}
```

The problem is now the `wait_for_fds()` example function: it will call something like `select()`, `poll()` or the more modern `epoll()` and `kqueue()`.

These kinds of system calls are “monitors” for file descriptors, and they are woken up in all of the processes/threads waiting for the same file descriptor.

Before you start blaming your kernel developers, this is the right approach, as the kernel cannot know if you are waiting for those file descriptors to call `accept()` or to make something funnier.

So, welcome again to the **thundering herd**.

## Application Servers VS WebServers

It survived decades of IT evolutions and it’s still one of the most important technologies powering the whole Internet.

Born as multiprocess-only, Apache had to always deal with the thundering herd problem and they solved it using SysV ipc semaphores.

Even on modern Apache releases, stracing one of its process (bound to multiple interfaces) you will see something like that (it is a Linux system):

```c++
semop(...); // lock
epoll_wait(...);
accept(...);
semop(...); // unlock
... // manage the request
```

the SysV semaphore protect your `epoll_wait` from thundering herd.

So, another problem solved, the world is a such a beautiful place… but ….

