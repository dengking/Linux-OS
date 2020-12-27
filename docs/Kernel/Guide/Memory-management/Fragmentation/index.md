# Fragmentation 



## wikipedia [Fragmentation (computing)](https://en.wikipedia.org/wiki/Fragmentation_(computing))





## Example

### 1) wikipedia [Memory-mapped file](https://en.wikipedia.org/wiki/Memory-mapped_file):

For small files, memory-mapped files can result in a waste of [slack space](https://en.wikipedia.org/wiki/Slack_space)[[7\]](https://en.wikipedia.org/wiki/Memory-mapped_file#cite_note-7) as memory maps are always aligned to the page size, which is mostly 4 KiB. Therefore, a 5 KiB file will allocate 8 KiB and thus 3 KiB are wasted. 