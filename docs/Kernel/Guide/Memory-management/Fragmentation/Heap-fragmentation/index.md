# Heap Fragmentation

## cpp4arduino [What is Heap Fragmentation?](https://cpp4arduino.com/2018/11/06/what-is-heap-fragmentation.html)

> NOTE: 这篇文章非常好，不仅非常形象的描述了heap fragmentation的含义，并且描述了解决这个问题的方法。

- *There is a lot of free memory, so why allocation fails?*
- *My program ran well for hours/days/months, why does it crash now?*
- *Why does my program run slower over time?*

Believe or not, the answers to these three questions are the same: you have a **heap fragmentation** problem. In this article, we’ll see what it means and how to fix it.

### What is the heap?

The “heap” is the area of the RAM where the **dynamic memory allocation** happens. Every time you call `malloc()`, you reserve a block of memory in the heap.

![The three areas of the RAM, with the heap highlighted](https://cpp4arduino.com/assets/images/2018/11/the-three-areas-of-the-ram.svg)

Similarly, every time you call `new`, you reserve a block in the heap. Because `new` calls `malloc()` and `delete` calls `free()`, everything we’ll see equally applies to `new` and `delete`.

Very often, your program allocates heap memory without explicitly calling `malloc()`. For example, when you create a `String` object, the constructor allocates some space in the heap to store the characters.

### What is heap fragmentation?

When you call `free()` to release a block, you create a hole of unused memory. After some time, the heap becomes a **swiss cheese with many holes**.

> NOTE: "**swiss cheese with many holes**"是一个非常形象的比喻

Here is a simplified view with an imaginary heap of 30 bytes:

![free() creates a hole in the heap](https://cpp4arduino.com/assets/images/2018/11/free-creates-a-hole.svg)

The holes count as free memory, so there are 20 bytes available. However, we are unable to allocate 20 bytes because there is not a consecutive(连续的) block of 20 free bytes.

This phenomenon is what we call “heap fragmentation.” It’s an inefficient utilization of the RAM that prevents a program from using the full capacity of the microcontroller(微控制器).

> NOTE: 在嵌入式中，使用"microcontroller"这个词语

### When does fragmentation happen?

Suppose you just released a block of memory and therefore created a hole in the heap.

![A hole in the heap](https://cpp4arduino.com/assets/images/2018/11/a-hole-in-the-heap.svg)

Is that always a problem? There are three possibilities.

First possibility: you allocate another block of the same size. The new block takes the place left by the old one. No hole remains.

![A block of the same size fills the hole](https://cpp4arduino.com/assets/images/2018/11/a-block-of-the-same-size-fill-the-hole.svg)

Second possibility: you allocate a smaller block. The new block fits in the hole but doesn’t fill it. A small hole remains.

![A smaller block fits in the hole](https://cpp4arduino.com/assets/images/2018/11/a-smaller-block-fits-in-the-hole.svg)

Third possibility: you allocate a larger block. The new block cannot fit in the hole, so it’s allocated further in the heap. A big hole remains.

![A larger block doesn't fit in the hole](https://cpp4arduino.com/assets/images/2018/11/a-larger-block-doesnt-fit-in-the-hole.svg)

As you see, only a program that allocates and releases blocks of different size increases the **heap fragmentation**.

### An example

Now that we get the theory, let’s see a concrete example.

Consider a `loop()` function that downloads the weather forecasts from a web server. It first saves the response a big `String`; then it extracts the date, the city, the temperature, the humidity(湿度), and the weather description in five `String`s of various size.

```C++
String serverResponse;
String date, city, temperature, humidity, description;
void loop() {
   serverResponse = downloadFromServer();
   date = extractDate(serverResponse);
   city = extractCity(serverResponse);
   temperature = extractTemperature(serverResponse);
   description = extractDescription(serverResponse);
}
```

The first iteration of `loop()` is OK: it allocates the `String`s in the heap but doesn’t release them, so no fragmentation happens.

Then, each iteration creates new `String`s to replace the old ones. The new `String`s allocate new blocks and the old `String`s release the old blocks.

Here is the problem: every time the server returns a different response, the sizes of the blocks change. As we saw, allocation of **varying** sizes creates holes in the heap, which increases the fragmentation.

> NOTE: varying size是非常容易造成heap fragmentation的，因此一个解决方法是使用 "Strategy 3: Constant allocation"

### Measuring the fragmentation

There are several formal definitions for the fragmentation; in this article, I’ll use this simple definition:

![Fragmentation's formula](https://cpp4arduino.com/assets/images/2018/11/fragmentation-formula.svg)

Let’s try some numbers in this formula. Suppose you have 1KB of free RAM.

- At 0% (no fragmentation), you can allocate 1KB in one shot.
- At 25%, you can allocate 750B in one shot.
- At 50%, you can only allocate 500B in one shot.
- At 75%, you can only allocate 250B in one shot.

A value of 50% or more is considered high and can seriously impede(阻碍) your program, as we’ll see.

### How fragmentation evolves over time

Now that we have a formal definition, let’s write a program that will show the evolution of the fragmentation over time.

#### Computing the fragmentation

To compute the fragmentation percentage, we apply the formula and multiply by 100:

```C++
float getFragmentation() {
  return 100 - getLargestAvailableBlock() * 100.0 / getTotalAvailableMemory();
}
```

As you can guess, `getLargestAvailableBlock()` returns the size of the largest allocable block, and `getTotalAvailableMemory()` returns the total free memory.

Writing these two functions is the trickiest(棘手的) part of this program because they are dependent on the platform. In [the code samples](https://github.com/bblanchon/cpp4arduino/tree/master/HeapFragmentation), I implemented a version for AVR (Arduino UNO et al.) and another for ESP8266.

#### Drilling(演练) holes

To produce fragmentation, we saw that we could use a few `String`s of various size and replace them repeatedly.

The easiest way to do that is to have an array of `String` and to replace them with random values:

```C++
String strings[NUMBER_OF_STRINGS];

for (String &s : strings)
   s = generateRandomString();
```

As the name suggests, `generateRandomString()` returns a `String` whose length varies from one call to the other:

```C++
String generateRandomString() {
  String result;
  int len = random(SMALLEST_STRING, LARGEST_STRING);
  while (len--) result += '?';
  return result;
}
```

This program roughly simulates the weather forecast example.

#### The results

I obtained the following graph with 20 strings whose length varied from 10 to 50 characters. The program ran on an Arduino UNO.

![A graph showing the evolution of heap fragmentation over time](https://cpp4arduino.com/assets/images/2018/11/evolution-of-heap-fragmentation.svg)

As you see, when the program starts, the fragmentation is close to zero and then increases irregularly until it stabilizes at about 70%.

I encourage you to tweak the settings to see the effect on the fragmentation. In particular, you’ll see that when `SMALLEST_STRING` and `LARGEST_STRING` are equals, i.e., if the `String`s are all of the same sizes, no fragmentation occurs.

### Why is heap fragmentation bad?

We saw how fragmentation increases, now let’s talk about the consequences of a high fragmentation level.

#### Consequence 1: Unreliable program

By definition, a high fragmentation level means you have a lot of free memory, but you can only allocate small blocks. If your program needs a bigger block, it will not get it and will stop working.

#### Consequence 2: Degraded performance

A highly fragmented heap is slower because the memory allocator takes more time to find the best hole, the so-called “best-fit.”

### If it’s so huge, why nobody talks about it?

Heap fragmentation is a solved problem for most programmers, but not for us Arduino programmers. Let’s see how other platforms handle the problem.

#### Solution 1: Virtual memory

The programs running on our computers use **Virtual Memory**. The value of the pointer is not the physical location in the RAM; instead, the CPU translates the address on the fly. This **decoupling** allows defragmenting the RAM without moving anything but requires dedicated hardware that we do not have on our microcontrollers.

#### Solution 2: Optimized allocators

Either as part of the standard library or as a linked library, C++ programs running on a computer embeds a **heap allocator** that is much more efficient than what we have on our Arduinos.

The most common optimization is to gather small blocks into bins: one bin for blocks of 4 bytes, one bin for 8 bytes, etc. Thanks to this technique the small objects don’t contribute to and are not affected by the fragmentation.

#### Solution 3: Short string optimization

Even if the C++ standard doesn’t mandate it, all implementations of `std::string` support the “Small String Optimization,” or SSO. `std::string` stores short strings locally and only uses the heap for long strings.

By reducing the number of small objects in the heap, the SSO reduces the fragmentation. Unfortunately, the `String` class doesn’t perform SSO in Arduino.

#### Solution 4: Heap compacting(紧凑)

In languages with managed memory, the garbage collector moves the memory blocks to squash the holes.

We cannot use this technique in C++ because moving a block would change its address, so all pointers to this block would be invalid.

#### Solution 5: Memory pool

Instead of allocating many small blocks, a program can allocate only one big block and divide it as it needs. Within this block, the program is free to use any allocation strategy.

For example, ArduinoJson implements this technique with `DynamicJsonBuffer`.

### So what can I do to reduce heap fragmentation?

None of these techniques applies to our Arduino programs, which means we have to code in a way that reduces the fragmentation.

#### Strategy 1: Avoid heap (in particular, avoid String)

In many cases, we can avoid dynamic allocation. Instead of allocating objects in the heap, we place them in the stack or in the globals. By design, these two areas are not fragmented.

For example, we could replace all `String` objects with plain old `char[]`. Not only we would reduce the fragmentation, but we would also create a smaller and faster executable.

#### Strategy 2: Short object lifetime

**Short-lived objects** have a small impact on the heap fragmentation. They rapidly come and go, leaving the heap in the same state.

Long-lived objects, however, have a substantial impact on the heap fragmentation. They book their room and stick here for a long time, leaving the heap with an unmovable block in the middle.

So, if you still needed another reason to avoid global variables, there you have it.

#### Strategy 3: Constant allocation

As we saw, repeated allocations of the same size don’t cause fragmentation; so, we could keep our objects in the heap but always use the same size.

For example, if we have a string that can have between 10 and 100 characters, we could always reserve 100 characters:

```
myString.reserve(100);
```

As curious as it sounds, allocating more memory than strictly necessary allows more efficient utilization of the RAM.

### Conclusion

This article was unusually long, I hoped you’ve gone through it.

Here is what you need to remember:

1. Fragmentation is an inefficient utilization of the RAM.
2. Arduino programs, more than others, are affected by fragmentation.
3. It’s our responsibility as programmers to fight against fragmentation.

As usual, you’ll find the source code of the examples [on GitHub](https://github.com/bblanchon/cpp4arduino/tree/master/HeapFragmentation).

I’ll see you soon with another article!