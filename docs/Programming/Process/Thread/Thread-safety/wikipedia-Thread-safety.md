# wikipedia [Thread safety](https://en.wikipedia.org/wiki/Thread_safety)

**Thread safety** is a [computer programming](https://en.wikipedia.org/wiki/Computer_programming) concept applicable to [multi-threaded](https://en.wikipedia.org/wiki/Thread_(computing)) code. Thread-safe code only manipulates shared data structures in a manner that ensures that all threads behave properly and fulfill their design specifications without unintended interaction. There are various strategies for making thread-safe data structures.[[1\]](https://en.wikipedia.org/wiki/Thread_safety#cite_note-1)[[2\]](https://en.wikipedia.org/wiki/Thread_safety#cite_note-2)

A program may execute code in several threads simultaneously in a shared [address space](https://en.wikipedia.org/wiki/Address_space) where each of those threads has access to virtually all of the [memory](https://en.wikipedia.org/wiki/Computer_storage) of every other thread. Thread safety is a property that allows code to run in multithreaded environments by re-establishing some of the correspondences between the actual flow of control and the text of the program, by means of [synchronization](https://en.wikipedia.org/wiki/Synchronization_(computer_science)).



## Levels of thread safety

[Software libraries](https://en.wikipedia.org/wiki/Library_(computing)) can provide certain thread-safety guarantees. For example, concurrent reads might be guaranteed to be thread-safe, but concurrent writes might not be. Whether a program using such a library is thread-safe depends on whether it uses the library in a manner consistent with those guarantees.

Different vendors use slightly different terminology for thread-safety:[[3\]](https://en.wikipedia.org/wiki/Thread_safety#cite_note-3)[[4\]](https://en.wikipedia.org/wiki/Thread_safety#cite_note-4)[[5\]](https://en.wikipedia.org/wiki/Thread_safety#cite_note-5)[[6\]](https://en.wikipedia.org/wiki/Thread_safety#cite_note-6)

- **Thread safe**: Implementation is guaranteed to be free of [race conditions](https://en.wikipedia.org/wiki/Race_condition#Computing) when accessed by multiple threads simultaneously.
- **Conditionally safe**: Different threads can access different objects simultaneously, and access to shared data is protected from race conditions.
- **Not thread safe**: Data structures should not be accessed simultaneously by different threads.

Thread safety guarantees usually also include design steps to prevent or limit the risk of different forms of [deadlocks](https://en.wikipedia.org/wiki/Deadlock), as well as optimizations to maximize concurrent performance. However, deadlock-free guarantees cannot always be given, since deadlocks can be caused by [callbacks](https://en.wikipedia.org/wiki/Callback_(computer_programming)) and violation of [architectural layering](https://en.wikipedia.org/wiki/Architectural_layer) independent of the library itself.



## Implementation approaches

Below we discuss two approaches for avoiding [race conditions](https://en.wikipedia.org/wiki/Race_condition#Computing) to achieve thread safety.

The first class of approaches focuses on avoiding **shared state**, and includes:

- [Re-entrancy](https://en.wikipedia.org/wiki/Reentrant_(subroutine)) 

  Writing code in such a way that it can be partially executed by a thread, reexecuted by the same thread or simultaneously executed by another thread and still correctly complete the original execution. This requires the saving of [state](https://en.wikipedia.org/wiki/State_(computer_science)) information in variables local to each execution, usually on a stack, instead of in [static](https://en.wikipedia.org/wiki/Static_variable) or [global](https://en.wikipedia.org/wiki/Global_variable) variables or other non-local state. All non-local state must be accessed through atomic operations and the data-structures must also be reentrant.

- [Thread-local storage](https://en.wikipedia.org/wiki/Thread-local_storage) 

  Variables are localized so that each thread has its own private copy. These variables retain their values across [subroutine](https://en.wikipedia.org/wiki/Subroutine) and other code boundaries, and are thread-safe since they are local to each thread, even though the code which accesses them might be executed simultaneously by another thread.

- [Immutable objects](https://en.wikipedia.org/wiki/Immutable_object) 

  The state of an object cannot be changed after construction. This implies both that only read-only data is shared and that inherent(固有的) thread safety is attained. Mutable (non-const) operations can then be implemented in such a way that they create new objects instead of modifying existing ones. This approach is characteristic of [functional programming](https://en.wikipedia.org/wiki/Functional_programming) and is also used by the *string* implementations in Java, C# and Python.[[7\]](https://en.wikipedia.org/wiki/Thread_safety#cite_note-7)

The second class of approaches are **synchronization-related**, and are used in situations where shared state cannot be avoided:

- [Mutual exclusion](https://en.wikipedia.org/wiki/Mutual_exclusion)

  Access to shared data is *serialized* using mechanisms that ensure only one thread reads or writes to the shared data at any time. Incorporation of mutual exclusion needs to be well thought out, since improper usage can lead to side-effects like [deadlocks](https://en.wikipedia.org/wiki/Deadlock), [livelocks](https://en.wikipedia.org/wiki/Livelock) and [resource starvation](https://en.wikipedia.org/wiki/Resource_starvation).

- [Atomic operations](https://en.wikipedia.org/wiki/Linearizability) 

  Shared data is accessed by using atomic operations which cannot be interrupted by other threads. This usually requires using special [machine language](https://en.wikipedia.org/wiki/Machine_language) instructions, which might be available in a [runtime library](https://en.wikipedia.org/wiki/Runtime_library). Since the operations are atomic, the shared data is always kept in a valid state, no matter how other threads access it. Atomic operations form the basis of many thread locking mechanisms, and are used to implement mutual exclusion primitives.



## Examples

In the following piece of [Java](https://en.wikipedia.org/wiki/Java_(programming_language)) code, the method is thread-safe:

```java
class Counter {
    private int i = 0;

    public synchronized void inc() {
        i++;
    }
}
```

In the [C programming language](https://en.wikipedia.org/wiki/C_(programming_language)), each thread has its own stack. However, a [static variable](https://en.wikipedia.org/wiki/Static_variable) is not kept on the stack; all threads share simultaneous access to it. If multiple threads overlap while running the same function, it is possible that a static variable might be changed by one thread while another is midway through checking it. This difficult-to-diagnose [logic error](https://en.wikipedia.org/wiki/Logic_error), which may compile and run properly most of the time, is called a [race condition](https://en.wikipedia.org/wiki/Race_condition#Software). One common way to avoid this is to use another shared variable as a ["lock" or "mutex"](https://en.wikipedia.org/wiki/Lock_(computer_science)) (from **mut**ual **ex**clusion).

In the following piece of C code, the function is thread-safe, but not reentrant:

```c
# include <pthread.h>

int increment_counter ()
{
 static int counter = 0;
 static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

 // only allow one thread to increment at a time
 pthread_mutex_lock(&mutex);

 ++counter;

 // store value before any other threads increment it further
 int result = counter;

 pthread_mutex_unlock(&mutex);

 return result;
}
```

SUMMARY:the above code is not reentrant,because it use static variable.Refer to [this article](https://www.ibm.com/developerworks/library/l-reent/) for an answer。

In the above, `increment_counter` can be called by different threads without any problem since a mutex is used to synchronize all access to the shared `counter` variable. But if the function is used in a reentrant interrupt handler and a second interrupt arises inside the function, the second routine will hang forever. As interrupt servicing can disable other interrupts, the whole system could suffer.

The same function can be implemented to be both thread-safe and reentrant using the lock-free [atomics](https://en.wikipedia.org/wiki/Linearizability) in [C++11](https://en.wikipedia.org/wiki/C%2B%2B11):

```c++
# include <atomic>

int increment_counter ()
{
 static std::atomic<int> counter(0);

 // increment is guaranteed to be done atomically
 int result = ++counter;

 return result;
}
```



## See also

- [Concurrency control](https://en.wikipedia.org/wiki/Concurrency_control)
- [Exception safety](https://en.wikipedia.org/wiki/Exception_safety)
- [Priority inversion](https://en.wikipedia.org/wiki/Priority_inversion)
- [ThreadSafe](https://en.wikipedia.org/wiki/ThreadSafe)