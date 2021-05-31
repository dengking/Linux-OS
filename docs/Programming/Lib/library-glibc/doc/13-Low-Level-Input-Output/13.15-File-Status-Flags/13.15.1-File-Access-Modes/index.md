# gnu libc [13.15.1 File Access Modes](https://www.gnu.org/software/libc/manual/html_node/Access-Modes.html#Access-Modes)

The **file access modes** allow a **file descriptor** to be used for reading, writing, or both. (On GNU/Hurd systems, they can also allow none of these, and allow execution of the file as a program.) The **access modes** are chosen when the file is opened, and never change.



## Macro: int `O_RDONLY`

Open the file for read access.



## Macro: int `O_WRONLY`

Open the file for write access.



## Macro: int `O_RDWR`

Open the file for both reading and writing.



On GNU/Hurd systems (and not on other systems), `O_RDONLY` and `O_WRONLY` are independent bits that can be bitwise-ORed together, and it is valid for either bit to be set or clear. This means that `O_RDWR` is the same as `O_RDONLY|O_WRONLY`. A **file access mode** of zero is permissible; it allows no operations that do input or output to the file, but does allow other operations such as `fchmod`. On GNU/Hurd systems, since “read-only” or “write-only” is a misnomer(用词不当), `fcntl.h` defines additional names for the **file access modes**. These names are preferred when writing GNU-specific code. But most programs will want to be portable to other POSIX.1 systems and should use the POSIX.1 names above instead.



## Macro: int `O_READ`

Open the file for reading. Same as `O_RDONLY`; only defined on GNU.



## Macro: int `O_WRITE`

Open the file for writing. Same as `O_WRONLY`; only defined on GNU.



## Macro: int `O_EXEC`

Open the file for executing. Only defined on GNU.





To determine the **file access mode** with `fcntl`, you must extract the access mode bits from the retrieved file status flags. On GNU/Hurd systems, you can just test the `O_READ` and `O_WRITE` bits in the flags word. But in other POSIX.1 systems, reading and writing access modes are not stored as distinct bit flags. The portable way to extract the file access mode bits is with `O_ACCMODE`.



## Macro: int `O_ACCMODE`

This macro stands for a mask that can be bitwise-ANDed with the file status flag value to produce a value representing the file access mode. The mode will be `O_RDONLY`, `O_WRONLY`, or `O_RDWR`. (On GNU/Hurd systems it could also be zero, and it never includes the `O_EXEC` bit.)