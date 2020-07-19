# 4 Running Programs Under gdb

## 4.1 Compiling for Debugging



`gcc`, the gnu C/C++ compiler, supports ‘`-g`’ with or without ‘`-O`’, making it possible to debug optimized code. We recommend that you always use ‘`-g`’ whenever you compile a program. You may think your program is correct, but there is no sense in pushing your luck. For more information, see Chapter 11 [Optimized Code], page 159.





`gdb` knows about preprocessor macros and can show you their expansion (see Chapter 12 [Macros], page 163). Most compilers do not include information about preprocessor macros in the debugging information if you specify the ‘`-g`’ flag alone. Version 3.1 and later of `gcc`, the gnu C compiler, provides macro information if you are using the `DWARF` debugging format, and specify the option ‘`-g3`’.

> NOTE: 上面这段话的意思是：在编译期的option中添加上`-g3  -DWARF`就可以包含macro的调试信息，比如：
>
> ```
> gcc -g3  -DWARF
> ```

See Section “Options for Debugging Your Program or GCC” in Using the gnu Compiler Collection (GCC), for more information on `gcc` options affecting debug information.

You will have the best debugging experience if you use the latest version of the `DWARF` debugging format that your compiler supports. `DWARF` is currently the most expressive and best supported debugging format in `gdb`.

>  NOTE: 关于`DWARF` 是一种debugging format。

## 4.2 Starting your Program

### `run`

`r`

## 4.3 Your Program’s Arguments



## 4.7 Debugging an Already-running Process

### `attach process-id`



### `detach`



## 4.9 Debugging Multiple Inferiors and Programs

`gdb` lets you run and debug multiple programs in a single session. In addition, `gdb` on some systems may let you run several programs simultaneously (otherwise you have to exit from one before starting another). In the most general case, you can have multiple threads of execution in each of multiple processes, launched from multiple executables.

### inferior

`gdb` represents the state of each program execution with an object called an **inferior**. An inferior typically corresponds to a **process**, but is more general and applies also to targets that do not have processes. **Inferiors** may be created before a process runs, and may be retained after a process exits. **Inferiors** have unique identifiers that are different from process ids. 

### `info inferiors`

`info inferiors`

Print a list of all inferiors currently being managed by gdb.

To switch focus between inferiors, use the `inferior` command:

### `inferior infno`

`inferior infno`



The debugger convenience variable ‘`$_inferior`’ contains the number of the current inferior. You may find this useful in writing **breakpoint conditional expressions**, **command scripts**, and so forth. See Section 10.11 [Convenience Variables], page 139, for general information on convenience variables.



### `add-inferior` and `clone-inferior`

You can get multiple executables into a debugging session via the `add-inferior` and `clone-inferior` commands. On some systems `gdb` can add inferiors to the debug session automatically by following calls to `fork` and `exec`. To remove inferiors from the debugging session use the remove-inferiors command.



## 4.11 Debugging Forks

On most systems, `gdb` has no special support for debugging programs which create additional processes using the fork function. When a program forks, `gdb` will continue to debug the parent process and the child process will run unimpeded（未受阻的）. If you have set a breakpoint in any code which the child then executes, the child will get a `SIGTRAP` signal which (unless it catches the signal) will cause it to terminate.

> NOTE: 默认是调试parent process，即默认情况下，gdb是`attach` parent process的。那如何让`gdb` attach到child process呢？下面对此进行了介绍：

However, if you want to debug the child process there is a workaround which isn’t too painful. Put a call to `sleep` in the code which the child process executes after the fork. It may be useful to sleep only if a certain environment variable is set, or a certain file exists, so that the delay need not occur when you don’t want to run `gdb` on the child. While the child is sleeping, use the `ps` program to get its **process ID**. Then tell `gdb` (a new invocation of `gdb` if you are also debugging the parent process) to **attach** to the **child process** (see
Section 4.7 [Attach], page 32). From that point on you can debug the child process just like any other process which you attached to.

On some systems, `gdb` provides support for debugging programs that create additional processes using the `fork` or `vfork` functions. On gnu/Linux platforms, this feature is supported with kernel version 2.5.46 and later.

By default, when a program forks, `gdb` will continue to debug the parent process and the child process will run unimpeded.

### `set follow-fork-mode`

If you want to follow the **child process** instead of the **parent process**, use the command `set follow-fork-mode`

`set follow-fork-mode mode`

- `parent`
- `child`

`show follow-fork-mode`

### `set detach-on-fork`

On Linux, if you want to debug both the parent and child processes, use the command `set detach-on-fork`.

`set detach-on-fork mode`

- `on`
- `off`

`show detach-on-fork`



