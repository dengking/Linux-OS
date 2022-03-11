# xcrun

它应该是Xcode run的缩写。

## manpagez [man xcrun(1)](https://www.manpagez.com/man/1/xcrun/)



## jianshu [iOS编译命令 clang xcrun](https://www.jianshu.com/p/80240af0bac6)

其实，xcode安装的时候顺带安装了xcrun命令，xcrun命令在clang的基础上进行了一些封装，要更好用一些。

```bash
##### 在模拟器下编译
xcrun -sdk iphonesimulator clang -rewrite-objc main.m

#在真机下编译
xcrun -sdk iphoneos clang -rewrite-objc main.m
```

有时候我们在本机安装了多个Xcode，可以指定xcrun使用不同的Xcode对应的SDK

```csharp
xcode-select -s /Applications/Xcode9.4.1.app
```

