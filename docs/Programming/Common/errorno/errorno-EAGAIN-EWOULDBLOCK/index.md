# `EAGAIN` and `EWOULDBLOCK`



## stackoverflow [What does EAGAIN mean?](https://stackoverflow.com/questions/4058368/what-does-eagain-mean)



### [A](https://stackoverflow.com/a/4058377)

[EAGAIN](https://web.archive.org/web/20130508062559/http://www.wlug.org.nz/EAGAIN) is often raised when performing [non-blocking I/O](http://www.kegel.com/dkftpbench/nonblocking.html). It means *"there is no data available right now, try again later"*.

It [might](http://www.opengroup.org/onlinepubs/000095399/basedefs/errno.h.html) (or [might not](http://mail-archives.apache.org/mod_mbox/httpd-dev/200004.mbox/)) be the same as `EWOULDBLOCK`, which means *"your thread would have to block in order to do that"*.



## [errno(3)](https://www.man7.org/linux/man-pages/man3/errno.3.html)
