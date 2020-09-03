# wikipedia [Time of check to time of use](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use)

In [software development](https://en.wikipedia.org/wiki/Software_development), **time of check to time of use** (**TOCTOU**, **TOCTTOU** or **TOC/TOU)** is a class of [software bugs](https://en.wikipedia.org/wiki/Software_bug) caused by **changes** in a system between the *checking* of a condition (such as a security credential) and the *use* of the results of that check. This is one example of a [race condition](https://en.wikipedia.org/wiki/Race_condition).

***SUMMARY*** : 由发生在checking of condition和use the result of the check之间的change而导致的

A simple example is as follows: Consider a Web application that allows a user to edit pages, and also allows administrators to lock pages to prevent editing. A user requests to edit a page, getting a form which can be used to alter its content. Before the user submits the form, an administrator locks the page, which should prevent editing. However, since editing has already begun, when the user submits the form, those edits (which have already been made) are accepted. When the user began editing, the appropriate authorization was *checked*, and the user was indeed allowed to edit. However, the authorization was *used* later, at a time when edits should no longer have been allowed.

***翻译*** ： 一个简单的示例如下：考虑允许用户编辑页面的Web应用程序，还允许管理员锁定页面以防止编辑。 用户请求编辑页面，获取可用于更改其内容的表单。 在用户提交表单之前，管理员会锁定页面，这会阻止编辑。 但是，由于编辑已经开始，当用户提交表单时，将接受这些编辑（已经进行了编辑）。 当用户开始编辑时，检查了相应的授权，确实允许用户编辑。 但是，在不再允许编辑的情况下，稍后会使用授权。

TOCTOU race conditions are common in [Unix](https://en.wikipedia.org/wiki/Unix) between operations on the [file system](https://en.wikipedia.org/wiki/File_system#Metadata),[[1\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-1) but can occur in other contexts, including local [sockets](https://en.wikipedia.org/wiki/Unix_domain_socket) and improper use of [database transactions](https://en.wikipedia.org/wiki/Database_transaction). In the early 1990s, the mail utility of BSD 4.3 UNIX had an [exploitable](https://en.wikipedia.org/wiki/Exploit_(computer_security)) race condition for temporary files because it used the [mktemp() C library function](https://en.wikipedia.org/wiki/C_standard_library#Threading_problems,_vulnerability_to_race_conditions).[[2\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-2) Early versions of [OpenSSH](https://en.wikipedia.org/wiki/OpenSSH) had an exploitable race condition for [Unix domain sockets](https://en.wikipedia.org/wiki/Unix_domain_sockets).[[3\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-3)





## Examples

In [Unix](https://en.wikipedia.org/wiki/Unix), the following [C](https://en.wikipedia.org/wiki/C_(programming_language)) code, when used in a `setuid` program, has a TOCTOU bug:

```python
if (access("file", W_OK) != 0) {
   exit(1);
}

fd = open("file", O_WRONLY);
write(fd, buffer, sizeof(buffer));
```

Here, *access* is intended to check whether the **real user** who executed the `setuid` program would normally be allowed to write the file (i.e., `access` checks the [real userid](https://en.wikipedia.org/wiki/Real_userid) rather than [effective userid](https://en.wikipedia.org/wiki/Effective_userid)).



This [race condition](https://en.wikipedia.org/wiki/Race_condition) is vulnerable to an attack:

| Victim                                                       | Attacker                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `if (access("file", W_OK) != 0) {    exit(1); }  fd = open("file", O_WRONLY); // Actually writing over /etc/passwd write(fd, buffer, sizeof(buffer)); ` | `//  // // After the access check symlink("/etc/passwd", "file"); // Before the open, "file" points to the password database // //` |

In this example, an attacker can exploit the [race condition](https://en.wikipedia.org/wiki/Race_condition) between the `access` and `open` to trick the `setuid` victim into overwriting an entry in the system password database. TOCTOU races can be used for [privilege escalation](https://en.wikipedia.org/wiki/Privilege_escalation), to get administrative access to a machine.

Although this sequence of events requires precise timing, it is possible for an attacker to arrange such conditions without too much difficulty.

The implication is that applications cannot assume the state managed by the operating system (in this case the file system namespace) will not change between system calls.



## Reliably timing TOCTOU

Exploiting a TOCTOU race condition requires precise timing to ensure that the attacker's operations interleave properly with the victim's. In the example above, the attacker must execute the `symlink` system call precisely between the `access` and `open`. For the most general attack, the attacker must be scheduled for execution after each operation by the victim, also known as "single-stepping" the victim.

In the case of BSD 4.3 mail utility and mktemp(),[[4\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-4) the attacker can simply keep launching mail utility in one process, and keep guessing the temporary file names and keep making symlinks in another process. The attack can usually succeed in less than one minute.

Techniques for single-stepping a victim program include file system mazes[[5\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-5) and algorithmic complexity attacks.[[6\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-6) In both cases, the attacker manipulates the OS state to control scheduling of the victim.

File system mazes force the victim to read a directory entry that is not in the OS cache, and the OS puts the victim to sleep while it is reading the directory from disk. Algorithmic complexity attacks force the victim to spend its entire scheduling quantum inside a single system call traversing the kernel's hash table of cached file names. The attacker creates a very large number of files with names that hash to the same value as the file the victim will look up.



## Preventing TOCTOU

Despite conceptual simplicity, TOCTOU race conditions are difficult to avoid and eliminate. One general technique is to use [exception handling](https://en.wikipedia.org/wiki/Exception_handling) instead of checking, under the philosophy of **EAFP** "It is easier to ask for forgiveness than permission" rather than **LBYL** "look before you leap" – in this case there is no check, and failure of assumptions to hold are detected at use time, by an exception.[[7\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-7)

In the context of file system TOCTOU race conditions, the fundamental challenge is ensuring that the file system cannot be changed between two system calls. In 2004, an impossibility result was published, showing that there was no portable, deterministic technique for avoiding TOCTOU race conditions.[[8\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-8)

Since this impossibility result, libraries for tracking [file descriptors](https://en.wikipedia.org/wiki/File_descriptor) and ensuring correctness have been proposed by researchers.[[9\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-9)

An alternative solution proposed in the research community is for UNIX systems to adopt transactions in the file system or the OS kernel. Transactions provide a [concurrency control](https://en.wikipedia.org/wiki/Concurrency_control) abstraction for the OS, and can be used to prevent TOCTOU races. While no production UNIX kernel has yet adopted transactions, proof-of-concept research prototypes have been developed for Linux, including the Valor file system[[10\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-10) and the TxOS kernel.[[11\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-11) [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) has added transactions to its [NTFS](https://en.wikipedia.org/wiki/NTFS)file system,[[12\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-12) but Microsoft discourages their use, and has indicated that they may be removed in a future version of Windows.[[13\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-13)

[File locking](https://en.wikipedia.org/wiki/File_locking) is a common technique for preventing race conditions for a single file, but it does not extend to the file system namespace and other metadata, nor does locking work well with networked filesystems, and cannot prevent TOCTOU race conditions.

For setuid binaries a possible solution is to use the `seteuid()` system call to change the effective user and then perform the `open()`. Differences in `setuid()` between operating systems can be problematic.[[14\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-14)



## Preventing TOCTOU

Despite conceptual simplicity, TOCTOU race conditions are difficult to avoid and eliminate. One general technique is to use [exception handling](https://en.wikipedia.org/wiki/Exception_handling) instead of checking, under the philosophy of **EAFP** "It is easier to ask for forgiveness than permission" rather than **LBYL** "look before you leap" – in this case there is no check, and failure of assumptions to hold are detected at use time, by an exception.[[7\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-7)

In the context of file system TOCTOU race conditions, the fundamental challenge is ensuring that the file system cannot be changed between two system calls. In 2004, an impossibility result was published, showing that there was no portable, deterministic technique for avoiding TOCTOU race conditions.[[8\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-8)

Since this impossibility result, libraries for tracking [file descriptors](https://en.wikipedia.org/wiki/File_descriptor) and ensuring correctness have been proposed by researchers.[[9\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-9)

An alternative solution proposed in the research community is for UNIX systems to adopt transactions in the file system or the OS kernel. Transactions provide a [concurrency control](https://en.wikipedia.org/wiki/Concurrency_control) abstraction for the OS, and can be used to prevent TOCTOU races. While no production UNIX kernel has yet adopted transactions, proof-of-concept research prototypes have been developed for Linux, including the Valor file system[[10\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-10) and the TxOS kernel.[[11\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-11) [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) has added transactions to its [NTFS](https://en.wikipedia.org/wiki/NTFS)file system,[[12\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-12) but Microsoft discourages their use, and has indicated that they may be removed in a future version of Windows.[[13\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-13)

[File locking](https://en.wikipedia.org/wiki/File_locking) is a common technique for preventing race conditions for a single file, but it does not extend to the file system namespace and other metadata, nor does locking work well with networked filesystems, and cannot prevent TOCTOU race conditions.

For setuid binaries a possible solution is to use the `seteuid()` system call to change the effective user and then perform the `open()`. Differences in `setuid()` between operating systems can be problematic.[[14\]](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use#cite_note-14)

## See also

- [Linearizability](https://en.wikipedia.org/wiki/Linearizability)

