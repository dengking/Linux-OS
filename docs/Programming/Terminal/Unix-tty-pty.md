# [tty (unix)](https://en.wikipedia.org/wiki/Tty_(unix))

In [computing](https://en.wikipedia.org/wiki/Computing), **tty** is a command in [Unix](https://en.wikipedia.org/wiki/Unix) and [Unix-like](https://en.wikipedia.org/wiki/Unix-like) [operating systems](https://en.wikipedia.org/wiki/Operating_system) to print the **file name** of the **terminal** connected to [standard input](https://en.wikipedia.org/wiki/Standard_input).[[1\]](https://en.wikipedia.org/wiki/Tty_(unix)#cite_note-1)

tty stands for TeleTYpewriter.[[2\]](https://en.wikipedia.org/wiki/Tty_(unix)#cite_note-2)

## Example

Given below is a sample output when the command is run

```
$ tty
/dev/pts/10
```





# [man 4 tty](http://man7.org/linux/man-pages/man4/tty.4.html)

## NAME

​       tty - controlling terminal

## DESCRIPTION

The file `/dev/tty` is a **character file** with major number 5 and minor number 0, usually
of mode 0666 and owner.group root.tty.  It is a synonym for the **controlling  terminal**
of a process, if any.

In  addition to the `ioctl(2)` requests supported by the device that tty refers to, the
`ioctl(2)` request `TIOCNOTTY` is supported.



### TIOCNOTTY

Detach the calling process from its **controlling terminal**.If the process is the **session leader**, then `SIGHUP` and `SIGCONT` signals are sent to the **foreground process group** and all processes in the current session lose their **controlling tty**.

This `ioctl(2)` call works only on file descriptors connected to `/dev/tty`.  It is  used by  daemon  processes  when  they  are  invoked by a user at a terminal.

This `ioctl(2)` call works only on file descriptors connected to `/dev/tty`.  It is  used by  daemon  processes  when  they  are  invoked by a user at a terminal.  The process attempts to open `/dev/tty`.  If the open succeeds, it detaches itself from the  terminal  by  using  `TIOCNOTTY`, while if the open fails, it is obviously not attached to a terminal and does not need to detach itself.

# [man 1 tty](http://man7.org/linux/man-pages/man1/tty.1.html)

## NAME

​       tty - print the file name of the **terminal** connected to **standard input**

## SYNOPSIS

​       `tty [OPTION]...`

## DESCRIPTION

Print the **file name** of the **terminal** connected to **standard input**.





# man 8 agetty



## NAME

`agetty` - alternative Linux `getty`

## SYNOPSIS

`agetty [options] port [baud_rate...]  [term]`

## DESCRIPTION

`agetty` opens a **tty port**, prompts for a login name and invokes the `/bin/login` command.It is normally invoked by `init(8)`.

`agetty` has several non-standard features that are useful for hard-wired and for dial-in lines:






















# [Difference between pts and tty](https://unix.stackexchange.com/questions/21280/difference-between-pts-and-tty)

> **Possible Duplicate:**
> [What is the exact difference between a 'terminal', a 'shell', a 'tty' and a 'console'?](https://unix.stackexchange.com/questions/4126/what-is-the-exact-difference-between-a-terminal-a-shell-a-tty-and-a-cons)

I always see pts and tty when I use the `who` command but I never understand how they are different? Can somebody please explain me this?

***COMMENTS*** : 

See also [How does a Linux terminal work?](http://unix.stackexchange.com/questions/79334/how-does-a-linux-terminal-work) and [what is stored in /dev/pts files and Can we open those?](http://unix.stackexchange.com/questions/93531/what-is-stored-in-dev-pts-files-and-can-we-open-those) – [Gilles](https://unix.stackexchange.com/users/885/gilles)[Nov 14 '13 at 20:07](https://unix.stackexchange.com/questions/21280/difference-between-pts-and-tty#comment154105_21280)



## [A](https://unix.stackexchange.com/a/21294)

A *tty* is a native terminal device, the backend is either hardware or kernel emulated.

A *pty* (pseudo terminal device) is a terminal device which is emulated by an other program (example: `xterm`, `screen`, or `ssh` are such programs). A *pts* is the slave part of a *pty*.

(More info can be found in `man pty`.)

**Short summary**:

A *pty* is created by a process through `posix_openpt()` (which usually opens the special device `/dev/ptmx`), and is constituted by a pair of bidirectional character devices:

1. The master part, which is the file descriptor obtained by this process through this call, is used to emulate a terminal. After some initialization, the second part can be unlocked with `unlockpt()`, and the master is used to receive or send characters to this second part (slave).
2. The slave part, which is anchored in the filesystem as `/dev/pts/x` (the real name can be obtained by the master through `ptsname()` ) behaves like a native terminal device (`/dev/ttyx`). In most cases, a shell is started that uses it as a controlling terminal.

