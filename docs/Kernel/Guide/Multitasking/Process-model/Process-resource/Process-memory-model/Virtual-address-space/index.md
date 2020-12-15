# Virtual address space

## wikipedia [Virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space)

In [computing](https://en.wikipedia.org/wiki/Computing), a **virtual address space** (**VAS**) or **address space** is the set of ranges of virtual addresses that an [operating system](https://en.wikipedia.org/wiki/Operating_system) makes available to a process. The range of virtual addresses usually starts at a low address and can extend to the highest address allowed by the computer's [instruction set architecture](https://en.wikipedia.org/wiki/Instruction_set) and supported by the [operating system](https://en.wikipedia.org/wiki/Operating_system)'s pointer size implementation, which can be 4 [bytes](https://en.wikipedia.org/wiki/Bytes) for [32-bit](https://en.wikipedia.org/wiki/32-bit) or 8 [bytes](https://en.wikipedia.org/wiki/Bytes) for [64-bit](https://en.wikipedia.org/wiki/64-bit) OS versions. This provides several benefits, one of which is security through [process isolation](https://en.wikipedia.org/wiki/Process_isolation) assuming each process is given a separate [address space](https://en.wikipedia.org/wiki/Address_space).

> NOTE: process isolation是非常有必要的，因为当OS中运行多个process的时候，OS就需要进行调度，因此就有可能暂停某个process的执行而转去执行另外一个process；可能过来一些时间后，再resume之前暂停的process；可以看到，为了达到使process可中断，不同process之间的isolation非常重要，被中断的process的address space应当要免收其他的正在running的process的影响；

![Virtual address space and physical address space relationship.svg](https://upload.wikimedia.org/wikipedia/commons/thumb/3/32/Virtual_address_space_and_physical_address_space_relationship.svg/300px-Virtual_address_space_and_physical_address_space_relationship.svg.png)

### Example



When a new application on a [32-bit](https://en.wikipedia.org/wiki/32-bit) OS is executed, the process has a 4 [GiB](https://en.wikipedia.org/wiki/Gibibyte) VAS: each one of the [memory addresses](https://en.wikipedia.org/wiki/Memory_address) (from 0 to $2^{32} − 1$) in that space can have a single byte as a value. Initially, none of them have values ('-' represents no value). Using or setting values in such a VAS would cause a [memory exception](https://en.wikipedia.org/wiki/Page_fault).

***SUMMARY*** : 上述32-bit指的是OS的Word size

```
           0                                           4 GiB
VAS        |----------------------------------------------|
```

Then the application's executable file is mapped into the VAS. Addresses in the process VAS are mapped to bytes in the exe file. The OS manages the mapping:

```
           0                                           4 GiB
VAS        |---vvvvvvv------------------------------------|
mapping        |-----|
file bytes     app.exe
```

The v's are values from bytes in the [mapped file](https://en.wikipedia.org/wiki/Memory-mapped_file). Then, required [DLL](https://en.wikipedia.org/wiki/Dynamic-Link_Library) files are mapped (this includes custom libraries as well as system ones such as `kernel32.dll` and `user32.dll`):

```
           0                                           4 GiB
VAS        |---vvvvvvv----vvvvvv---vvvv-------------------|
mapping        |||||||    ||||||   ||||
file bytes     app.exe    kernel   user
```

The process then starts executing bytes in the exe file. However, the only way the process can use or set '-' values in its VAS is to ask the OS to map them to bytes from a **file**. A common way to use VAS memory in this way is to map it to the [page file](https://en.wikipedia.org/wiki/Page_file). The page file is a single file, but multiple distinct sets of contiguous bytes can be mapped into a VAS:

```
           0                                           4 GiB
VAS        |---vvvvvvv----vvvvvv---vvvv----vv---v----vvv--|
mapping        |||||||    ||||||   ||||    ||   |    |||
file bytes     app.exe    kernel   user   system_page_file
```

And different parts of the page file can map into the VAS of different processes:

```
           0                                           4 GiB
VAS 1      |---vvvv-------vvvvvv---vvvv----vv---v----vvv--|
mapping        ||||       ||||||   ||||    ||   |    |||
file bytes     app1 app2  kernel   user   system_page_file
mapping             ||||  ||||||   ||||       ||   |
VAS 2      |--------vvvv--vvvvvv---vvvv-------vv---v------|
```

On [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) 32-bit, by default, only 2 GiB are made available to processes for their own use.[[2\]](https://en.wikipedia.org/wiki/Virtual_address_space#cite_note-2) The other 2 GiB are used by the operating system. On later 32-bit editions of Microsoft Windows it is possible to extend the user-mode virtual address space to 3 GiB while only 1 GiB is left for kernel-mode virtual address space by marking the programs as IMAGE_FILE_LARGE_ADDRESS_AWARE and enabling the /3GB switch in the boot.ini file. 

On Microsoft Windows 64-bit, in a process running an executable that was linked with /LARGEADDRESSAWARE:NO, the operating system artificially limits the user mode portion of the process's virtual address space to 2 GiB. This applies to both 32- and 64-bit executables.[[5\]](https://en.wikipedia.org/wiki/Virtual_address_space#cite_note-5)[[6\]](https://en.wikipedia.org/wiki/Virtual_address_space#cite_note-6) Processes running executables that were linked with the /LARGEADDRESSAWARE:YES option, which is the default for 64-bit Visual Studio 2010 and later, have access to more than 2 GiB of virtual address space: Up to 4 GiB for 32-bit executables, up to 8 TiB for 64-bit executables in Windows through Windows 8, and up to 128 TiB for 64-bit executables in Windows 8.1 and later. 

Allocating memory via [C](https://en.wikipedia.org/wiki/C_(programming_language))'s [malloc](https://en.wikipedia.org/wiki/Malloc) establishes the page file as the backing store for any new virtual address space. However, a process can also [explicitly map](https://en.wikipedia.org/wiki/Memory-mapped_file) file bytes.

### Linux

For [x86](https://en.wikipedia.org/wiki/X86) CPUs, [Linux](https://en.wikipedia.org/wiki/Linux) 32-bit allows splitting the user and kernel address ranges in different ways: *3G/1G user/kernel* (default), *1G/3G user/kernel* or *2G/2G user/kernel*. 







## TODO: Memory layout of a process in linux 


https://inst.eecs.berkeley.edu/~cs161/sp15/slides/lec3-sw-vulns.pdf

https://inst.eecs.berkeley.edu/

https://cpp.tech-academy.co.uk/memory-layout/

https://cpp.tech-academy.co.uk/

https://stackoverflow.com/questions/3080375/how-is-the-memory-layout-of-a-c-c-program



geeksforgeeks [Memory Layout of C Programs](https://www.geeksforgeeks.org/memory-layout-of-c-program/)



## Memory layout of process with thread

### stackoverflow [The memory layout of a multithreaded process](https://stackoverflow.com/questions/18149218/the-memory-layout-of-a-multithreaded-process)

[A](https://stackoverflow.com/a/18149464)

I just tested it with a short Python "program" in the interactive interpreter:

```python
import threading
import time
def d(): time.sleep(120)
t = [threading.Thread(target=d) for _ in range(250)]
for i in t: i.start()
```

Then I pressed `^Z` and looked at the appropriate `/proc/.../maps` file for this process.

It showed me

```
00048000-00049000 ---p 00000000 00:00 0
00049000-00848000 rw-p 00000000 00:00 0          [stack:28625]
00848000-00849000 ---p 00000000 00:00 0
00849000-01048000 rw-p 00000000 00:00 0          [stack:28624]
01048000-01049000 ---p 00000000 00:00 0
01049000-01848000 rw-p 00000000 00:00 0          [stack:28623]
01848000-01849000 ---p 00000000 00:00 0
01849000-02048000 rw-p 00000000 00:00 0          [stack:28622]
...
47700000-47701000 ---p 00000000 00:00 0
47701000-47f00000 rw-p 00000000 00:00 0          [stack:28483]
47f00000-47f01000 ---p 00000000 00:00 0
47f01000-48700000 rw-p 00000000 00:00 0          [stack:28482]
...
bd777000-bd778000 ---p 00000000 00:00 0
bd778000-bdf77000 rw-p 00000000 00:00 0          [stack:28638]
bdf77000-bdf78000 ---p 00000000 00:00 0
bdf78000-be777000 rw-p 00000000 00:00 0          [stack:28639]
be777000-be778000 ---p 00000000 00:00 0
be778000-bef77000 rw-p 00000000 00:00 0          [stack:28640]
bef77000-bef78000 ---p 00000000 00:00 0
bef78000-bf777000 rw-p 00000000 00:00 0          [stack:28641]
bf85c000-bf87d000 rw-p 00000000 00:00 0          [stack]
```

which shows what I already suspected: the stacks are allocated with a relative distance which is (hopefully) large enough.

The stacks have a relative distance of 8 MiB (this is the default value; it is possible to set it otherwise), and one page at the top is protected in order to detect a stack overflow.

The one at the bottom is the "main" stack; it can - in this example - grow until the next one is reached.