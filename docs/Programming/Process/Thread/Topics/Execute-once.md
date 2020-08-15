# Execute once

在阅读cppreference `Storage class specifiers#Static local variables`，其中谈及了这样的问题：

> If multiple threads attempt to initialize the same static local variable concurrently, the initialization occurs exactly once (similar behavior can be obtained for arbitrary functions with [std::call_once](../thread/call_once.html)).
>
> Note: usual implementations of this feature use variants of the double-checked locking pattern, which reduces runtime overhead for already-initialized local statics to a single non-atomic boolean comparison.

这是在进行multiple thread programming中，经常会遇到的一类问题，有必要总结一下。

## cppreference std::call_once