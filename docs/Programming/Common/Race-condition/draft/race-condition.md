# [What is a race condition?](https://stackoverflow.com/questions/34510/what-is-a-race-condition)

When writing multi-threaded applications, one of the most common problems experienced are **race conditions**.

My questions to the community are:

What is a race condition? How do you detect them? How do you handle them? Finally, how do you prevent them from occurring?



***COMMENTS*** : 

There is a great chapter in the [Secure Programming for Linux HOWTO](http://www.dwheeler.com/secure-programs/Secure-Programs-HOWTO/avoid-race.html) that describes what they are, and how to avoid them. – [Craig H](https://stackoverflow.com/users/2328/craig-h) [Aug 29 '08 at 15:59](https://stackoverflow.com/questions/34510/what-is-a-race-condition#comment56911256_34510)

I'd like to mention that - without specifying the language - most parts of this question cannot be answered properly, because in different languages, the definition, the consequences and the tools to prevent them might differ. – [MikeMB](https://stackoverflow.com/users/2881849/mikemb) [Apr 21 '15 at 17:18](https://stackoverflow.com/questions/34510/what-is-a-race-condition#comment47688054_34510)

@MikeMB. Agreed, except when analyzing byte code execution, like it is done by Race Catcher (see this thread [stackoverflow.com/a/29361427/1363844](http://stackoverflow.com/a/29361427/1363844)) we can address all those approximately 62 languages that compile to byte code (see [en.wikipedia.org/wiki/List_of_JVM_languages](https://en.wikipedia.org/wiki/List_of_JVM_languages)) – [Ben](https://stackoverflow.com/users/1363844/ben) [Aug 12 '16 at 5:49](https://stackoverflow.com/questions/34510/what-is-a-race-condition#comment65179234_34510) 



## [A](https://stackoverflow.com/a/34550)

A **race condition** occurs when two or more threads can access **shared data** and they try to **change** it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. Therefore, the result of the change in data is dependent on the thread scheduling algorithm, i.e. both threads are "racing" to access/change the data.

Problems often occur when one thread does a "check-then-act" (e.g. "check" if the value is X, then "act" to do something that depends on the value being X) and another thread does something to the value in between the "check" and the "act". E.g:

```C
if (x == 5) // The "Check"
{
   y = x * 2; // The "Act"

   // If another thread changed x in between "if (x == 5)" and "y = x * 2" above,
   // y will not be equal to 10.
}
```

The point being, y could be 10, or it could be anything, depending on whether another thread changed x in between the check and act. You have no real way of knowing.

In order to prevent race conditions from occurring, you would typically put a lock around the shared data to ensure only one thread can access the data at a time. This would mean something like this:

```C
// Obtain lock for x
if (x == 5)
{
   y = x * 2; // Now, nothing can change x until the lock is released. 
              // Therefore y = 10
}
// release lock for x
```



## [A](https://stackoverflow.com/a/34745)

A "race condition" exists when multithreaded (or otherwise parallel) code that would access a shared resource could do so in such a way as to cause unexpected results.

Take this example:

```c
for ( int i = 0; i < 10000000; i++ )
{
   x = x + 1; 
}
```

If you had 5 threads executing this code at once, the value of x WOULD NOT end up being 50,000,000. It would in fact vary with each run.

This is because, in order for each thread to increment the value of x, they have to do the following: (simplified, obviously)

```
Retrieve the value of x
Add 1 to this value
Store this value to x
```

Any thread can be at any step in this process at any time, and they can step on each other when a shared resource is involved. The state of x can be changed by another thread during the time between x is being read and when it is written back.

Let's say a thread retrieves the value of x, but hasn't stored it yet. Another thread can also retrieve the **same** value of x (because no thread has changed it yet) and then they would both be storing the **same** value (x+1) back in x!

Example:

```
Thread 1: reads x, value is 7
Thread 1: add 1 to x, value is now 8
Thread 2: reads x, value is 7
Thread 1: stores 8 in x
Thread 2: adds 1 to x, value is now 8
Thread 2: stores 8 in x
```

Race conditions can be avoided by employing some sort of **locking** mechanism before the code that accesses the shared resource:

```c
for ( int i = 0; i < 10000000; i++ )
{
   //lock x
   x = x + 1; 
   //unlock x
}
```

Here, the answer comes out as 50,000,000 every time.

For more on locking, search for: mutex, semaphore, critical section, shared resource.



***SUMMARY*** :

```c
#include <pthread.h>
#include <stdio.h>

int i = 0;
pthread_t ntid;

void* task(void *arg){
    for ( int i = 0; i < 10000000; i++ )
    {
       x = x + 1; 
    }
    print("%d\n", x);
}

int main(){
    int  err;
    for(int i=0;i<5;i++){
        err = pthread_create(&ntid, NULL, task, NULL);
        if (err != 0)
            print("can’t create thread");
			exit(err);
    }
    exit(0);
}
```

