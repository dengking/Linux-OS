# 关于本章

本章描述Linux OS提供的OS相关的command。



## [What is the difference between ps and top command?](https://unix.stackexchange.com/questions/62176/what-is-the-difference-between-ps-and-top-command)



### [A](https://unix.stackexchange.com/a/62186)

`top` is mostly used interactively (try reading man page or pressing "h" while `top` is running) and `ps` is designed for non-interactive use (scripts, extracting some information with shell pipelines etc.)



### [A](https://unix.stackexchange.com/a/62190)

`top` allows you display of process statistics continuously until stopped vs. `ps` which gives you a single snapshot.



### [A](https://unix.stackexchange.com/a/497650)

For CPU usage, `ps` displays average CPU usage over the lifetime of the process as it is instantaneous and would always be 0% or 100%. `top` gives a more instantaneous look at it from averaging over recent polls.

More information here: [Top and ps not showing the same cpu result](https://unix.stackexchange.com/questions/58539/top-and-ps-not-showing-the-same-cpu-result)