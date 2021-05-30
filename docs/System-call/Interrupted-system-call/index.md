# Interrupted system call

## Interrupted system call

在下面文章中，对此进行了详细的介绍:

1、`man-7-signal`

2、`Book-APUE\10-Signals\10.5-Interrupted-System-Calls`

通过 [signal(7) ](http://man7.org/linux/man-pages/man7/signal.7.html) 中的内容可知:

> 重点在于 "may block for an indefinite time(无限时间)"，前提条件之一是: 
>
> "blocked call"，因此system call必须是blocked。
>
> 下面是回避"may block for an indefinite time(无限时间)"的方式:
>
> 1、non-blocking IO



### Slow system call、slow device

stackexchange [Difference between slow system calls and fast system calls](https://unix.stackexchange.com/questions/14293/difference-between-slow-system-calls-and-fast-system-calls)



### 通过Nonblocking I/O来转换slow system call

从上面的介绍来看，其实所谓的slow  system call是跟它所操作的device密切相关的，而Unix OS的everything in Unix is file的philosophy，将很多device都抽象成了file，我们通过对这些file的file descriptor进行操作来实现对device的操作，因此很多操作都是类似于IO；默认情况下，当我们对slow device执行system call的时候，就非常可能出现slow system call的情况；Unix OS是非常灵活的，它是有提供system call来允许用户改变这种默认行为的：这就是Unix中的nonblocking I/O，通过在指定的file descriptor上设置nonblocking标志，来告诉kernel不要block对该file descriptor进行操作的thread；

上述想法是在《APUE 14.2 Nonblocking I/O》中提出的。



在这一节对这个主题的内容进行了深入的介绍；

## stackoverflow [Interrupting blocked read](https://stackoverflow.com/questions/6249577/interrupting-blocked-read)

My program goes through a loop like this:

```c
...
while(1){
  read(sockfd,buf,sizeof(buf));
  ...
}
```

The `read` function blocks when it is waiting for input, which happens to be from a socket. I want to handle `SIGINT` and basically tell it to stop the read function if it is reading and then call an arbitrary function. What is the best way to do this?



### [A](https://stackoverflow.com/a/6249629)

From `read(2)`:

```none
   EINTR  The call was interrupted by a signal before any data
          was read; see signal(7).
```

If you amend your code to look more like:

```c
cont = 1;
while (1 && cont) {
    ret = read(sockfd, buf, sizeof(buf));
    if (ret < 0 && errno == EINTR)
        cont = arbitrary_function();
}
```

This lets `arbitrary_function()` decide if the `read(2)` should be re-tried or not.

**Update**

You need to handle the signal in order to get the `EINTR` behavior from `read(2)`:

```c
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>

int interrupted;

void handle_int(num) {
  interrupted = 1;
}

int main(void){
  char buf[9001];
  struct sigaction int_handler = {.sa_handler=handle_int};
  sigaction(SIGINT,&int_handler,0);
  while(!interrupted){
    printf("interrupted: %d\n", interrupted);
    if(read(0,buf,sizeof(buf))<0){
      if(errno==EINTR){
        puts("eintr");
      }else{
        printf("%d\n",errno);
      }
      puts(".");
    }
  }
  puts("end");
  return 0;
}
```

Gives output:

```c
$ ./foo
interrupted: 0
hello
interrupted: 0
^Ceintr
.
end
```

> NOTE: 当thread阻塞在system call中的时候，如果产生了signal，则OS会转去执行signal handler，然后这个system call就被interrupted了，这意味中这个system call会返回，通常是返回错误值-1，并且`errorno`被设置为`EINTR`；其实用户可以据此将这个system call进行restart，具体的写法参见：《interrupted-system-call-self-pipe-trick.md》





## TODO

https://www.ibm.com/support/knowledgecenter/en/SS3RA7_17.0.0/clementine/clef_prog_ssapi_guidelines_7.html


http://www.justskins.com/forums/interrupted-system-call-read-235357.html


https://unix.stackexchange.com/questions/509375/what-is-interrupted-system-call


https://unix.stackexchange.com/questions/253349/eintr-is-there-a-rationale-behind-it





### stackexchange [Interruption of system calls when a signal is caught](https://unix.stackexchange.com/questions/16455/interruption-of-system-calls-when-a-signal-is-caught)

From reading the man pages on the `read()` and `write()` calls it appears that these calls get interrupted by **signals** regardless of whether they have to block or not.

In particular, assume

1、a process establishes a handler for some signal.

2、a device is opened (say, a terminal) with the `O_NONBLOCK` **not** set (i.e. operating in blocking mode)

3、the process then makes a `read()` system call to read from the device and as a result executes a kernel control path in kernel-space.

4、while the precess is executing its `read()` in kernel-space, the signal for which the handler was installed earlier is delivered to that process and its signal handler is invoked.

Reading the man pages and the appropriate sections in [SUSv3 'System Interfaces volume (XSH)'](http://pubs.opengroup.org/onlinepubs/009695399/), one finds that:

i. If a `read()` is interrupted by a signal before it reads any data (i.e. it had to block because no data was available), it returns -1 with `errno` set to [EINTR].

ii. If a `read()` is interrupted by a signal after it has successfully read some data (i.e. it was possible to start servicing the request immediately), it returns the number of bytes read.

**Question A):** Am I correct to assume that in either case (block/no block) the delivery and handling of the signal is not entirely transparent to the `read()`?

> NOTE: not entirely transparent意味着`read`是需要考虑signal的；	

Case i. seems understandable since the blocking `read()` would normally place the process in the `TASK_INTERRUPTIBLE` state so that when a signal is delivered, the kernel places the process into `TASK_RUNNING` state.

However when the `read()` doesn't need to block (case ii.) and is processing the request in kernel-space, I would have thought that the arrival of a **signal** and its handling would be transparent much like the arrival and proper handling of a HW(hardware) interrupt would be（这段话的意思是在system call正在执行而非blocked的时候，作者认为OS在这种情况下，不应该中断system call的运行而应该将OS处理硬中断那样）. In particular I would have **assumed** that upon delivery of the signal, the process would be temporarily placed into **user mode** to execute its **signal handler** from which it would return eventually to finish off processing the interrupted `read()`(in kernel-space) so that the `read()` runs its course to completion after which the process returns back to the point just after the call to `read()` (in user-space), with all of the available bytes read as a result（这只是作者的一种假设）.

But ii. seems to imply that the `read()` is interrupted, since data is available immediately, but it returns returns only some of the data (instead of all).

This brings me to my second (and final) question:

**Question B):** If my assumption under A) is correct, why does the `read()` get interrupted, even though it does not need to block because there is data available to satisfy the request immediately? In other words, why is the `read()` not resumed after executing the signal handler, eventually resulting in all of the available data (which was available after all) to be returned?

