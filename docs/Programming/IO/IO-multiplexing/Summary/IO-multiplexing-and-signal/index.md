# IO multiplexing and signal



## osiris [Safe UNIX Signal Handling Tips](http://osiris.978.org/~alex/safesignalhandling.html)

> NOTE: 
>
> 总结的非常好

Suppose you have a program with a main loop like the following pseudo-code:

```C
void gotsignal() {
  caught_signal=1;
}

void main() {
  signal(SIGwhatever, gotsignal);

  while(1) {
    /* do stuff */
    if(caught_signal) {
      /* do stuff */
    } else {
      /* do something else */
    }
    select();
    /* do more stuff */
  }
```

At first glance, everything is okay. We know that a signal caught in `select()` will cause `select()` to return immediately. `caught_signal` is evaluated just before `select()` is called. It would appear that signals occuring between `select()` are also handled properly.

But there exists an interval, after `caught_signal` is evaluated but before `select()` is called, that a signal can come in. `caught_signal` is then set, but `select()` doesn't return because `select()` wasn't called when the signal came in.

The now slightly less inexperienced programmer may "solve" this problem like so:

```C
  ...
  while(1) {
    /* do stuff */
    if(caught_signal) {
      /* do stuff */
    } else {
      /* do something else */
    }
    sigprocmask(SIG_UNBLOCK, ...);
    select();
    sigprocmask(SIG_BLOCK, ...);
    /* do more stuff */
  }
```

We are on the right track. It is clear that our strategy for handling signals should center on making sure that `select()` cannot be called *after* a signal that occured *after* the test to determine if a signal arrived!

### Present solutions

#### `pselect()`

`pselect()` is much like `select()`, except it takes a list of signals as an additional argument. Functionally, it is like `sigprocmask(SIG_UNBLOCK); select(); sigprocmask(SIG_BLOCK);`, except signals have no opportunity to occure between `sigprocmask(SIG_UNBLOCK)` and `select()`. This is a guarantee made by the kernel.

Sadly, `pselect()` is not available on many systems. Until recently, most Linux kernel/GNU libc stacks did not support `pselect()`, or used an imperfect emulation.

#### The self-pipe trick

The self-pipe trick involves an anonymous pipe, created with `pipe()`, a signal handler, and `select()`. The signal handler writes a byte to the writing end of the pipe, and `select()` waits for the reading end of the pipe to become readable.

The self-pipe trick is reliable, but uses additional system resources (ofiles, memory, and so forth). Bernstein, D. J. ["The self-pipe trick."](http://cr.yp.to/docs/selfpipe.html) van Bergen, Emile. ["Avoiding races with Unix signals and select()."](http://www.xs4all.nl/~evbergen/unix-signals.html)



#### `sigsetjmp`/`siglongjmp`

Our third strategy is using `sigsetjmp()` and `siglongjmp()` to jump to a specific spot in our main loop:

```C++
void gotsignal() {
  caught_signal=1;
  if(oktojmp) siglongjmp();
}

void main() {
  signal(SIGwhatever, gotsignal);

  while(1) {
    /* do stuff */
    sigsetjmp(); oktojmp=1;
    if(caught_signal) {
      /* do stuff */
    } else {
      /* do something else */
    }
    select();
    /* do more stuff */
  }
```

Regardless of where the process is, even if it is in `select()`, the `siglongjmp()` from the signal handler will cause program flow to be redirected to `sigsetjmp()`. This is the strategy I use in my code.



## yp [The self-pipe trick](http://cr.yp.to/docs/selfpipe.html)

Richard Stevens's 1992 book "Advanced programming in the UNIX environment'' says that you can't safely mix select() or poll() with SIGCHLD (or other signals). The SIGCHLD might go off while select() is starting, too early to interrupt it, too late to change its timeout.

> NOTE: 
>
> "go off"的意思是"发生"

Solution: the self-pipe trick. Maintain a pipe and select for readability on the pipe input. Inside the SIGCHLD handler, write a byte (non-blocking, just in case) to the pipe output. Done.

> NOTE: 
>
> 在 [select(2)](https://www.man7.org/linux/man-pages/man2/select.2.html) 中，也对此进行了说明



Of course, the Right Thing would be to have fork() return a file descriptor, not a process ID.



## p-variant system call

### [pselect](https://www.man7.org/linux/man-pages/man2/select.2.html)

```C++
int pselect(int nfds, fd_set *restrict readfds,
            fd_set *restrict writefds, fd_set *restrict exceptfds,
            const struct timespec *restrict timeout,
            const sigset_t *restrict sigmask);
```

The `pselect()` system call allows an application to safely wait until either a file descriptor becomes ready or until a signal is caught.

> NOTE: 
>
> 在收到signal的时候，要return

`sigmask` is a pointer to a signal mask (see `sigprocmask(2)`); if it is not NULL, then `pselect()` first replaces the current signal mask by the one pointed to by sigmask, then does the "select" function, and then restores the original signal mask.  (If sigmask is NULL, the signal mask is not modified during the pselect() call.)

> NOTE: 
>
> 也就是是说，在select中，是使用用户指定的`sigmask` 

Other than the difference in the precision of the timeout argument, the following pselect() call:

```C++
ready = pselect(nfds, &readfds, &writefds, &exceptfds, timeout, &sigmask);
```

is equivalent to atomically executing the following calls:

```C++
sigset_t origmask;

pthread_sigmask(SIG_SETMASK, &sigmask, &origmask);
ready = select(nfds, &readfds, &writefds, &exceptfds, timeout);
pthread_sigmask(SIG_SETMASK, &origmask, NULL)
```

The reason that pselect() is needed is that if one wants to wait for either a signal or for a file descriptor to become ready, then an atomic test is needed to prevent race conditions. (Suppose the signal handler sets a **global flag** and returns.  Then a test of this **global flag** followed by a call of select() could hang indefinitely(无限期的、不确定的) if the signal arrived just after the test but just before the call.  By contrast, pselect() allows one to first block signals, handle the signals that have come in, then call pselect() with the desired sigmask, avoiding the race.)

#### The self-pipe trick

On systems that lack pselect(), reliable (and more portable) signal trapping can be achieved using the self-pipe trick.  In this technique, a signal handler writes a byte to a pipe whose other end is monitored by select() in the main program.  (To avoid possibly blocking when writing to a pipe that may be full or reading from a pipe that may be empty, nonblocking I/O is used when reading from and writing to the pipe.)

### [ppoll()](https://www.man7.org/linux/man-pages/man2/poll.2.html)

The relationship between poll() and ppoll() is analogous to the relationship between select(2) and pselect(2): like pselect(2), ppoll() allows an application to safely wait until either a file descriptor becomes ready or until a signal is caught.

