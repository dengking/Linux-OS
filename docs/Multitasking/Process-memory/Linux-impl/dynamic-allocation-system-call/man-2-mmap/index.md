# mmap 

## 用法总结

一、创建一个file/device mapping

二、dynamic allocation

三、shared memory IPC

下面是这种用法的一些例子:

1、[clone(2)](https://man7.org/linux/man-pages/man2/clone.2.html)

2、linuxhint [How to use mmap function in C language?](https://linuxhint.com/using_mmap_function_linux/) 



## wikipedia [mmap](https://en.wikipedia.org/wiki/Mmap)

In [computing](https://en.wikipedia.org/wiki/Computing), **`mmap(2)`** is a [POSIX](https://en.wikipedia.org/wiki/POSIX)-compliant [Unix](https://en.wikipedia.org/wiki/Unix) [system call](https://en.wikipedia.org/wiki/System_call) that maps files or devices into memory. It is a method of [memory-mapped file](https://en.wikipedia.org/wiki/Memory-mapped_file) I/O. 

It implements [demand paging](https://en.wikipedia.org/wiki/Demand_paging) because file contents are not read from disk directly and initially do not use physical RAM at all. 

> NOTE: 
>
> 一、这个特性非常重要，在 [folly](https://github.com/facebook/folly)/[folly](https://github.com/facebook/folly/tree/main/folly)/[**IndexedMemPool.h**](https://github.com/facebook/folly/blob/main/folly/IndexedMemPool.h) 中，对它有介绍
>
> > The pool mmap-s the entire necessary address space when the pool is constructed, but delays element construction.  This means that only elements that are actually returned to the caller get paged into the process's resident set (RSS).
>
> 上述其实是对mmap "demand paging"非常好的阐述
>
> 二、"initially do not use physical RAM at all" 意味着它非常快

### File-backed and anonymous

> NOTE: 
>
> 这主要是它的两种application

一、*File-backed mapping* maps an area of the process's [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) to files; i.e. reading those areas of memory causes the file to be read. It is the default mapping type.

二、*Anonymous mapping* maps an area of the process's virtual memory not backed by any file. The contents are initialized to zero. In this respect an anonymous mapping is similar to `malloc`, and is used in some `malloc(3)` implementations for certain allocations. However, anonymous mappings are not part of the POSIX standard, though implemented by almost all operating systems by the `MAP_ANONYMOUS` and `MAP_ANON` flags.

### Memory visibility

> NOTE: 
>
> 这一章讨论的内容和IPC有关



## [mmap(2) — Linux manual page](https://man7.org/linux/man-pages/man2/mmap.2.html)



`mmap()` creates a new mapping in the virtual address space of the calling process.  The starting address for the new mapping is specified in `addr`.  The length argument specifies the length of the mapping (which must be greater than 0).

> NOTE: 
>
> 它不仅仅只有这种用法，它还可以用于dynamic allocation

If `addr` is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.

### The `flags` argument

#### `MAP_ANONYMOUS`

The mapping is not backed by any file; its contents are initialized to zero.  The `fd` argument is ignored; however, some implementations require `fd` to be `-1` if `MAP_ANONYMOUS` (or `MAP_ANON`) is specified, and portable applications should ensure this.  The `offset` argument should be zero. The use of `MAP_ANONYMOUS` in conjunction with `MAP_SHARED` is supported on Linux only since kernel 2.4.

> NOTE: 
>
> 用于dynamic allocation，在 [clone(2)](https://man7.org/linux/man-pages/man2/clone.2.html) 中，展示了这种用法
>
> 

### EXAMPLES

```C
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
	char *addr;
	int fd;
	struct stat sb;
	off_t offset, pa_offset;
	size_t length;
	ssize_t s;

	if (argc < 3 || argc > 4)
	{
		fprintf(stderr, "%s file offset [length]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		handle_error("open");

	if (fstat(fd, &sb) == -1) /* To obtain file size */
		handle_error("fstat");

	offset = atoi(argv[2]);
	pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
	/* offset for mmap() must be page aligned */

	if (offset >= sb.st_size)
	{
		fprintf(stderr, "offset is past end of file\n");
		exit(EXIT_FAILURE);
	}

	if (argc == 4)
	{
		length = atoi(argv[3]);
		if (offset + length > sb.st_size)
			length = sb.st_size - offset;
		/* Can't display bytes past end of file */

	}
	else
	{ /* No length arg ==> display to end of file */
		length = sb.st_size - offset;
	}

	addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
	if (addr == MAP_FAILED)
		handle_error("mmap");

	s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
	if (s != length)
	{
		if (s == -1)
			handle_error("write");

		fprintf(stderr, "partial write");
		exit(EXIT_FAILURE);
	}

	munmap(addr, length + offset - pa_offset);
	close(fd);

	exit(EXIT_SUCCESS);
}
// gcc test.c

```



## gnu libc [13.8 Memory-mapped I/O](https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html)

