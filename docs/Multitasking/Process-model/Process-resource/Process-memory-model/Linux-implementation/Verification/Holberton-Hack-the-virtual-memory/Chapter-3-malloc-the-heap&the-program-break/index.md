# Chapter 3: [Hack the Virtual Memory: malloc, the heap & the program break](https://blog.holbertonschool.com/hack-the-virtual-memory-malloc-the-heap-the-program-break/)

This is the fourth chapter in a series around virtual memory. The goal is to learn some CS basics, but in a different and more practical way.

## The heap

In this chapter we will look at the heap and `malloc` in order to answer some of the questions we ended with at the end of the [previous chapter](https://blog.holbertonschool.com/hack-the-virtual-memory-drawing-the-vm-diagram/):

- Why doesn’t our allocated memory start at the very beginning of the heap (`0x2050010` vs `02050000`)? What are those first 16 bytes used for?
- Is the heap actually growing upwards?



## `strace`, `brk` and `sbrk`

`malloc` is a “regular” function (as opposed to a system call), so it must call some kind of syscall in order to manipulate the heap. Let’s use `strace` to find out.

`strace` is a program used to trace system calls and signals. Any program will always use a few syscalls before your `main` function is executed. In order to know which syscalls are used by `malloc`, we will add a `write` syscall before and after the call to `malloc`(`3-main.c`).

```C++
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - let's find out which syscall malloc is using
 *
 * Return: EXIT_FAILURE if something failed. Otherwise EXIT_SUCCESS
 */
int main(void)
{
    void *p;

    write(1, "BEFORE MALLOC\n", 14);
    p = malloc(1);
    write(1, "AFTER MALLOC\n", 13);
    printf("%p\n", p);
    getchar();
    return (EXIT_SUCCESS);
}
```




```
julien@holberton:~/holberton/w/hackthevm3$ gcc -Wall -Wextra -pedantic -Werror 3-main.c -o 3
julien@holberton:~/holberton/w/hackthevm3$ strace ./3 
execve("./3", ["./3"], [/* 61 vars */]) = 0
...
write(1, "BEFORE MALLOC\n", 14BEFORE MALLOC
)         = 14
brk(0)                                  = 0xe70000
brk(0xe91000)                           = 0xe91000
write(1, "AFTER MALLOC\n", 13AFTER MALLOC
)          = 13
...
read(0, 
```

From the above listing we can focus on this:

```
brk(0)                                  = 0xe70000
brk(0xe91000)                           = 0xe91000
```

-> `malloc` is using the `brk` system call in order to manipulate the heap. From `brk` man page (`man brk`), we can see what this system call is doing:

```
...
       int brk(void *addr);
       void *sbrk(intptr_t increment);
...
DESCRIPTION
       brk() and sbrk() change the location of the program  break,  which  defines
       the end of the process's data segment (i.e., the program break is the first
       location after the end of the uninitialized data segment).  Increasing  the
       program  break has the effect of allocating memory to the process; decreas‐
       ing the break deallocates memory.

       brk() sets the end of the data segment to the value specified by addr, when
       that  value  is  reasonable,  the system has enough memory, and the process
       does not exceed its maximum data size (see setrlimit(2)).

       sbrk() increments the program's data space  by  increment  bytes.   Calling
       sbrk()  with  an increment of 0 can be used to find the current location of
       the program break.
```

The **program break** is the address of the first location beyond the current end of the **data region** of the program in the virual memory.

> NOTE: 关于data region，参见 `Kernel\Guide\Multitasking\Process-model\Process-resource\Process-memory-model\Virtual-address-space`，其中援引了 wikipedia [Memory address # Contents of each memory location](https://en.wikipedia.org/wiki/Memory_address#Contents_of_each_memory_location) 中的内容:
>
> In modern [multitasking](https://en.wikipedia.org/wiki/Computer_multitasking) environment, an [application](https://en.wikipedia.org/wiki/Application_program) [process](https://en.wikipedia.org/wiki/Process_(computing)) usually has in its address space (or spaces) chunks of memory of following types:
>
> 1) [Machine code](https://en.wikipedia.org/wiki/Machine_code), including:
>
> - program's own code (historically known as *[code segment](https://en.wikipedia.org/wiki/Code_segment)* or *text segment*);
> - [shared libraries](https://en.wikipedia.org/wiki/Shared_libraries).
>
> 2) [Data](https://en.wikipedia.org/wiki/Data_(computing)), including:
>
> - initialized data ([data segment](https://en.wikipedia.org/wiki/Data_segment));
> - [uninitialized (but allocated)](https://en.wikipedia.org/wiki/.bss) variables;
> - [run-time stack](https://en.wikipedia.org/wiki/Run-time_stack);
> - [heap](https://en.wikipedia.org/wiki/Heap_(programming));
> - [shared memory](https://en.wikipedia.org/wiki/Shared_memory_(interprocess_communication)) and [memory mapped files](https://en.wikipedia.org/wiki/Memory_mapped_file).
>
> 显然上述 **data region** 和 wikipedia [Memory address # Contents of each memory location](https://en.wikipedia.org/wiki/Memory_address#Contents_of_each_memory_location) 中的2) [Data](https://en.wikipedia.org/wiki/Data_(computing)) 不是同一个概念，它所指为 [data segment](https://en.wikipedia.org/wiki/Data_segment)。


![program break before the call to malloc / brk](https://s3-us-west-1.amazonaws.com/holbertonschool/medias/program-break-before.png)

By increasing the value of the **program break**, via `brk` or `sbrk`, the function `malloc` creates a new space that can then be used by the process to dynamically allocate memory (using `malloc`).


![program break after the malloc / brk call](https://s3-us-west-1.amazonaws.com/holbertonschool/medias/program-break-after.png)

So the **heap** is actually an extension of the data segment of the program.

> NOTE: 这段话总结了heap和data segment之间的关联

The first call to `brk` (`brk(0)`) returns the current address of the **program break** to `malloc`. And the second call is the one that actually creates new memory (since `0xe91000` > `0xe70000`) by increasing the value of the **program break**. In the above example, the heap is now starting at `0xe70000` and ends at `0xe91000`. Let’s double check with the `/proc/[PID]/maps` file:

```
julien@holberton:/proc/3855$ ps aux | grep \ \./3$
julien     4011  0.0  0.0   4748   708 pts/9    S+   13:04   0:00 strace ./3
julien     4014  0.0  0.0   4336   644 pts/9    S+   13:04   0:00 ./3
julien@holberton:/proc/3855$ cd /proc/4014
julien@holberton:/proc/4014$ cat maps 
00400000-00401000 r-xp 00000000 08:01 176967                             /home/julien/holberton/w/hack_the_virtual_memory/03. The Heap/3
00600000-00601000 r--p 00000000 08:01 176967                             /home/julien/holberton/w/hack_the_virtual_memory/03. The Heap/3
00601000-00602000 rw-p 00001000 08:01 176967                             /home/julien/holberton/w/hack_the_virtual_memory/03. The Heap/3
00e70000-00e91000 rw-p 00000000 00:00 0                                  [heap]
...
julien@holberton:/proc/4014$ 
```

-> `00e70000-00e91000 rw-p 00000000 00:00 0 [heap]` matches the pointers returned back to `malloc` by `brk`.

That’s great, but wait, why did `malloc` increment the heap by `00e91000` – `00e70000` = `0x21000` or `135168` bytes, when we only asked for only 1 byte?

## Many mallocs

What will happen if we call `malloc` several times? (`4-main.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - many calls to malloc
 *
 * Return: EXIT_FAILURE if something failed. Otherwise EXIT_SUCCESS
 */
int main(void)
{
    void *p;

    write(1, "BEFORE MALLOC #0\n", 17);
    p = malloc(1024);
    write(1, "AFTER MALLOC #0\n", 16);
    printf("%p\n", p);

    write(1, "BEFORE MALLOC #1\n", 17);
    p = malloc(1024);
    write(1, "AFTER MALLOC #1\n", 16);
    printf("%p\n", p);

    write(1, "BEFORE MALLOC #2\n", 17);
    p = malloc(1024);
    write(1, "AFTER MALLOC #2\n", 16);
    printf("%p\n", p);

    write(1, "BEFORE MALLOC #3\n", 17);
    p = malloc(1024);
    write(1, "AFTER MALLOC #3\n", 16);
    printf("%p\n", p);

    getchar();
    return (EXIT_SUCCESS);
}
```



```c
julien@holberton:~/holberton/w/hackthevm3$ gcc -Wall -Wextra -pedantic -Werror 4-main.c -o 4
julien@holberton:~/holberton/w/hackthevm3$ strace ./4 
execve("./4", ["./4"], [/* 61 vars */]) = 0
...
write(1, "BEFORE MALLOC #0\n", 17BEFORE MALLOC #0
)      = 17
brk(0)                                  = 0x1314000
brk(0x1335000)                          = 0x1335000
write(1, "AFTER MALLOC #0\n", 16AFTER MALLOC #0
)       = 16
...
write(1, "0x1314010\n", 100x1314010
)             = 10
write(1, "BEFORE MALLOC #1\n", 17BEFORE MALLOC #1
)      = 17
write(1, "AFTER MALLOC #1\n", 16AFTER MALLOC #1
)       = 16
write(1, "0x1314420\n", 100x1314420
)             = 10
write(1, "BEFORE MALLOC #2\n", 17BEFORE MALLOC #2
)      = 17
write(1, "AFTER MALLOC #2\n", 16AFTER MALLOC #2
)       = 16
write(1, "0x1314830\n", 100x1314830
)             = 10
write(1, "BEFORE MALLOC #3\n", 17BEFORE MALLOC #3
)      = 17
write(1, "AFTER MALLOC #3\n", 16AFTER MALLOC #3
)       = 16
write(1, "0x1314c40\n", 100x1314c40
)             = 10
...
read(0, 
```

-> `malloc` is NOT calling `brk` each time we call it.

The first time, `malloc` creates a new space (the heap) for the program (by increasing the program break location). The following times, `malloc` uses the same space to give our program “new” chunks of memory. Those “new” chunks of memory are part of the memory previously allocated using `brk`. This way, `malloc` doesn’t have to use syscalls (`brk`) every time we call it, and thus it makes `malloc` – and our programs using `malloc` – faster. It also allows `malloc` and `free` to optimize the usage of the memory.

Let’s double check that we have only one heap, allocated by the first call to `brk`:

```
julien@holberton:/proc/4014$ ps aux | grep \ \./4$
julien     4169  0.0  0.0   4748   688 pts/9    S+   13:33   0:00 strace ./4
julien     4172  0.0  0.0   4336   656 pts/9    S+   13:33   0:00 ./4
julien@holberton:/proc/4014$ cd /proc/4172
julien@holberton:/proc/4172$ cat maps
00400000-00401000 r-xp 00000000 08:01 176973                             /home/julien/holberton/w/hack_the_virtual_memory/03. The Heap/4
00600000-00601000 r--p 00000000 08:01 176973                             /home/julien/holberton/w/hack_the_virtual_memory/03. The Heap/4
00601000-00602000 rw-p 00001000 08:01 176973                             /home/julien/holberton/w/hack_the_virtual_memory/03. The Heap/4
01314000-01335000 rw-p 00000000 00:00 0                                  [heap]
7f4a3f2c4000-7f4a3f47e000 r-xp 00000000 08:01 136253                     /lib/x86_64-linux-gnu/libc-2.19.so
7f4a3f47e000-7f4a3f67e000 ---p 001ba000 08:01 136253                     /lib/x86_64-linux-gnu/libc-2.19.so
7f4a3f67e000-7f4a3f682000 r--p 001ba000 08:01 136253                     /lib/x86_64-linux-gnu/libc-2.19.so
7f4a3f682000-7f4a3f684000 rw-p 001be000 08:01 136253                     /lib/x86_64-linux-gnu/libc-2.19.so
7f4a3f684000-7f4a3f689000 rw-p 00000000 00:00 0 
7f4a3f689000-7f4a3f6ac000 r-xp 00000000 08:01 136229                     /lib/x86_64-linux-gnu/ld-2.19.so
7f4a3f890000-7f4a3f893000 rw-p 00000000 00:00 0 
7f4a3f8a7000-7f4a3f8ab000 rw-p 00000000 00:00 0 
7f4a3f8ab000-7f4a3f8ac000 r--p 00022000 08:01 136229                     /lib/x86_64-linux-gnu/ld-2.19.so
7f4a3f8ac000-7f4a3f8ad000 rw-p 00023000 08:01 136229                     /lib/x86_64-linux-gnu/ld-2.19.so
7f4a3f8ad000-7f4a3f8ae000 rw-p 00000000 00:00 0 
7ffd1ba73000-7ffd1ba94000 rw-p 00000000 00:00 0                          [stack]
7ffd1bbed000-7ffd1bbef000 r--p 00000000 00:00 0                          [vvar]
7ffd1bbef000-7ffd1bbf1000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
julien@holberton:/proc/4172$ 
```

-> We have only one [heap] and the addresses match those returned by `sbrk`: `0x1314000` & `0x1335000`