# [How does word size affect the amount of virtual address space available?](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available)

So, I should really know this stuff already, but I am starting to learn more about the lower levels of software development. I am currently reading *Computer Systems: A Programmer's Perspective.* by Bryant O'Hallaron.

I am on chapter 2 and he is talking about the way data is represented internally.

I am having trouble understanding something conceptually and I am sure that I'm about to make my ignorance lucid here.

I understand that a "word" is just a set of bytes and that the word size is just how many **bits wide** the **system bus** is. But, he also says: "the most important system parameter determined by the **word size** is the maximum size of the **virtual address space**. That is, for a machine with a w-**bit** word size, the virtual addresses can range from 0 to (2^w)-1, giving the program access to at most 2^w **bytes**"

I am both confused on the general relationship between the word size and the amount of addresses in the system and how the specific formula is w-bit word size=2^w bytes of memory available.

I am really scratching my head here, can some one help me out?

**EDIT:** I actually misinterpreted his definition of a word and consequently the definition of word size. What he really said was:

> Busses are typically designed to transfer fixed-sized chunks of bytes known as *words*. The number of bytes in a word (the *word size*) is a fundamental system parameter that varies across systems. most machines today have word sizes of either 4 bytes(32 bits) or 8 bytes(64 bits). For the sake of our discussion here, we will assume a word size of 4 bytes, **and we will assume that buses transfer only one word at a time.**

which is pretty much a catch-all for the cases discussed in the answers without having to go into detail. He also said he would be oversimplifying some things, perhaps in later sections he will go into more detail.



## [A](https://softwareengineering.stackexchange.com/a/267227)

The idea is that one word of memory can be used as an address in the address space (i.e., a word is wide enough to hold a pointer). If an address were larger than a word, addressing would require multiple sequential words. That's not impossible, but is unreasonably complicated (and likely slow).

So, given an *w*-bit word, how many values can that word represent? How may addresses can it denote? Since any bit can take on two values, we end up with 2·2·2·…·2 = $2^w$ addresses. Addresses are counted starting by zero, so the highest address is $2^w$  - 1.

Example using a three-bit word: There are $2^3$=8 possible addresses:

```
bin: 000 001 010 011 100 101 110 111
dec:   0   1   2   3   4   5   6   7
```

The highest address is $2^3-1 = 8 - 1 = 7$. If the memory is an array of bytes and the address is an index to this array, then using a three-bit word we can only address eight bytes. Even if the array physically holds more bytes, we cannot reach them with a restricted index. Therefore, the amount of **virtual memory** is restricted by the **word size**.

***COMMENTS***

- Ahh, I get it now, so to have 8GB ram on a 32 bit system would be pointless then. – [Luke](https://softwareengineering.stackexchange.com/users/144763/luke) [Dec 23 '14 at 18:36](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544415_267227)

- 1

  Of course, counterexamples to the idea that word length and memory size are usually equal are common: the 6502 had an 8-bit word size but 16-bit addresses, the 8086 had 16-bit words and 20-bit addresses, the 80286 was likewise 16-bit but used 24-bit addresses, and the Pentium Pro was a 32-bit processor supporting 36-bit addresses. All of these are harder to use than the simple word = pointer scheme we've become used to, but architectures like this are not exactly rare, historically speaking. – [Jules](https://softwareengineering.stackexchange.com/users/66037/jules) [Dec 23 '14 at 18:42](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544421_267227)

- 

  @LukeP Yes, at 4GB or more a 64-bit system is a must. However, there's a technique called “[physical address extension](https://en.wikipedia.org/wiki/Physical_Address_Extension)” that allows a 32-bit OS running on compatible hardware to handle more than 4GB of physical memory – although the limit on virtual memory still holds. – [amon](https://softwareengineering.stackexchange.com/users/60357/amon) [Dec 23 '14 at 18:43](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544422_267227)

