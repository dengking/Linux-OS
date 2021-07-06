# [How to find ports opened by process ID in Linux?](https://stackoverflow.com/questions/942824/how-to-find-ports-opened-by-process-id-in-linux)



[A](https://stackoverflow.com/a/943063)

```sh
netstat --all --program | grep '3265'
```

- `--all` show listening and non-listening sockets.
- `--program` show the PID and name of the program to which socket belongs.

You could also use a port scanner such as Nmap.



[A](https://stackoverflow.com/a/35596973)

You can use the command below:

```sh
lsof -i -P |grep pid
```