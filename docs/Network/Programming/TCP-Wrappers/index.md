# TCP Wrappers

## wikipedia [TCP Wrappers](https://en.wikipedia.org/wiki/TCP_Wrappers)

**TCP Wrappers** (also known as **tcp_wrappers**) is a host-based networking [ACL](https://en.wikipedia.org/wiki/Access_control_list) system, used to [filter](https://en.wikipedia.org/wiki/Filter_(software)) network access to [Internet Protocol](https://en.wikipedia.org/wiki/Internet_protocol_suite) servers on ([Unix-like](https://en.wikipedia.org/wiki/Unix-like)) [operating systems](https://en.wikipedia.org/wiki/Operating_system) such as [Linux](https://en.wikipedia.org/wiki/Linux) or [BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution). It allows host or [subnetwork](https://en.wikipedia.org/wiki/Subnetwork) [IP addresses](https://en.wikipedia.org/wiki/IP_address), [names](https://en.wikipedia.org/wiki/Hostname) and/or [ident](https://en.wikipedia.org/wiki/Ident_protocol) query replies, to be used as tokens on which to filter for [access control](https://en.wikipedia.org/wiki/Access_control) purposes.



The [tarball](https://en.wikipedia.org/wiki/Tar_(file_format)) includes a [library](https://en.wikipedia.org/wiki/Library_(computer_science)) named **libwrap** that implements the actual functionality. Initially, only services that were spawned for each connection from a [super-server](https://en.wikipedia.org/wiki/Super-server) (such as [inetd](https://en.wikipedia.org/wiki/Inetd)) got *wrapped*, utilizing the **tcpd** program. However most common network service [daemons](https://en.wikipedia.org/wiki/Daemon_(computer_software)) today can be [linked](https://en.wikipedia.org/wiki/Linker_(computing)) against libwrap directly. This is used by daemons that operate without being spawned from a **super-server**, or when a single process handles multiple connections. Otherwise, only the first connection attempt would get checked against its ACLs.

> NOTE: tarball包含一个名为libwrap的库，它实现了实际的功能。最初，只有使用tcpd程序将来自超级服务器（例如inetd）的每个连接生成的服务包装起来。但是，今天最常见的网络服务守护进程可以直接链接到libwrap。守护进程使用它而不是从超级服务器生成，或者当单个进程处理多个连接时运行。否则，将仅针对其ACL检查第一次连接尝试。

When compared to host access control directives often found in daemons' configuration files, TCP Wrappers have the benefit of [runtime](https://en.wikipedia.org/wiki/Run_time_(program_lifecycle_phase)) ACL reconfiguration (i.e., services don't have to be reloaded or restarted) and a generic approach to network administration.

