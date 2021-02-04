# Reentrancy VS thread safety

两者是正交的概念，描述的是不同的性质；

两者的深层原因有些类似:

1、execution  flow会不受控制地被suspend/preempt

## Thread safe but not reentrant

添加了lock，则就可以保证thread safe了，但是，能否保证reentrant呢？

## Reentrant but not thread safe

