# gnu libc [13.15 File Status Flags](https://www.gnu.org/software/libc/manual/html_node/File-Status-Flags.html)

*File status flags* are used to specify attributes of the opening of a file. Unlike the **file descriptor flags** discussed in [Descriptor Flags](https://www.gnu.org/software/libc/manual/html_node/Descriptor-Flags.html#Descriptor-Flags), the **file status flags** are shared by duplicated **file descriptors** resulting from a single opening of the file. The **file status flags** are specified with the flags argument to `open`; see [Opening and Closing Files](https://www.gnu.org/software/libc/manual/html_node/Opening-and-Closing-Files.html#Opening-and-Closing-Files).

> NOTE: 
>
> 一、只有通过 `open`，才能够得到一个file descriptor；

**File status flags** fall into three categories, which are described in the following sections.

1、[Access Modes](https://www.gnu.org/software/libc/manual/html_node/Access-Modes.html#Access-Modes), specify what type of access is allowed to the file: reading, writing, or both. They are set by `open` and are returned by `fcntl`, but cannot be changed.

2、[Open-time Flags](https://www.gnu.org/software/libc/manual/html_node/Open_002dtime-Flags.html#Open_002dtime-Flags), control details of what `open` will do. These flags are not preserved after the `open` call.

3、[Operating Modes](https://www.gnu.org/software/libc/manual/html_node/Operating-Modes.html#Operating-Modes), affect how operations such as `read` and `write` are done. They are set by `open`, and can be fetched or changed with `fcntl`.

The symbols in this section are defined in the header file `fcntl.h`.

|                                                              |      |                                           |
| ------------------------------------------------------------ | ---- | ----------------------------------------- |
| • [Access Modes](https://www.gnu.org/software/libc/manual/html_node/Access-Modes.html#Access-Modes): |      | Whether the descriptor can read or write. |
| • [Open-time Flags](https://www.gnu.org/software/libc/manual/html_node/Open_002dtime-Flags.html#Open_002dtime-Flags): |      | Details of `open`.                        |
| • [Operating Modes](https://www.gnu.org/software/libc/manual/html_node/Operating-Modes.html#Operating-Modes): |      | Special modes to control I/O operations.  |
| • [Getting File Status Flags](https://www.gnu.org/software/libc/manual/html_node/Getting-File-Status-Flags.html#Getting-File-Status-Flags): |      | Fetching and changing these flags.        |