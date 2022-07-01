# man 1 time

我的实践:

```bash
time python nertcsdk/build/build.py --platform ios
```



## man7 [time(1) — Linux manual page](https://man7.org/linux/man-pages/man1/time.1.html)



## stackexchange [How to get execution millisecond time of a command in zsh?](https://unix.stackexchange.com/questions/453338/how-to-get-execution-millisecond-time-of-a-command-in-zsh)



[A](https://unix.stackexchange.com/a/453339)

zsh's `time` uses the `TIMEFMT` variable to control the format. [By default](http://zsh.sourceforge.net/Doc/Release/Parameters.html), this is `%J %U user %S system %P cpu %*E total`, which produces the following.

```bash
$ time sleep 2
sleep 2 0.00s user 0.00s system 0% cpu 2.002 total
```

This *does* produce millisecond accuracy (at least for `total`), so perhaps your system has a different default set (lagging distro?), or has modified `TIMEFMT`.

Have a look at the [manual page](http://zsh.sourceforge.net/Doc/Release/Parameters.html) for possible formats. I use the following in `~/.zshrc`:

```bash
TIMEFMT=$'\n================\nCPU\t%P\nuser\t%*U\nsystem\t%*S\ntotal\t%*E'
```

which produces the following.

```bash
$ time sleep 2 

================
CPU     0%
user    0.003
system  0.000
total   2.006
```