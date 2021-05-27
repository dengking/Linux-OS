# SysVinit

## archlinux [SysVinit](https://wiki.archlinux.org/index.php/SysVinit)

On systems based on SysVinit, **init** is the first process that is executed once the Linux kernel loads. The default init program used by the kernel is `/sbin/init` provided by [systemd-sysvcompat](https://archlinux.org/packages/?name=systemd-sysvcompat) (by default on new installs, see [systemd](https://wiki.archlinux.org/index.php/Systemd)) or [sysvinit](https://aur.archlinux.org/packages/sysvinit/)AUR. The word **init** will always refer to sysvinit in this article.