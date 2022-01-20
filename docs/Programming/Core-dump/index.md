# Core dump

## 开启core dump

如何开启core dump，设置core dump文件的位置、名称格式？

目前我参考了如下内容:

1、stackexchange [How to set the core dump file location (and name)?](https://unix.stackexchange.com/questions/192716/how-to-set-the-core-dump-file-location-and-name) # [A](https://unix.stackexchange.com/a/192836)

2、csdn [linux下的core文件路径及文件名设置](https://blog.csdn.net/qq_15437667/article/details/83934113)

下面是可行的: 

```shell
ulimit -c unlimited
echo "./%e.%s.core" > /proc/sys/kernel/core_pattern
```



### stackexchange [How to set the core dump file location (and name)?](https://unix.stackexchange.com/questions/192716/how-to-set-the-core-dump-file-location-and-name)



### TODO

stackoverflow [Changing location of core dump](https://stackoverflow.com/questions/16048101/changing-location-of-core-dump)



### Ubuntu

askubuntu [Where do I find the core dump in ubuntu 16.04LTS?](https://askubuntu.com/questions/966407/where-do-i-find-the-core-dump-in-ubuntu-16-04lts)

stackoverflow [Core dumped, but core file is not in the current directory?](https://stackoverflow.com/questions/2065912/core-dumped-but-core-file-is-not-in-the-current-directory)

## wikipedia [Core dump](https://en.wikipedia.org/wiki/Core_dump)



## stackoverflow [Why are core dump files generated?](https://stackoverflow.com/questions/775872/why-are-core-dump-files-generated)