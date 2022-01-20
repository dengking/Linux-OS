# [Bash Reference Manual](https://www.gnu.org/software/bash/manual/html_node/index.html)



### [1.2 What is a shell?](https://www.gnu.org/software/bash/manual/html_node/What-is-a-shell_003f.html#What-is-a-shell_003f)

At its base, a shell is simply a macro processor that executes commands. The term **macro processor** means functionality where text and symbols are expanded to create larger expressions.

A Unix shell is both a **command interpreter** and a **programming language**. 

A shell allows execution of GNU commands, both **synchronously** and **asynchronously**. The shell waits for synchronous commands to complete before accepting more input; asynchronous commands continue to execute in parallel with the shell while it reads and executes additional commands. The *redirection* constructs permit fine-grained control of the input and output of those commands. Moreover, the shell allows control over the contents of commands’ environments.

> NOTE: 
>
> "*redirection*"特指的是IO redirection，即IO重定向，它让我们能够将上一个的输出作为下一个的输入，即pipeline

Shells also provide a small set of built-in commands (*builtins*) implementing functionality impossible or inconvenient to obtain via separate utilities. For example, `cd`, `break`, `continue`, and `exec` cannot be implemented outside of the shell because they directly manipulate the shell itself. The `history`, `getopts`, `kill`, or `pwd`builtins, among others, could be implemented in separate utilities, but they are more convenient to use as builtin commands. All of the shell builtins are described in subsequent sections.



Shells offer features geared specifically for interactive use rather than to augment the programming language. These interactive features include **job control**, command line editing, command history and aliases. Each of these features is described in this manual.

> NOTE: 
>
> "job control"，这是我们经常会碰到的



## [2 Definitions](https://www.gnu.org/software/bash/manual/bash.html#Definitions)



## [3 Basic Shell Features](https://www.gnu.org/software/bash/manual/bash.html#Basic-Shell-Features)

## [4 Shell Builtin Commands](https://www.gnu.org/software/bash/manual/html_node/Shell-Builtin-Commands.html#Shell-Builtin-Commands)