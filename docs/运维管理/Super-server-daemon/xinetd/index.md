# `xinetd`



## wikipedia [xinetd](https://en.wikipedia.org/wiki/Xinetd)

In [computer networking](https://en.wikipedia.org/wiki/Computer_networking), **xinetd** (*Extended Internet Service Daemon*) is an [open-source](https://en.wikipedia.org/wiki/Open-source_software) [super-server](https://en.wikipedia.org/wiki/Super-server) [daemon](https://en.wikipedia.org/wiki/Daemon_(computer_software)),[[3\]](https://en.wikipedia.org/wiki/Xinetd#cite_note-3) runs on many [Unix-like](https://en.wikipedia.org/wiki/Unix-like) [systems](https://en.wikipedia.org/wiki/Operating_system) and manages [Internet](https://en.wikipedia.org/wiki/Internet)-based connectivity.

It offers a more secure alternative to the older [inetd](https://en.wikipedia.org/wiki/Inetd) ("the Internet daemon"), which most modern [Linux distributions](https://en.wikipedia.org/wiki/Linux_distribution) have deprecated.[[4\]](https://en.wikipedia.org/wiki/Xinetd#cite_note-4)



### Description

xinetd listens for incoming requests over a network and launches the appropriate [service](https://en.wikipedia.org/wiki/Network_service) for that request.[[5\]](https://en.wikipedia.org/wiki/Xinetd#cite_note-5) Requests are made using [port numbers](https://en.wikipedia.org/wiki/Port_numbers) as identifiers and xinetd usually launches another [daemon](https://en.wikipedia.org/wiki/Daemon_(computing)) to handle the request. It can be used to start services with both privileged and non-privileged port numbers.

xinetd features [access control](https://en.wikipedia.org/wiki/Access_control) mechanisms such as [TCP Wrapper](https://en.wikipedia.org/wiki/TCP_Wrapper) [ACLs](https://en.wikipedia.org/wiki/Access_control_list), extensive [logging](https://en.wikipedia.org/wiki/Data_logging) capabilities, and the ability to make [services](https://en.wikipedia.org/wiki/Service_(systems_architecture)) available based on time. It can place limits on the number of [servers](https://en.wikipedia.org/wiki/Server_(computing)) that the system can start, and has deployable defense mechanisms to protect against [port scanners](https://en.wikipedia.org/wiki/Port_scanner), among other things.

On some implementations of [Mac OS X](https://en.wikipedia.org/wiki/Mac_OS_X), this daemon starts and maintains various Internet-related services, including [FTP](https://en.wikipedia.org/wiki/File_Transfer_Protocol) and [telnet](https://en.wikipedia.org/wiki/Telnet). As an extended form of inetd, it offers enhanced security. It replaced inetd in [Mac OS X v10.3](https://en.wikipedia.org/wiki/Mac_OS_X_v10.3), and subsequently [launchd](https://en.wikipedia.org/wiki/Launchd) replaced it in [Mac OS X v10.4](https://en.wikipedia.org/wiki/Mac_OS_X_v10.4). However, [Apple](https://en.wikipedia.org/wiki/Apple_Computer) has retained inetd for compatibility purposes.



### Configuration

Configuration of xinetd resides in the default configuration file `/etc/xinetd.conf` and configuration of the services it supports reside in configuration files stored in the `/etc/xinetd.d` directory. The configuration for each service usually includes a switch to control whether xinetd should enable or disable the service.



When the *wait* is on *yes* the xinetd will not receive request for the service if it has a connection. So the number of connections is limited to one. It provides very good protection when we want to establish only one connection per time.

There are many more options available for xinetd. In most Linux distributions the full list of possible options and their description is accessible with a "man xinetd.conf" command.

To apply the new configuration a [SIGHUP](https://en.wikipedia.org/wiki/SIGHUP) signal must be sent to the xinetd process to make it re-read the configuration files. This can be achieved with the following command: `kill -SIGHUP "PID"`. PID is the actual process identifier number of the xinetd, which can be obtained with the command `pgrep xinetd`.[[6\]](https://en.wikipedia.org/wiki/Xinetd#cite_note-6)[[7\]](https://en.wikipedia.org/wiki/Xinetd#cite_note-7)

