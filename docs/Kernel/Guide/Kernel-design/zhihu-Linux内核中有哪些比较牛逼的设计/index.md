# zhihu [Linux 内核中有哪些比较牛逼的设计?](https://www.zhihu.com/question/332710035)



## [水灵木子珈的回答 - 知乎](https://www.zhihu.com/question/332710035/answer/1854780284) 

cgroup + namespace. 

基于这两个技术，有了LXC也有了Docker。

简单的来说，两个技术的作用就是：

- **cgroup = [limits](https://www.zhihu.com/search?q=limits&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A1854780284}) how much you can use;**
- **namespaces = limits what you can see (and therefore use**



