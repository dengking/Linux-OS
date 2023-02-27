# thegreenplace [Basics of Futexes](https://eli.thegreenplace.net/2018/basics-of-futexes/)

The main idea is to enable a more efficient way for **userspace code** to synchronize multiple threads, with minimal kernel involvement.

In this post I want to provide a basic overview of **futexes**, how they work, and how they're used to implement the more familiar **synchronization primitives** in higher-level APIs and languages.

An important disclaimer: **futexes** are a very low-level feature of the Linux kernel, suitable for use in foundational runtime components like the `C/C++` standard libraries. It is extremely unlikely that you will ever need to use them in application code.

## Motivation

Before the introduction of **futexes**, system calls were required for locking and unlocking **shared resources** (for example `semop`). **System calls** are relatively expensive, however, requiring a **context switch** from **userspace** to **kernel space**; as programs became increasingly concurrent, locks started showing up on profiles as a significant percentage of the run time. This is very unfortunate, given that locks accomplish no real work ("business logic") but are only there to guarantee that access to **shared resources** is safe.

The futex proposal is based on a clever observation: in most cases, locks are actually not contended. If a thread comes upon a free lock, locking it can be cheap because most likely no other thread is trying to lock it at the exact same time. So we can get by without a system call, attemping much cheaper atomic operations first [2]. There's a very high chance that the atomic instruction will succeed.

> NOTE: 
>
> futex是基于这样的现实而进行优化的: 在大多数情况下，lock是并不竞争的: "in most cases, locks are actually not contended", 在这种情况下，对于这种lock，"locking it can be cheap"；基于此futex提出了一种方案: "So we can get by without a system call, attemping much cheaper atomic operations first [2]. There's a very high chance that the atomic instruction will succeed" 
>
> "get by"的意思是: 过得去、尚可、设法继续存在；即首先 "attemping much cheaper atomic operations"。

However, in the unlikely event that another thread *did* try to take the lock at the same time, the atomic approach may fail. In this case there are two options. We can busy-loop using the atomic until the lock is cleared; while this is 100% userspace, it can also be extremely wasteful since looping can significantly occupy a core, and the lock can be held for a long time. The alternative is to "sleep" until the lock is free (or at least there's a high chance that it's free); we need the kernel to help with that, and this is where futexes come in.

> NOTE: 
>
> non-blocking: busy-loop VS blocking: sleep-wakeup

## Simple futex use - waiting and waking

The [futex(2) system call](http://man7.org/linux/man-pages/man2/futex.2.html) multiplexes a lot of functionality on top of a single interface. I will not discuss any of the advanced options here (some of them are so esoteric(深奥) they're not even officially documented) but will focus on just `FUTEX_WAIT` and `FUTEX_WAKE`. 

> The `futex()` system call provides a method for waiting until a certain condition becomes true. It is typically used as a **blocking construct** in the context of **shared-memory synchronization**. When using futexes, the majority of the synchronization operations are performed in user space. A user-space program employs the `futex()` system call only when it is likely that the program has to block for a longer time until the condition becomes true. Other `futex()` operations can be used to wake any processes or threads waiting for a particular condition.

Simply stated, a futex is a kernel construct that helps **userspace code** synchronize on **shared events**. Some **userspace processes** (or threads) can wait on an event (`FUTEX_WAIT`), while another **userspace process** can signal the event (`FUTEX_WAKE`) to notify waiters. The waiting is efficient - the waiters are suspended by the kernel and are only scheduled anew when there's a wake-up signal.

> NOTE: 
>
> "anew"的意思是"重新"



Let's study a [simple example](https://github.com/eliben/code-for-blog/blob/master/2018/futex-basics/futex-basic-process.c) demonstrating basic usage of futexes to coordinate two processes. The `main` function sets up the machinery and launches a child process that:

1、Waits for `0xA` to be written into a **shared memory slot**.

2、Writes `0xB` into the same **memory slot**.

Meanwhile, the parent:

1、Writes `0xA` into the **shared memory slot**.

2、Waits for `0xB` to be written into the slot.

This is a simple handshake between two processes. Here's the code:

```C++
int main(int argc, char** argv) {
  int shm_id = shmget(IPC_PRIVATE, 4096, IPC_CREAT | 0666);
  if (shm_id < 0) {
    perror("shmget");
    exit(1);
  }
  int* shared_data = shmat(shm_id, NULL, 0);
  *shared_data = 0;

  int forkstatus = fork();
  if (forkstatus < 0) {
    perror("fork");
    exit(1);
  }

  if (forkstatus == 0) {
    // Child process

    printf("child waiting for A\n");
    wait_on_futex_value(shared_data, 0xA);

    printf("child writing B\n");
    // Write 0xB to the shared data and wake up parent.
    *shared_data = 0xB;
    wake_futex_blocking(shared_data);
  } else {
    // Parent process.

    printf("parent writing A\n");
    // Write 0xA to the shared data and wake up child.
    *shared_data = 0xA;
    wake_futex_blocking(shared_data);

    printf("parent waiting for B\n");
    wait_on_futex_value(shared_data, 0xB);

    // Wait for the child to terminate.
    wait(NULL);
    shmdt(shared_data);
  }

  return 0;
}

```

Note that we use POSIX shared memory APIs to create a memory location mapped into both processes. We can't just use a regular pointer here, because the address spaces of the two processes will be different [[3\]](https://eli.thegreenplace.net/2018/basics-of-futexes/#id8).

### `wait_on_futex_value`

Here is `wait_on_futex_value`:

```C++
void wait_on_futex_value(int* futex_addr, int val) {
  while (1) {
    int futex_rc = futex(futex_addr, FUTEX_WAIT, val, NULL, NULL, 0);
    if (futex_rc == -1) {
      if (errno != EAGAIN) {
        perror("futex");
        exit(1);
      }
    } else if (futex_rc == 0) {
      if (*futex_addr == val) {
        // This is a real wakeup.
        return;
      }
    } else {
      abort();
    }
  }
}
```



### `wake_futex_blocking`

Here is `wake_futex_blocking`:

```C++
void wake_futex_blocking(int* futex_addr) {
  while (1) {
    int futex_rc = futex(futex_addr, FUTEX_WAKE, 1, NULL, NULL, 0);
    if (futex_rc == -1) {
      perror("futex wake");
      exit(1);
    } else if (futex_rc > 0) {
      return;
    }
  }
}
```



## Futexes are kernel queues for userspace code

Simply stated, a `futex` is a queue the kernel manages for userspace convenience. It lets userspace code ask the kernel to suspend until a certain condition is satisfied, and lets other userspace code signal that condition and wake up waiting processes. Earlier we've menioned busy-looping as one approach to wait on success of atomic operations; a kernel-managed queue is the much more efficient alternative, absolving(赦免) userspace code from the need to burn billions of CPU cycles on pointless spinning.

Here's a diagram from LWN's ["A futex overview and update"](https://lwn.net/Articles/360699/):

![Futex implementation diagram from LWN](https://eli.thegreenplace.net/images/2018/futex-lwn-diagram.png)

In the Linux kernel, futexes are implemented in `kernel/futex.c`. The kernel keeps a **hash table** keyed by the address to quickly find the proper queue data structure and adds the calling process to the **wait queue**. There's quite a bit of complication, of course, due to using fine-grained locking within the kernel itself and the various advanced options of futexes.