> NOTE: 其实作者的问题归结起来就是在 APUE 的10.5 Interrupted System Calls中提及的automatic restarting of certain interrupted system calls。



#### [A](https://unix.stackexchange.com/a/16487)

Summary: you're correct that receiving a signal is not transparent, neither in case i (interrupted without having read anything) nor in case ii (interrupted after a partial read). To do otherwise in case i would require making fundamental changes both to the architecture of the operating system and the architecture of applications.

***TRANSLATION*** : 否则，在情况i中需要对操作系统的体系结构和应用程序的体系结构进行基本的改变。

#### The OS implementation view

Consider what happens if a system call is interrupted by a signal. The **signal handler** will execute user-mode code. But the **syscall handler** is kernel code and does not trust any user-mode code. So let's explore the choices for the **syscall handler**:

一、Terminate the **system call**; report how much was done to the user code. It's up to the application code to **restart**（重新调用） the **system call** in some way, if desired. That's how unix works.

在APUE的10.5 Interrupted System Calls给出了符合上述想法的code：

```c
again:
    if ((n = read(fd, buf, BUFFSIZE)) < 0) {
        if (errno == EINTR)
            goto again; /* just an interrupted system call */
            			/* handle other errors */
    }
```



二、Save the state of the **system call**, and allow the user code to resume the call. This is problematic for several reasons:

1、While the user code is running, something could happen to invalidate the saved state. For example, if reading from a file, the file might be truncated. So the kernel code would need a lot of logic to handle these cases.

> NOTE:  : user code可能导致saved state 编程invalid

2、The saved state can't be allowed to keep any lock, because there's no guarantee that the user code will ever resume the syscall, and then the lock would be held forever.

> NOTE:  : 不能允许保存的状态保持任何锁定，因为无法保证用户代码将恢复系统调用，然后锁定将永久保留

上面这段话并没有搞懂

3、The kernel must expose new interfaces to resume or cancel ongoing syscalls, in addition to the normal interface to start a syscall. This is a lot of complication for a rare case.

> NOTE:  : 注意作者在这里使用的三个动词：start，resume，cancel；它们的具体含义如下：

start a syscall，即调用

resume a syscall，在start a  syscall之后，在此syscall执行的期间此syscall被interrupted了，而后在resume这个syscall，即恢复这个syscall的运行



4、The saved state would need to use resources (memory, at least); those resources would need to be allocated and held by the kernel but be counted against the process's allotment. This isn't insurmountable, but it is a complication.

