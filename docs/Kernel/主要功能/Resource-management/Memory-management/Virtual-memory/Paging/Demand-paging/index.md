# Demand paging



## wikipedia [Demand paging](https://en.wikipedia.org/wiki/Demand_paging)

In [computer](https://en.wikipedia.org/wiki/Computer) [operating systems](https://en.wikipedia.org/wiki/Operating_systems), **demand paging** (as opposed to [anticipatory](https://en.wikipedia.org/wiki/Paging#Page_replacement_techniques) paging) is a method of [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) management. In a system that uses demand paging, the operating system copies a disk [page](https://en.wikipedia.org/wiki/Paging) into physical memory only if an attempt is made to access it and that page is not already in memory (*i.e.*, if a [page fault](https://en.wikipedia.org/wiki/Page_fault) occurs). It follows that a [process](https://en.wikipedia.org/wiki/Process_(computing)) begins execution with none of its pages in physical memory, and many page faults will occur until most of a process's [working set](https://en.wikipedia.org/wiki/Working_set) of pages are located in physical memory. This is an example of a [lazy loading](https://en.wikipedia.org/wiki/Lazy_loading) technique.

> NOTE: 
>
> `mmap`也是使用的demand paging，在 wikipedia [mmap](https://en.wikipedia.org/wiki/Mmap) 中，也对此进行了说明。