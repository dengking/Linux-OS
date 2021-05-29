# Process exit status



## wikipedia [Exit status](https://en.wikipedia.org/wiki/Exit_status)

The **exit status** of a [process](https://en.wikipedia.org/wiki/Computer_process) in [computer programming](https://en.wikipedia.org/wiki/Computer_programming) is a small number passed from a [child process](https://en.wikipedia.org/wiki/Child_process) (or callee) to a [parent process](https://en.wikipedia.org/wiki/Parent_process) (or caller) when it has finished executing a specific procedure or delegated task. In [DOS](https://en.wikipedia.org/wiki/DOS), this may be referred to as an **errorlevel**.

> NOTE: parent process如何获取child process的exit status呢？参见下面的[POSIX](#POSIX)这段，其中提及了the [*wait*](https://en.wikipedia.org/wiki/Wait_(operating_system)) system call

When computer programs are executed, the [operating system](https://en.wikipedia.org/wiki/Operating_system) creates an [abstract entity](https://en.wikipedia.org/wiki/Abstract_entity) called a [process](https://en.wikipedia.org/wiki/Computer_process) in which the book-keeping for that program is maintained. In multitasking operating systems such as [Unix](https://en.wikipedia.org/wiki/Unix) or [Linux](https://en.wikipedia.org/wiki/Linux), new processes can be created by active processes. The process that spawns another is called a *parent process*, while those created are *child processes*. Child processes run concurrently with the parent process. The technique of spawning child processes is used to delegate some work to a child process when there is no reason to stop the execution of the parent. When the child finishes executing, it exits by calling the [*exit*](https://en.wikipedia.org/wiki/Exit_(system_call)) [system call](https://en.wikipedia.org/wiki/System_call). This system call facilitates passing the **exit status code** back to the parent, which can retrieve this value using the [*wait*](https://en.wikipedia.org/wiki/Wait_(operating_system)) system call.

### Semantics

The parent and the child can have an understanding about the meaning of the **exit statuses**. For example, it is common programming practice for a child process to return (exit with) zero to the parent signifying success. Apart from this return value from the child, other information like how the process exited, either normally or by a [signal](https://en.wikipedia.org/wiki/Signal_(computing)) may also be available to the parent process.

***SUMMARY*** : other information如何传递到parent process呢？

The specific set of codes returned is unique to the program that sets it. Typically it indicates success or failure. The value of the code returned by the function or program may indicate a specific cause of failure. On many systems, the higher the value, the more severe the cause of the error.[[1\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-1) Alternatively, each bit may indicate a different condition, which are then [evaluated by the *or* operator](https://en.wikipedia.org/wiki/Or_(logic)) together to give the final value; for example, [fsck](https://en.wikipedia.org/wiki/Fsck) does this.

Sometimes, if the codes are designed with this purpose in mind, they can be used directly as a branch index upon return to the initiating program to avoid additional tests.

### Shell and scripts

[Shell scripts](https://en.wikipedia.org/wiki/Shell_script) typically execute commands and capture their **exit statuses**.

For the shell’s purposes, a command which exits with a zero **exit status** has succeeded. A nonzero exit status indicates failure. This seemingly counter-intuitive scheme is used so there is one well-defined way to indicate success and a variety of ways to indicate various failure modes. When a command is terminated by a signal whose number is N, a shell sets the variable $? to a value greater than 128. Most shells use 128+N, while ksh93 uses 256+N.

If a command is not found, the shell should return a status of 127. If a command is found but is not executable, the return status should be 126.[[2\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-2) Note that this is not the case for all shells.

If a command fails because of an error during expansion or redirection, the exit status is greater than zero.

### C language

The [C](https://en.wikipedia.org/wiki/C_(programming_language)) programming language allows programs exiting or returning from the [main function](https://en.wikipedia.org/wiki/Main_function) to signal success or failure by returning an integer, or returning the [macros](https://en.wikipedia.org/wiki/Macro_(computer_science)) `EXIT_SUCCESS` and `EXIT_FAILURE`. On Unix-like systems these are equal to 0 and 1 respectively.[[3\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-glibc-3) A C program may also use the `exit()` function specifying the integer status or exit macro as the first parameter.

The return value from `main` is passed to the `exit` function, which for values zero, `EXIT_SUCCESS` or `EXIT_FAILURE` may translate it to “an implementation defined form” of *successful termination* or *unsuccessful termination*.

Apart from zero and the macros `EXIT_SUCCESS` and `EXIT_FAILURE`, the C standard does not define the meaning of return codes. Rules for the use of return codes vary on different platforms (see the platform-specific sections).

### POSIX

In [Unix](https://en.wikipedia.org/wiki/Unix) and other [POSIX-compatible systems](https://en.wikipedia.org/wiki/POSIX), the **parent process** can retrieve the **exit status** of a child process using the `wait()` family of system calls defined in [wait.h](https://en.wikipedia.org/w/index.php?title=Wait.h&action=edit&redlink=1). [[6\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-6). Of these, the `waitid()` [[7\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-7) call retrieves the full 32-bit exit status, but the older `wait()` and `waitpid()` [[8\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-8) calls retrieve only the least significant 8 bits of the exit status.

The `wait()` and `waitpid()` interfaces set a *status* value of type `int` packed as a [bitfield](https://en.wikipedia.org/wiki/Bitfield) with various types of child termination information. If the child terminated by exiting (as determined by the `WIFEXITED()` macro; the usual alternative being that it died from an uncaught [signal](https://en.wikipedia.org/wiki/Signal_(computing))), [SUS](https://en.wikipedia.org/wiki/Single_UNIX_Specification) specifies that the low-order 8 bits of the exit status can be retrieved from the status value using the `WEXITSTATUS()` macro.

In the `waitid()` system call (added with SUSv1), the child exit status and other information are no longer in a bitfield but in the structure of type `siginfo_t`.[[9\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-9)

POSIX-compatible systems typically use a convention of zero for success and nonzero for error.[[10\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-10) Some conventions have developed as to the relative meanings of various error codes; for example GNU recommend that codes with the high bit set be reserved for serious errors,[[3\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-glibc-3).

BSD-derived OS's have defined an extensive set of preferred interpretations: Meanings for 15 status codes 64 through 78 are defined in [sysexits.h](https://en.wikipedia.org/w/index.php?title=Sysexits.h&action=edit&redlink=1). [[11\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-11) These historically derive from [sendmail](https://en.wikipedia.org/wiki/Sendmail) and other [message transfer agents](https://en.wikipedia.org/wiki/Message_transfer_agent), but they have since found use in many other programs.[[12\]](https://en.wikipedia.org/wiki/Exit_status#cite_note-12)

