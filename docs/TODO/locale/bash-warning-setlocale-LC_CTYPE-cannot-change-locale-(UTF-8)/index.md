在 `.bash_profile` 中添加如下:

```bash
export PATH
export LC_ALL="zh_CN.GBK"
export LANG="zh_CN.GBK"
```



`source`后，输出如下:

```bash
[dk@localhost ~]$ source .bash_profile 
-bash: warning: setlocale: LC_ALL: cannot change locale (zh_CN.GBK)
-bash: warning: setlocale: LC_ALL: cannot change locale (zh_CN.GBK)
[dk@localhost ~]$ 
```

