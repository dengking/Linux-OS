[TOC]



# [“Out Of Memory” Does Not Refer to Physical Memory](https://blogs.msdn.microsoft.com/ericlippert/2009/06/08/out-of-memory-does-not-refer-to-physical-memory/)





# [Is Virtual memory infinite?](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite)

I have been asked in an interview if virtual memory is infinite? I answered saying that it is not infinite. Then the interviewer asked the explanation and what I suggested was that in windows we do have a manual way to configure virtual memory to a certain limit.

I would like to know if Virtual memory is really Infinite?



## [A](https://stackoverflow.com/a/6609035)

**First of all, forget the idea that virtual memory is limited by the size of pointers on your machine.**

**Virtual memory limits** are not the same as **addressing space**. You can address more virtual memory than is available in your pointer-based address space using paging.

- **Virtual memory upper** limits are set by the OS: for example, on 32-bit Windows the limit is 16TB, and on 64-bit Windows the limit is 256TB.
- Virtual memory is also physically limited by the available disc space.

For an excellent overview, which addresses various misconceptions, see the following:

**http://blogs.msdn.com/b/ericlippert/archive/2009/06/08/out-of-memory-does-not-refer-to-physical-memory.aspx**

***COMMENTS***

- Yes @stusmith i think you are right about You can address more virtual memory than is available in your pointer-based ,and it is whole idea of using virtual memory. – [Amit Singh Tomar](https://stackoverflow.com/users/448413/amit-singh-tomar) [Jul 7 '11 at 10:42](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment7800273_6609035) 

- 1

  Virtual memory is not exactly limited by disk space, it can be allocated but not mapped, so-called "reserved virtual memory". See [msdn.microsoft.com/en-us/library/windows/desktop/…](https://msdn.microsoft.com/en-us/library/windows/desktop/aa366887(v=vs.85).aspx) and `MEM_RESERVE` for explanation. – [Sergey Alaev](https://stackoverflow.com/users/1445898/sergey-alaev) [Apr 6 '17 at 9:50](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment73572065_6609035) 





## [A](https://stackoverflow.com/a/6608900)

At the very least, the size of virtual memory is limited by the size of pointers on given platform (unless it has near/far pointers and non-flat memory model). For example, you cannot address more than about 2^32 (4GB) of memory using single 32-bit pointer.

In practice, the virtual memory must be backed up with something eventually -- like a pagefile on disk -- so the size of storage enforces a more practical limit.

- Sorry, that's just wrong. Look up "PAE" ([Physical Address Extension](https://en.wikipedia.org/wiki/Physical_Address_Extension)) for example. – [stusmith](https://stackoverflow.com/users/6604/stusmith) [Jul 7 '11 at 10:18](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment7799899_6608900)

- 1

  @stusmith : A PAE-enabled Linux-kernel requires that the CPU also support PAE. So, it is limited by the computer architecture, right? – [Priyank Bhatnagar](https://stackoverflow.com/users/610856/priyank-bhatnagar) [Jul 7 '11 at 10:28](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment7800052_6608900)

- 2

  @logic_max: Yes, but a 32-bit Intel chip is capable of supporting PAE. Maybe a better way of putting it is: **it is the lowest value of [chip support, OS limit, disk space]**. Usually that lowest value is disk space. – [stusmith](https://stackoverflow.com/users/6604/stusmith) [Jul 7 '11 at 10:30](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment7800095_6608900)

- 

  @stusmith I don't think that ARM, PowerPC, MIPS, or many other CPUs have PAE. Neither do older **x86** CPUs. There is no right answer to this poor question. In fact, depending on how you count (for the system, for a process), the answer is different, but still not infinite. Down-vote anyone who says it is infinite. – [artless noise](https://stackoverflow.com/users/1880339/artless-noise)[May 30 '14 at 17:47](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment36913024_6608900) 

- 1

  It is also not true that everything **must** be backed by disk. A large *zero initialized* array can all be backed by a single page of zeros (typically 4-8k). Any read from any address will show zero. On the first write to a page, a fault happens and then the page is allocated (needs disk or memory) and remapped. This can allow large sparse arrays. – [artless noise](https://stackoverflow.com/users/1880339/artless-noise) [Jun 2 '14 at 20:52](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment36993051_6608900) 

- 

  The sum of the virtual address spaces of *all* the processes running at once can be larger than what the 'user pointer' register can address - **since the 'process id' is effectively part of the virtual address**. In some cases these "process-unique" addresses actually point to the same PM (e.g. shared libraries, data shared after fork() ) - but even allowing for that, it's possible for the total amount of truly distinct VM pages to exceed what one process can address. – [greggo](https://stackoverflow.com/users/450000/greggo) [Aug 13 '14 at 16:51](https://stackoverflow.com/questions/6608820/is-virtual-memory-infinite#comment39416112_6608900)



# [How much memory can a 64bit machine address at a time?](https://superuser.com/questions/168114/how-much-memory-can-a-64bit-machine-address-at-a-time)

