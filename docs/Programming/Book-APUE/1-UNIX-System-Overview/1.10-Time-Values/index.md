# 1.10 Time Values

UNIX systems have maintained two different time values:

## 一、Calendar time

This value counts the number of seconds since the **Epoch**: 00:00:00 January 1, 1970, Coordinated Universal Time (UTC). (Older manuals refer to UTC as Greenwich Mean Time.) These time values are used to record the time when a fifile was last modifified, for example.

The primitive system data type `time_t` holds these time values.

## 二、Process time、CPU time

> NOTE:
>
> 从后面我们可以看到：CPU time = User CPU time + System CPU time

This is also called **CPU time** and measures the central processor resources used by a process. Process time is measured in clock ticks, which have historically been 50, 60, or 100 ticks per second.

The primitive system data type `clock_t` holds these time values. (We’ll show how to obtain the number of clock ticks per second with the sysconf function in Section 2.5.4.)



When we measure the execution time of a process, as in Section 3.9, we’ll see that the UNIX System maintains three values for a process:

1、Clock time

2、User CPU time(简称为 user)

3、System CPU time(简称为 sys)

The clock time, sometimes called *wall clock time*, is the amount of time the process takes to run, and its value depends on the number of other processes being run on the system. Whenever we report the clock time, the measurements are made with no other activities on the system.



It is easy to measure the **clock time**, **user time**, and **system time** of any process: simply execute the time(1) command, with the argument to the time command being the command we want to measure. For example:

```
$ cd /usr/include

$ time -p grep _POSIX_SOURCE \*/\*.h > /dev/null

real 0m0.81s

user 0m0.11s

sys 0m0.07s
```

