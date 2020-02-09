

# [Virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space)

In [computing](https://en.wikipedia.org/wiki/Computing), a **virtual address space** (**VAS**) or **address space** is the set of ranges of virtual addresses that an [operating system](https://en.wikipedia.org/wiki/Operating_system) makes available to a process. The range of virtual addresses usually starts at a low address and can extend to the highest address allowed by the computer's [instruction set architecture](https://en.wikipedia.org/wiki/Instruction_set) and supported by the [operating system](https://en.wikipedia.org/wiki/Operating_system)'s pointer size implementation, which can be 4 [bytes](https://en.wikipedia.org/wiki/Bytes) for [32-bit](https://en.wikipedia.org/wiki/32-bit) or 8 [bytes](https://en.wikipedia.org/wiki/Bytes) for [64-bit](https://en.wikipedia.org/wiki/64-bit) OS versions. This provides several benefits, one of which is security through [process isolation](https://en.wikipedia.org/wiki/Process_isolation) assuming each process is given a separate [address space](https://en.wikipedia.org/wiki/Address_space).

> NOTE: process isolation是非常有必要的，因为当OS中运行多个process的时候，OS就需要进行调度，因此就有可能暂停某个process的执行而转去执行另外一个process；可能过来一些时间后，再resume之前暂停的process；可以看到，为了达到使process可中断，不同process之间的isolation非常重要，被中断的process的address space应当要免收其他的正在running的process的影响；

![Virtual address space and physical address space relationship.svg](https://upload.wikimedia.org/wikipedia/commons/thumb/3/32/Virtual_address_space_and_physical_address_space_relationship.svg/300px-Virtual_address_space_and_physical_address_space_relationship.svg.png)

## Example



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

## Linux

For [x86](https://en.wikipedia.org/wiki/X86) CPUs, [Linux](https://en.wikipedia.org/wiki/Linux) 32-bit allows splitting the user and kernel address ranges in different ways: *3G/1G user/kernel* (default), *1G/3G user/kernel* or *2G/2G user/kernel*. 







