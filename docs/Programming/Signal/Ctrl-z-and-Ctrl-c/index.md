# askubuntu [What is the difference between Ctrl-z and Ctrl-c in the terminal?](https://askubuntu.com/questions/510811/what-is-the-difference-between-ctrl-z-and-ctrl-c-in-the-terminal)

Can anyone tell me the difference between `ctrl+z` and `ctrl+c`?

When I am in the terminal, both the combinations stop the current process, but what exactly is the difference between both?



## [A](https://askubuntu.com/a/510816)

If we leave edge cases to one side, the difference is simple. `Control+C` aborts the application almost immediately while `Control+Z` shunts(调转) it into the background, suspended.

The shell send different signals to the underlying applications on these combinations:

1、`Control+C` (control character `intr`) sends `SIGINT` which will interrupt the application. Usually causing it to abort(终止), but this is up to the application to decide.

2、`Control+Z` (control character `susp`) sends `SIGTSTP` to a foreground application, effectively putting it in the background, suspended. This is useful if you need to break out of something like an editor to go and grab some data you needed. You can go back into the application by running `fg` (or `%x` where `x` is the job number as shown in `jobs`).

We can test this by running `nano TEST`, then pressing `Control+Z` and then running `ps aux | grep TEST`. This will show us the `nano` process is still running:

```
oli     3278  0.0  0.0  14492  3160 pts/4    T    13:59   0:00 nano TEST
```

Further, we can see (from that T, which is in the status column) that [the process has been stopped](https://askubuntu.com/a/360253/449). So it's still alive, but it's not running... It can be resumed.

Some applications will crash if they have ongoing external processes (like a web request) that might timeout while they're asleep.

## [A](https://askubuntu.com/a/510815)

`Control+Z` suspends a process (`SIGTSTP`) and `Control+C` interrupts a process (`SIGINT`)

<http://en.wikipedia.org/wiki/Control-Z>

> On Unix-like systems, Control+Z is the most common default keyboard mapping for the key sequence that suspends a process

<http://en.wikipedia.org/wiki/Control-C>

> In POSIX systems, the sequence causes the active program to receive a SIGINT signal. If the program does not specify how to handle this condition, it is terminated. Typically a program which does handle a SIGINT will still terminate itself, or at least terminate the task running inside it

