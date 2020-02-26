# Stream VS fd

OS层的system call都是使用的fd。

Stream一种抽象，他是对fd的封装，基于它，实现了很多非常简单易用的操作。