- 

  @lukep - not exactly pointless, just that you'd have to jump through certain hoops to use the extra memory that might make it more hassle than it's e worth. Note that 32-bit versions of server variants of Windows, for example, can handle up to 64gb of memory, but end-user systems are limited to 4gb because a lot of things stop working properly when you try to extend the memory beyond the 4gb barrier. – [Jules](https://softwareengineering.stackexchange.com/users/66037/jules) [Dec 23 '14 at 18:46](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544425_267227)

- 

  Related reading: [x86 memory segmentation](https://en.wikipedia.org/wiki/X86_memory_segmentation), probably the one architecture people are likely to be familiar with that had a segmented memory model and all the hassles that came with it. – user22815 [Dec 23 '14 at 21:35](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544476_267227)



# [A](https://softwareengineering.stackexchange.com/a/267229)

> I understand that a "word" is just a set of bytes and that the word size is just how many bits wide the system bus is. But, he also says: "the most important system parameter determined by the word size is the maximum size of the virtual address space. That is, for a machine with a w-bit word size, the virtual addresses can range from 0 to (2^w)-1, giving the program access to at most 2^w bytes"

That's assuming a lot. The assumptions are not unreasonable, but holding them in a book pretending to introduce computer architecture to programmers seems a weakness of the book.

A word is a sequence of bits with the width used for normal argument of integer computation. (And that's still assuming that the architecture doesn't define a word with another, smaller, size which was the word used in an ancestor of the architecture.) That is often the size of integer registers. Bus have often that size, but they may be smaller or larger and are not really used to define what is the word size.

There is an important class of processors for which data addresses have the same size as word. That's not always true. There are other processors may have a smaller or bigger address space (this is somewhat out of fashion, the 8086 had 16-bit words but the addresses were 20-bit wide, the PDP-10 had 36-bit words but the addresses were 18-bit wide).

There is an important class of processors for which each byte of memory has its own address. That's not always true. There are other processors which give addresses to words, not to bytes. That's also out of fashion for general purpose processors, but more specialized one like DSP are still doing that.

So if you have a processor which is in those two classes, a word of width w bits may holds 2^w different value, each referencing one byte. This is a maximum for the virtual memory size. The processor may have architectural restrictions which prevent the use of all that space (reserving part for the OS, for IO), or it may have other restrictions (the data structures used to map the virtual memory to the physical one in 64-bit processors often are not able to map the whole 64-bit space). There are at least two instances of machines which ignored the high order byte of 32-bit addresses and programmers have taken advantage of that (using those bits for flags and other stuff) leading to a painful evolution when later one wanted to use the bits for addresses (IBM 360 and MC68000 as used on Mac).

- I actually misinterpreted his original definition. I'm editing the question to reflect his exact definition – [Luke](https://softwareengineering.stackexchange.com/users/144763/luke) [Dec 23 '14 at 18:46](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544424_267229)

- 1

  @LukeP, that doesn't change much. Word size is a property of the ISA (Instruction Set Architecture). Bus sizes is a property of the implementation of the ISA (also called micro-architecture). A bus may be wider or smaller than a word, that's not important for the programmer. The same ISA may be implemented several times, with different bus size. – [AProgrammer](https://softwareengineering.stackexchange.com/users/11575/aprogrammer) [Dec 23 '14 at 18:54](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544427_267229) 

- 

  but the bus is still going to be sending the same amount of information over, it just may have to be done in a different amount of "words" right? – [Luke](https://softwareengineering.stackexchange.com/users/144763/luke) [Dec 23 '14 at 18:59](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544429_267229)

- 

  Yes. You have to think about the ISA as the interface between software and hardware. And as most interface, its goal is to expose functionality and hide implementation. And buses (there may be several, of different width) are part of the implementation. – [AProgrammer](https://softwareengineering.stackexchange.com/users/11575/aprogrammer) [Dec 23 '14 at 20:44](https://softwareengineering.stackexchange.com/questions/267218/how-does-word-size-affect-the-amount-of-virtual-address-space-available#comment544464_267229)

