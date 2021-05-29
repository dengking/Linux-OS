# [PTHREAD_SETCANCELSTATE(3)](http://man7.org/linux/man-pages/man3/pthread_setcancelstate.3.html)

## NAME

`pthread_setcancelstate`,  `pthread_setcanceltype`  -  set  cancelability state and type

## SYNOPSIS

```c
       #include <pthread.h>

       int pthread_setcancelstate(int state, int *oldstate);
       int pthread_setcanceltype(int type, int *oldtype);
```

Compile and link with `-pthread`.

## DESCRIPTION

The `pthread_setcancelstate()` sets the cancelability state of the calling thread to the value given in state.  The previous cancelability state of the thread is returned in the buffer pointed to by `oldstate`.  The state argument must have one of the following values:

### `PTHREAD_CANCEL_ENABLE`

The thread is cancelable.  This is the default cancelability state in all new threads, including the initial thread.  The thread's cancelability type determines when a cancelable thread will respond to a cancellation request.

### `PTHREAD_CANCEL_DISABLE`

The thread is not cancelable.  If a cancellation request is received, it is blocked until cancelability is enabled.



The `pthread_setcanceltype()` sets the cancelability type of the calling thread to the value given in type.  The previous cancelability type of the thread is returned in the buffer pointed to by `oldtype`.  The type argument must have one of the following values:

### `PTHREAD_CANCEL_DEFERRED`

A cancellation request is deferred until the thread next calls a function that is a cancellation point (see [pthreads(7)](http://man7.org/linux/man-pages/man7/pthreads.7.html)). This is the default cancelability type in all new threads, including the initial thread.

### `PTHREAD_CANCEL_ASYNCHRONOUS`

The thread can be canceled at any time.  (Typically, it will be canceled immediately upon receiving a cancellation request, but the system doesn't guarantee this.)

The set-and-get operation performed by each of these functions is atomic with respect to other threads in the process calling the same function.



## NOTES

For details of what happens when a thread is canceled, see [pthread_cancel(3)](http://man7.org/linux/man-pages/man3/pthread_cancel.3.html).

Briefly disabling cancelability is useful if a thread performs some critical action that must not be interrupted by a cancellation request.  Beware of disabling cancelability for long periods, or around operations that may block for long periods, since that will render the thread unresponsive to cancellation requests.

### Asynchronous cancelability

Setting the cancelability type to `PTHREAD_CANCEL_ASYNCHRONOUS` is rarely useful.  Since the thread could be canceled at any time, it cannot safely reserve resources (e.g., allocating memory with [malloc(3)](http://man7.org/linux/man-pages/man3/malloc.3.html)), acquire mutexes, semaphores, or locks, and so on. **Reserving resources** is unsafe because the application has no way of knowing what the state of these resources is when the thread is canceled; that is, did cancellation occur before the resources were reserved, while they were reserved, or after they were released? Furthermore, some internal data structures (e.g., the linked list of free blocks managed by the [malloc(3)](http://man7.org/linux/man-pages/man3/malloc.3.html) family of functions) may be left in an **inconsistent state** if cancellation occurs in the middle of the
function call.  Consequently, clean-up handlers cease（停止） to be useful.

Functions that can be safely asynchronously canceled are called **async-cancel-safe** functions.  POSIX.1-2001 and POSIX.1-2008 require only that `pthread_cancel(3)`, `pthread_setcancelstate()`, and `pthread_setcanceltype()` be **async-cancel-safe**.  In general, other library functions can't be safely called from an **asynchronously cancelable thread**.

One of the few circumstances in which asynchronous cancelability is useful is for cancellation of a thread that is in a pure compute-bound loop.

