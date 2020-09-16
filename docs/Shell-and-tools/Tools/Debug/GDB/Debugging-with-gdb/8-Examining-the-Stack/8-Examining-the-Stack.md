# [8 Examining the Stack](https://sourceware.org/gdb/current/onlinedocs/gdb/Stack.html#Stack)

When your program has stopped, the first thing you need to know is where it stopped and how it got there.

Each time your program performs a function call, information about the call is generated. That information includes the location of the call in your program, the arguments of the call, and the local variables of the function being called. The information is saved in a block of data called a ***stack frame***. The stack frames are allocated in a region of memory called the ***call stack***.

One of the stack frames is selected by gdb and many gdb commands refer implicitly to the selected frame. In particular, whenever you ask gdb for the value of a variable in your program, the value is found in the selected frame. There are special gdb commands to select whichever frame you are interested in. See Section 8.3 [Selecting a Frame], page 98.

> NOTE: 尤其是在debug一个already running process的时候，必须先select一个frame，然后才能够查看其中的variable。

## 8.1 Stack Frames

The call stack is divided up into contiguous pieces called stack frames, or frames for short; each frame is the data associated with one call to one function. The frame contains the arguments given to the function, the function’s local variables, and the address at which the function is executing.

## 8.2 Backtraces

A backtrace is a summary of how your program got where it is. It shows one line per frame, for many frames, starting with the currently executing frame (frame zero), followed by its caller (frame one), and on up the stack.

### `backtrace` / `bt`



## 8.3 Selecting a Frame

Most commands for examining the stack and other data in your program work on whichever stack frame is selected at the moment. Here are the commands for selecting a stack frame; all of them finish by printing a brief description of the stack frame just selected.

### `frame n`



### `up n`



### `down n`



## 8.4 Information About a Frame

There are several other commands to print information about the selected stack frame.

### `frame`z



### `info frame`



## [8.5 Applying a Command to Several Frames.](https://sourceware.org/gdb/current/onlinedocs/gdb/Frame-Apply.html#Frame-Apply)

### `frame apply`



## 8.6 Management of Frame Filters.

