# Troubleshoot CPU bound bottleneck



## stackexchange [How to find which Process is causing High CPU usage](https://unix.stackexchange.com/questions/20483/how-to-find-which-process-is-causing-high-cpu-usage)

[A](https://unix.stackexchange.com/a/20484)

`top` will display what is using your CPU. If you have it installed, `htop` allows you more fine-grained control, including filtering by—in your case—CPU

[A](https://unix.stackexchange.com/a/22244)

```
ps -eo pcpu,pid,user,args | sort -k1 -r -n | head -10
```

Works for me, show the top 10 cpu using threads, sorted numerically