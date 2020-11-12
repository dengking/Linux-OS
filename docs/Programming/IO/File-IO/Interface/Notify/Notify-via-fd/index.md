# Notify via file descriptor

Linux中遵循everything is a file，因此，很多event都可以以`fd`(file descriptor)的方式来进行通知。

## `TIMERFD_CREATE(2)`

man: http://man7.org/linux/man-pages/man2/timerfd_create.2.html

## `SIGNALFD(2)`

man: http://man7.org/linux/man-pages/man2/signalfd.2.html

## `EVENTFD(2)` 

man: http://man7.org/linux/man-pages/man2/eventfd.2.html