# systemd.service

## freedesktop [systemd.service](https://www.freedesktop.org/software/systemd/man/systemd.service.html#)

### Description[¶](https://www.freedesktop.org/software/systemd/man/systemd.service.html#Description)

A **unit configuration file** whose name ends in "`.service`" encodes information about a process controlled and supervised(监督) by `systemd`.

This man page lists the configuration options **specific** to this unit type. See [systemd.unit(5)](https://www.freedesktop.org/software/systemd/man/systemd.unit.html#) for the **common** options of all unit configuration files. The common configuration items are configured in the generic "`[Unit]`" and "`[Install]`" sections. The **service** specific configuration options are configured in the "`[Service]`" section.

> 总结：特定的的配置项和通用的配置项。

Additional options are listed in [systemd.exec(5)](https://www.freedesktop.org/software/systemd/man/systemd.exec.html#), which define the execution environment the commands are executed in（执行环节）, and in [systemd.kill(5)](https://www.freedesktop.org/software/systemd/man/systemd.kill.html#), which define the way the processes of the service are terminated(终止流程), and in [systemd.resource-control(5)](https://www.freedesktop.org/software/systemd/man/systemd.resource-control.html#), which configure resource control settings for the processes of the service.

If a service is requested under a certain name but no **unit configuration file** is found, `systemd` looks for a `SysV init` script by the same name (with the `.service` suffix removed) and dynamically creates a service unit from that script. This is useful for compatibility with `SysV`. Note that this compatibility is quite comprehensive but not 100%. For details about the incompatibilities, see the [Incompatibilities with SysV](https://www.freedesktop.org/wiki/Software/systemd/Incompatibilities) document.

### Service Templates[¶](https://www.freedesktop.org/software/systemd/man/systemd.service.html#Service%20Templates)

It is possible for **systemd** services to take a single argument via the "`service@argument.service`" syntax. Such services are called "instantiated" services, while the unit definition without the *argument* parameter is called a "template". An example could be a`dhcpcd@.service` service template which takes a network interface as a parameter to form an instantiated service. Within the service file, this parameter or "instance name" can be accessed with %-specifiers. See [systemd.unit(5)](https://www.freedesktop.org/software/systemd/man/systemd.unit.html#) for details.

> 思考：上面这段话并没有搞清楚



### Options[¶](https://www.freedesktop.org/software/systemd/man/systemd.service.html#Options)

Service files must include a "`[Service]`" section, which carries information about the service and the process it supervises（监管）. A number of options that may be used in this section are shared with other unit types. These options are documented in [systemd.exec(5)](https://www.freedesktop.org/software/systemd/man/systemd.exec.html#), [systemd.kill(5)](https://www.freedesktop.org/software/systemd/man/systemd.kill.html#) and [systemd.resource-control(5)](https://www.freedesktop.org/software/systemd/man/systemd.resource-control.html#). The options specific to the "`[Service]`" section of service units are the following:





## how to run a program as a service in systemd system

https://superuser.com/questions/1236961/running-an-executable-as-a-service-under-debian-8

https://www.tecmint.com/create-new-service-units-in-systemd/