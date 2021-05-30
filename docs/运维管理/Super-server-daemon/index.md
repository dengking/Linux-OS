# Super server daemon



## wikipedia [Super-server](https://en.wikipedia.org/wiki/Super-server)

A **super-server** or sometimes called a **service dispatcher** is a type of [daemon](https://en.wikipedia.org/wiki/Daemon_(computer_software)) run generally on [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems.

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9c/Super-server.png/420px-Super-server.png)



Principle of Super-server

### Usage

A super-server starts other [servers](https://en.wikipedia.org/wiki/Server_(computing)) when needed, normally with access to them checked by a [TCP wrapper](https://en.wikipedia.org/wiki/TCP_Wrapper). It uses very few resources when in idle state. This can be ideal for [workstations](https://en.wikipedia.org/wiki/Workstations) used for local [web development](https://en.wikipedia.org/wiki/Web_development), client/server development[*citation needed*] or low-traffic daemons with occasional usage (such as [ident](https://en.wikipedia.org/wiki/Ident_protocol) and [SSH](https://en.wikipedia.org/wiki/Secure_Shell)).

> NOTE: 超级服务器在需要时启动其他服务器，通常可以通过TCP包装器检查它们。 它处于空闲状态时使用的资源非常少。 这对于用于本地Web开发，客户端/服务器开发[需要引用]或偶尔使用的低流量守护进程（例如ident和SSH）的工作站来说是理想的。	

### Performance

There is a slight delay in connecting to the sub-daemons. Thus, when compared to standalone servers, a super-server setup may perform worse, especially when under high load. Some servers, such as hpa-tftpd, therefore take over the [internet socket](https://en.wikipedia.org/wiki/Internet_socket) and listen on it themselves for some specified interval, anticipating more connections to come.

## Implementations

- [inetd](https://en.wikipedia.org/wiki/Inetd)
- [launchd](https://en.wikipedia.org/wiki/Launchd)
- [systemd](https://en.wikipedia.org/wiki/Systemd)
- [ucspi-tcp](https://en.wikipedia.org/wiki/Ucspi-tcp)
- [xinetd](https://en.wikipedia.org/wiki/Xinetd)


