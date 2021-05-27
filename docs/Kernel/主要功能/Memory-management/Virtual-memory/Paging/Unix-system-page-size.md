# [how is page size determined in virtual address space?](https://unix.stackexchange.com/questions/128213/how-is-page-size-determined-in-virtual-address-space)

Linux uses a **virtual memory system** where all of the addresses are [**virtual addresses**](https://en.wikipedia.org/wiki/Virtual_memory) and not **physical addresses**. These **virtual addresses** are converted into **physical addresses** by the processor.

To make this translation easier, virtual and physical memory are divided into **pages**. Each of these pages is given a unique number; the page frame number.

Some **page sizes** can be 2 KB, 4 KB, etc. But how is this page size number determined? Is it influenced by the size of the architecture? For example, a 32-bit bus will have 4 GB address space.



## [A](https://unix.stackexchange.com/a/128218)

You can find out a system's default page size by querying its configuration via the `getconf`command:

```shell
$ getconf PAGE_SIZE
4096
```

or

```shell
$ getconf PAGESIZE
4096
```

**NOTE:** The above units are typically in bytes, so the 4096 equates to 4096 bytes or 4kB.

This is hardwired in the Linux kernel's source here:

### Example

```C
$ more /usr/src/kernels/3.13.9-100.fc19.x86_64/include/asm-generic/page.h
...
...
/* PAGE_SHIFT determines the page size */

#define PAGE_SHIFT  12
#ifdef __ASSEMBLY__
#define PAGE_SIZE   (1 << PAGE_SHIFT)
#else
#define PAGE_SIZE   (1UL << PAGE_SHIFT)
#endif
#define PAGE_MASK   (~(PAGE_SIZE-1))
```

### How does shifting give you 4096?

When you shift bits, you're performing a binary multiplication by 2. So in effect a shifting of bits to the left (`1 << PAGE_SHIFT`) is doing the multiplication of 2^12 = 4096.

```shell
$ echo "2^12" | bc
4096
```