- Note that the signal handler might make system calls that themselves get interrupted; so you can't just have a **static** resource allotment that covers all possible syscalls.

    参见APUE的10.6 Reentrant Functions，使用了static resource allotment的system call都是non reentrant的

- And what if the resources cannot be allocated? Then the syscall would have to fail anyway. Which means the application would need to have code to handle this case, so this design would not simplify the application code.

三、Remain in progress (but suspended), create a new thread for the signal handler. This, again, is problematic:

- Early unix implementations had a single thread per process.
- The signal handler would risk overstepping on the syscall's shoes. This is an issue anyway, but in the current unix design, it's contained.
- Resources would need to be allocated for the new thread; see above.

The main difference with an interrupt is that the interrupt code is trusted, and highly constrained. It's usually not allowed to allocate resources, or run forever, or take locks and not release them, or do any other kind of nasty things; since the interrupt handler is written by the OS implementer himself, he knows that it won't do anything bad. On the other hand, application code can do anything.

#### The application design view

When an application is interrupted in the middle of a system call, should the syscall continue to completion? Not always. For example, consider a program like a shell that's reading a line from the terminal, and the user presses `Ctrl+C`, triggering SIGINT. The read must not complete, that's what the signal is all about. Note that this example shows that the `read` syscall must be interruptible even if no byte has been read yet.

So there must be a way for the application to tell the kernel to cancel the system call. Under the unix design, that happens automatically: the signal makes the syscall return. Other designs would require a way for the application to resume or cancel the syscall at its leasure.

The `read` system call is the way it is because it's the primitive that makes sense, given the general design of the operating system. What it means is, roughly, “read as much as you can, up to a limit (the buffer size), but stop if something else happens”. To actually read a full buffer involves running `read` in a loop until as many bytes as possible have been read; this is a higher-level function, [`fread(3)`](http://pubs.opengroup.org/onlinepubs/009695399/functions/fread.html). Unlike [`read(2)`](http://pubs.opengroup.org/onlinepubs/009695399/functions/read.html) which is a system call, `fread` is a library function, implemented in user space on top of `read`. It's suitable for an application that reads for a file or dies trying; it's not suitable for a command line interpreter or for a networked program that must throttle connections cleanly, nor for a networked program that has concurrent connections and doesn't use threads.

The example of read in a loop is provided in Robert Love's Linux System Programming:

```C
ssize_t ret;
while (len != 0 && (ret = read (fd, buf, len)) != 0) {
  if (ret == -1) {
    if (errno == EINTR)
      continue;
    perror ("read");
    break;
  }
  len -= ret;
  buf += ret;
}
```

It takes care of `case i` and `case ii` and few more.



> NOTE: 上面在The OS implementation view中提及的choice，其实是处理interruption的几种choice；choice1其实就是give up；后面的几种choice都是interrupt and resume then；





### stackoverflow [When and how are system calls interrupted?](https://stackoverflow.com/questions/8049756/when-and-how-are-system-calls-interrupted)

This is a followup question to [Is a successful send() "atomic"?](https://stackoverflow.com/questions/8041171/is-a-successful-send-atomic/8041309), as I think it actually concerns system calls in general, not just sends on sockets.

Which system calls can be interrupted, and when they are, where is the interruption handled? I've learned about `SA_RESTART`, but don't exactly understand what is going on.

- If I make a system call without `SA_RESTART`, can the call be interrupted by any kind of interrupts (e.g. user input) that don't concern my application, but require the OS to abort my call and do something else? Or is it only interrupted by signals that directly concern my process (CTRL+C, socket closed, ...)?
- When setting `SA_RESTART`, what are the semantics of a send() or any other "slow" syscall? Will it always block until all of my data is transmitted or the socket goes down, or can it return with a number smaller than the count in send()'s parameter?
- Where is restarting implemented? Does the OS know that I want the call to be restarted upon any interrupts, or is some signal sent to my process and then handled by library code? Or do I have to do it myself, e.g. wrap the call in a while loop and retry as often as necessary?





### stackoverflow [Is a successful send() “atomic”?](https://stackoverflow.com/questions/8041171/is-a-successful-send-atomic)



Does a successful call to `send()` with the number returned equal to the amount specified in the size parameter guarantee that no "partial sends" will occur?

Or is there some way that the OS might be interrupted while servicing the system call, send part of the data, wait for a possibly long time, then send the rest and return without notifying me with a smaller return value?

I'm not talking about a case where there is not enough room in the kernel buffer; I realize that I would then get a smaller return value and have to try again.

**Update:** Based on the answers so far, my question could be rephrased as follows:

Is there any way for packets/data to be sent over the wire *before* the call to send() returns?