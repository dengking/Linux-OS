# wikipedia [Capability-based security](https://en.wikipedia.org/wiki/Capability-based_security)

**Capability-based security** is a concept in the design of [secure computing](https://en.wikipedia.org/wiki/Computer_security) systems, one of the existing [security models](https://en.wikipedia.org/wiki/Computer_security_model). A **capability** (known in some systems as a **key**) is a communicable(可传达的), unforgeable(不可篡改的) [token](https://en.wikipedia.org/wiki/Access_token) of authority. It refers to a value that [references](https://en.wikipedia.org/wiki/Reference_(computer_science)) an [object](https://en.wikipedia.org/wiki/Object_(computer_science)) along with an associated set of [access rights](https://en.wikipedia.org/wiki/Access_control).

> NOTE: 
>
> 1、显然Linux OS file descriptor是典型的capability-based security。

## Introduction

Capabilities achieve their objective of improving system security by being used in place of forgeable [references](https://en.wikipedia.org/wiki/Reference_(computer_science)). A forgeable reference (for example, a [path name](https://en.wikipedia.org/wiki/Path_(computing))) identifies an object, but does not specify which access rights are appropriate for that object and the user program which holds that reference. Consequently, any attempt to access the referenced object must be validated by the operating system, based on the [ambient authority](https://en.wikipedia.org/wiki/Ambient_authority) of the requesting program, typically via the use of an [access control list](https://en.wikipedia.org/wiki/Access_control_list) (ACL). 

Instead, in a system with capabilities, the mere fact that a user program possesses(拥有) that capability entitles(使有资格，使有权) it to use the referenced object **in accordance with**(按照) the rights that are specified by that capability. In theory, a system with capabilities removes the need for any **access control list** or similar mechanism by giving all entities(实体) all and only the capabilities they will actually need.

> NOTE: 翻译如下:
>
> "功能通过替代可伪造的引用来实现提高系统安全性的目标。可伪造的引用(例如，路径名)标识一个对象，但不指定哪些访问权限适合该对象和持有该引用的用户程序。因此，任何访问被引用对象的尝试都必须由操作系统验证，基于请求程序的环境权限，通常通过使用访问控制列表(ACL)。
>
> 相反，在一个具有功能的系统中，用户程序拥有该功能这一事实使它有权根据该功能指定的权利来使用所引用的对象。从理论上讲，具有功能的系统通过给予所有实体所有且仅提供它们实际需要的功能，从而消除了对任何访问控制列表或类似机制的需求。"
>
> 总的来说，使用"Capability-based security"可以替代ACL。

### Implementation

A capability is typically implemented as a [privileged](https://en.wikipedia.org/wiki/Privilege_(computer_science)) [data structure](https://en.wikipedia.org/wiki/Data_structure) that consists of a section that specifies **access rights**, and a section that uniquely identifies the object to be accessed. The user does not access the data structure or object directly, but instead via a [handle](https://en.wikipedia.org/wiki/Handle_(computing)). In practice, it is used much like a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor) in a traditional operating system (a traditional handle), but to access every object on the system. Capabilities are typically stored by the operating system in a list, with some mechanism in place to prevent the program from directly modifying the contents of the capability (so as to forge(篡改) access rights or change the object it points to). Some systems have also been based on [capability-based addressing](https://en.wikipedia.org/wiki/Capability-based_addressing) (hardware support for capabilities), such as [Plessey System 250](https://en.wikipedia.org/wiki/Plessey_System_250).

### Use capability

Programs possessing capabilities can perform functions on them, such as passing them on to other programs, converting them to a less-privileged version, or deleting them. The operating system must ensure that only specific operations can occur to the capabilities in the system, in order to maintain the integrity of the security policy.

## Examples

### File descriptor

> NOTE: File descriptor is a capacity.

Now suppose that the user program successfully executes the following statement:

```c
int fd = open("/etc/passwd", O_RDWR);
```

The variable `fd` now contains the index of a file descriptor in the **process's file descriptor table**. This file descriptor *is* a capability. Its existence in the process's file descriptor table is sufficient to know that the process does indeed have legitimate(合法的) access to the object. A key feature of this arrangement is that the file descriptor table is in [kernel memory](https://en.wikipedia.org/wiki/Kernel_(computer_science)) and cannot be directly manipulated by the user program.

## POSIX capabilities

POSIX draft 1003.1e specifies a concept of permissions(权限) called "capabilities". However, POSIX capabilities differ from capabilities in this article—POSIX capability is not associated with any object; a process having `CAP_NET_BIND_SERVICE` capability can listen on any TCP port under 1024. This system is found in Linux.[[1\]](https://en.wikipedia.org/wiki/Capability-based_security#cite_note-1)

> NOTE: POSIX capabilities本质上是permission，而不是本文的capacity。

## Implementations

> NOTE: 未读