# gnu libc [13.14 File Descriptor Flags](https://www.gnu.org/software/libc/manual//html_node/Descriptor-Flags.html#Descriptor-Flags)

*File descriptor flags* are miscellaneous(各种各样的) attributes of a **file descriptor**. These flags are associated with particular **file descriptors**, so that if you have created duplicate **file descriptors** from a single opening of a file, each **descriptor** has its own set of flags.

> NOTE: 
>
> 一、"File Descriptor Flag"是"File Descriptor"的attribute
>
> 二、每个open file，都有一个对应的"File Descriptor"

Currently there is just one file descriptor flag: `FD_CLOEXEC`, which causes the descriptor to be closed if you use any of the `exec…` functions (see [Executing a File](https://www.gnu.org/software/libc/manual//html_node/Executing-a-File.html#Executing-a-File)).

The symbols in this section are defined in the header file `fcntl.h`.

## Macro: int `F_GETFD`

This macro is used as the ***command* argument** to `fcntl`, to specify that it should return the **file descriptor flags** associated with the `filedes` argument.

The normal return value from `fcntl` with this command is a nonnegative number which can be interpreted as the bitwise OR of the individual flags (except that currently there is only one flag to use).

> NOTE:
>
> "tag-man 2 fcntl macro-F_GETFD-return the file descriptor flag"

## Macro: int `F_SETFD`

This macro is used as the ***command* argument** to `fcntl`, to specify that it should set the **file descriptor flags** associated with the `filedes` argument. This requires a third `int` argument to specify the new flags, so the form of the call is:

```c
fcntl (filedes, F_SETFD, new-flags)
```

The following macro is defined for use as a **file descriptor flag** with the `fcntl` function. The value is an integer constant usable as a bit mask value.

> "tag-man 2 fcntl macro-F_SETFD-set the file descriptor flag-bitwise mask OR"

## Macro: int `FD_CLOEXEC`

This flag specifies that the **file descriptor** should be closed when an `exec` function is invoked; see [Executing a File](https://www.gnu.org/software/libc/manual//html_node/Executing-a-File.html#Executing-a-File). When a **file descriptor** is allocated (as with `open` or `dup`), this bit is initially cleared on the new file descriptor, meaning that descriptor will survive into the new program after `exec`.

> NOTE: 
>
> 一、当分配 **file descriptor** 时（与`open`或`dup`一样），该位最初在新 **file descriptor** 上被清除，这意味着 **file descriptor** 将在exec之后存活到新程序中。
>
> 二、"tag-new file descriptor-man 2 dup open"



## Example

If you want to modify the **file descriptor flags**, you should get the current flags with `F_GETFD` and modify the value. Don’t assume that the flags listed here are the only ones that are implemented; your program may be run years from now and more flags may exist then. For example, here is a function to set or clear the flag `FD_CLOEXEC` without altering any other flags:

```c
/* Set the FD_CLOEXEC flag of desc if value is nonzero,
   or clear the flag if value is 0.
   Return 0 on success, or -1 on error with errno set. */

int
set_cloexec_flag (int desc, int value)
{
  int oldflags = fcntl (desc, F_GETFD, 0);
  /* If reading the flags failed, return error indication now. */
  if (oldflags < 0)
    return oldflags;
  /* Set just the flag we want to set. */
  if (value != 0)
    oldflags |= FD_CLOEXEC;
  else
    oldflags &= ~FD_CLOEXEC;
  /* Store modified flag word in the descriptor. */
  return fcntl (desc, F_SETFD, oldflags);
}
```

