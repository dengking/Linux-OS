
## wikipedia [Stack trace](https://en.wikipedia.org/wiki/Stack_trace)

In [computing](https://en.wikipedia.org/wiki/Computing), a **stack trace** (also called **stack backtrace**[[1\]](https://en.wikipedia.org/wiki/Stack_trace#cite_note-1) or **stack traceback**[[2\]](https://en.wikipedia.org/wiki/Stack_trace#cite_note-2)) is a **report** of the active [stack frames](https://en.wikipedia.org/wiki/Stack_frame) at a certain point in time during the execution of a [program](https://en.wikipedia.org/wiki/Computer_program). When a program is run, memory is often dynamically allocated in two places：the **stack** and the **heap**. Memory is contiguously allocated on a stack but not on a heap, thus reflective of their names. Stack also refers to a programming construct, thus to differentiate it, this stack is referred to as the program's **runtime stack**. Technically, once a block of memory has been allocated on the stack, it cannot be easily removed as there can be other blocks of memory that were allocated before it. Each time a function is called in a program, a block of memory is allocated on top of the runtime stack called the **activation record** (or stack pointer.) At a high level, an activation record allocates memory for the function's parameters and local variables declared in the function.

Programmers commonly use stack tracing during interactive and post-mortem [debugging](https://en.wikipedia.org/wiki/Debugging). End-users may see a stack trace displayed as part of an [error message](https://en.wikipedia.org/wiki/Error_message), which the user can then report to a programmer.

A stack trace allows tracking the sequence of [nested functions](https://en.wikipedia.org/wiki/Nested_function) called - up to the point where the stack trace is generated. In a post-mortem scenario this extends up to the function where the failure occurred (but was not necessarily caused). [Sibling calls](https://en.wikipedia.org/wiki/Tail_call) do not appear in a stack trace.

As an example, the following [Python](https://en.wikipedia.org/wiki/Python_(programming_language)) program contains an error.

