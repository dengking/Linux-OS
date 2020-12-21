# Debug HS middleware

`gdb --args xxx -s 0 start local_mode`

> NOTE: `XXX`是主程序的名称

message-oriented middleware中，runtime dynamical load Shared library，它由start script来启动，如何来对它进行debug？

```shell
gdb --args
set follow-fork-mode child
set stop-on-shard-lib 1
```