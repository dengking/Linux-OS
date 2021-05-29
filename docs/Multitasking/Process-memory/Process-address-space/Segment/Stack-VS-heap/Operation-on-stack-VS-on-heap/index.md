# Operation on the stack VS operation on the heap

在工程Linux-OS中，分析了process的memory model，它主要由如下两部分组成:

1 stack

2 heap

那operation on the stack VS operation on the heap? 下面是分析素材: 

## 素材

### 1)stackoverflow [Meaning of acronym SSO in the context of std::string](https://stackoverflow.com/questions/10315041/meaning-of-acronym-sso-in-the-context-of-stdstring) # [A](https://stackoverflow.com/a/10319672)

Operations on **automatic variables** ("from the stack", which are variables that you create without calling `malloc` / `new`) are generally much faster than those involving the free store ("the heap", which are variables that are created using `new`). 

However, the size of automatic arrays is fixed at compile time, but the size of arrays from the free store is not. 

Moreover, the stack size is limited (typically a few MiB), whereas the free store is only limited by your system's memory.

SSO is the **Short / Small String Optimization**. A `std::string` typically stores the string as a pointer to the **free store** ("the heap"), which gives similar performance characteristics as if you were to call `new char [size]`. This prevents a **stack overflow** for very large strings, but it can be slower, especially with **copy operations**. As an optimization, many implementations of `std::string` create a **small automatic array**,

> NOTE: C++中的分类:
>
> 1 automatic object
>
> 2 dynamic object
>
> 上述operation，包括了:
>
> 1 new

### 2) stackoverflow [What and where are the stack and heap?](https://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap) # [A](https://stackoverflow.com/a/80113)

The stack is faster because the access pattern makes it trivial to allocate and deallocate memory from it (a pointer/integer is simply incremented or decremented), while the heap has much more complex bookkeeping involved in an allocation or deallocation. Also, each byte in the stack tends to be reused very frequently which means it tends to be mapped to the processor's cache, making it very fast. Another performance hit for the heap is that the heap, being mostly a global resource, typically has to be **multi-threading safe**, i.e. each allocation and deallocation needs to be - typically - synchronized with "all" other heap accesses in the program.

## Benchmark

前面给出了理论的分析，那么我们要如何来进行验证呢? 下面是以C++ `std::string`来进行说明的例子，关于C++ `std::string`的实现，参见 工程programming language的 `C-and-C++\String\C++string` 章节，它是非常能够体现Operation on the stack VS operation on the heap: 

#### stackoverflow [Meaning of acronym SSO in the context of std::string](https://stackoverflow.com/questions/10315041/meaning-of-acronym-sso-in-the-context-of-stdstring) # [A](https://stackoverflow.com/a/51796541) # Benchmarks

As already explained by the other answers, SSO means **Small / Short String Optimization**. The motivation behind this optimization is the undeniable(不可否认的) evidence that applications in general handle much more shorter strings than longer strings.

As explained by David Stone [in his answer above](https://stackoverflow.com/a/10319672/4289700), the `std::string` class uses an internal buffer to store contents up to a given length, and this eliminates the need to dynamically allocate memory. This makes the code *more efficient* and *faster*.

[This other related answer](https://stackoverflow.com/a/28003328/4289700) clearly shows that the size of the internal buffer depends on the `std::string` implementation, which varies from platform to platform (see benchmark results below).



Here is a small program that benchmarks the **copy operation** of lots of strings with the same length. It starts printing the time to copy 10 million strings with length = 1. Then it repeats with strings of length = 2. It keeps going until the length is 50.

```cpp
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

static const char CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static const int ARRAY_SIZE = sizeof(CHARS) - 1;

static const int BENCHMARK_SIZE = 10000000;
static const int MAX_STRING_LENGTH = 50;

using time_point = std::chrono::high_resolution_clock::time_point;

void benchmark(std::vector<std::string> &list)
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	// force a copy of each string in the loop iteration
	for (const auto s : list)
	{
		std::cout << s;
	}

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cerr << list[0].length() << ',' << duration << '\n';
}

void addRandomString(std::vector<std::string> &list, const int length)
{
	std::string s(length, 0);
	for (int i = 0; i < length; ++i)
	{
		s[i] = CHARS[rand() % ARRAY_SIZE];
	}
	list.push_back(s);
}

int main()
{
	std::cerr << "length,time\n";

	for (int length = 1; length <= MAX_STRING_LENGTH; length++)
	{
		std::vector<std::string> list;
		for (int i = 0; i < BENCHMARK_SIZE; i++)
		{
			addRandomString(list, length);
		}
		benchmark(list);
	}

	return 0;
}
// g++ --std=c++11 test.cpp
```

If you want to run this program, you should do it like `./a.out > /dev/null` so that the time to print the strings isn't counted. The numbers that matter are printed to `stderr`, so they will show up in the console.

I have created charts with the output from my MacBook and Ubuntu machines. Note that there is a huge jump in the time to copy the strings when the length reaches a given point. That's the moment when strings don't fit in the internal buffer anymore and memory allocation has to be used.

Note also that on the linux machine, the jump happens when the length of the string reaches 16. On the macbook, the jump happens when the length reaches 23. This confirms that SSO depends on the platform implementation.

## Optimization

### 避免system call new heap allocation

由于相比与automatic object，system call new heap allocation一个dynamic object是非常耗时的，因此我们需要尽可能地**避免system call new heap allocation**: 

下面是一些例子: 

#### Producer/consumer模型

在producer/consumer模型中，每次都调用system call new出一个message，这是非常低效的，而是应该:

1) 使用buffer/cache/queue，提前分配好内存空间，然后向这个buffer/cache/queue进行read/write，无论是read还是write，其实所对应的都是copy，相比于system call而言，copy是更加高效的

2) 对于message，最好使用automatic object，通过copy to/from buffer/cache/queue 

最最典型的例子是spdlog asynchronous的做法。

#### C++ `std::string` SSO

避免每次system call new heap allocation的另外一个例子是C++ `std::string` SSO，参见工程programming language的`C-and-C++\String\C++string`章节。

## thoughts

相比于copy、move，new才是慢的