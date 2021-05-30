# Unix philosophy



## wikipedia [Unix philosophy](https://en.wikipedia.org/wiki/Unix_philosophy)

The **Unix philosophy**, originated by [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson), is a set of cultural norms and philosophical approaches to [minimalist](https://en.wikipedia.org/wiki/Minimalism_(computing)), [modular](https://en.wikipedia.org/wiki/Modularity_(programming)) [software development](https://en.wikipedia.org/wiki/Software_development). It is based on the experience of leading developers of the [Unix](https://en.wikipedia.org/wiki/Unix) [operating system](https://en.wikipedia.org/wiki/Operating_system). Early Unix developers were important in bringing the concepts of modularity and reusability into software engineering practice, spawning a "[software tools](https://en.wikipedia.org/wiki/Software_tools)" movement. Over time, the leading developers of Unix (and programs that ran on it) established a set of cultural norms for developing software, norms which became as important and influential as the technology of Unix itself; this has been termed the "Unix philosophy."

The Unix philosophy emphasizes building simple, short, clear, modular, and extensible code that can be easily maintained and repurposed by developers other than its creators. The Unix philosophy favors [composability](https://en.wikipedia.org/wiki/Composability) as opposed to [monolithic design](https://en.wikipedia.org/wiki/Monolithic_application).

> NOTE: 
>
> 最后一段话强调了Unix philosophy的核心所在，即composability。



### Origin

The UNIX philosophy is documented by [Doug McIlroy](https://en.wikipedia.org/wiki/Doug_McIlroy)[[1\]](https://en.wikipedia.org/wiki/Unix_philosophy#cite_note-taoup-ch1s6-1) in the Bell System Technical Journal from 1978:[[2\]](https://en.wikipedia.org/wiki/Unix_philosophy#cite_note-2)

1、Make each program do one thing well. To do a new job, build a fresh rather than complicate old programs by adding new "features".

> NOTE: 
>
> 1、single responsibility principle

2、Expect the output of every program to become the input to another, as yet unknown, program. Don't clutter output with extraneous information. Avoid stringently（严格的） columnar or binary input formats. Don't insist on interactive input.

> NOTE: 
>
> IO direction重定向来实现pipeline，这是在Unix-like system中，经常使用的一种模式

3、Design and build software, even（甚至是） operating systems, to be tried early, ideally within weeks. Don't hesitate to throw away the clumsy parts and rebuild them.

> NOTE: 
>
> 1、设计和构建软件，甚至是操作系统，要及早尝试，最好在几周内完成。 不要犹豫扔掉笨拙的部分并重建它们。

4、Use tools in preference to unskilled help to lighten a programming task, even if you have to detour to build the tools and expect to throw some of them out after you've finished using them.

> NOTE: 
>
> 1、使用工具优先于不熟练的帮助来减轻编程任务，即使你不得不绕道去构建工具并期望在你使用它们之后抛出一些工具。



It was later summarized by [Peter H. Salus](https://en.wikipedia.org/wiki/Peter_H._Salus) in A Quarter-Century of Unix (1994):[[1\]](https://en.wikipedia.org/wiki/Unix_philosophy#cite_note-taoup-ch1s6-1)

- Write programs that do one thing and do it well.
- Write programs to work together.
- Write programs to handle text streams, because that is a universal interface.

In their award-winning Unix paper of 1974, Ritchie and Thompson quote the following design considerations:[[3\]](https://en.wikipedia.org/wiki/Unix_philosophy#cite_note-3)

- Make it easy to write, test, and run programs.
- Interactive use instead of [batch processing](https://en.wikipedia.org/wiki/Batch_processing).
- [Economy](https://en.wikipedia.org/wiki/Frugality) and [elegance](https://en.wikipedia.org/wiki/Elegance) of design due to size constraints ("salvation through suffering").
- [Self-supporting](https://en.wikipedia.org/wiki/Self_supporting) system: all Unix software is maintained under Unix.

> The whole philosophy of UNIX seems to stay out of [assembler](https://en.wikipedia.org/wiki/Assembly_language).
>
> — [Michael Sean Mahoney](https://en.wikipedia.org/wiki/Michael_Sean_Mahoney)[[4\]](https://en.wikipedia.org/wiki/Unix_philosophy#cite_note-interview-4)