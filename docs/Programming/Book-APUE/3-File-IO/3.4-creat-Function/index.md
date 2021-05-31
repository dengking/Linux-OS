# 3.4 creat Function

> NOTE:
>
> 需要注意的是，create函数相当于：
>
> ```C
> open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
> ```
>
> 其中有`O_TRUNC`，这说明如果文件`path`已经存在，那么就会对该文件进行truncate，显然这会导致对已有文件的修改，并且这种修改是隐式的，chapter 3.11 Atomic Operations中介绍了更加安全的方式，即首先判断文件是否存在，然后在由用户来决定如何来进行操作；
>
> 

