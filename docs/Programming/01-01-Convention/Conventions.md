# unix handler and start_rtn

## FORWORD

今天在阅读APUE的chapter 7.3  Process Termination，看其`atexit` Function，通过此函数，我们可以用来注册 ***exit handlers***，这种通过使用函数指针来作为参数的方式在Unix-like的API中非常常见，并且，它们的命名往往也是类似的，比如常常带handler等；所以我决定进行整理；



# [`atexit`](http://man7.org/linux/man-pages/man3/atexit.3.html) and *exit handler*



参见 APUE chapter 7.3  Process Termination



# [`sigaction`](http://man7.org/linux/man-pages/man2/sigaction.2.html) Function and  *signal handler* 



参见APUE 10.14 `sigaction` Function



# [`signal`](http://man7.org/linux/man-pages/man2/signal.2.html) Function and  *signal handler* 



参见APUE 10.3 `signal` Function



# [`pthread_create`](http://man7.org/linux/man-pages/man3/pthread_create.3.html)  and `start_rtn`



参见APUE 11.4 Thread Creation