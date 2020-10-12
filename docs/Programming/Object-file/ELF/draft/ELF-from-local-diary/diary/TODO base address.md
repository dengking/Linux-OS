#Base Address

The virtual addresses in the program headers might not represent the **actual** virtual addresses
of the program's memory image. Executable files typically contain **absolute code**. To let the
process execute correctly, the segments must reside at the virtual addresses used to build the
executable file. On the other hand, **shared object segments** typically contain
**position-independent code**. This lets a segment's virtual address change from one process to
another, without invalidating<!--使无效--> execution behavior. Though the system chooses virtual addresses for individual processes, it maintains the segments’ relative positions<!--尽管操作系统为每个进程都使用virtual address，但是它还是会维护segment的相对位置-->. Because
position-independent code uses relative addressing between segments<!--positioni-independent使用的在segment之间使用的是相对位置-->, the difference between
virtual addresses in memory must match the difference between virtual addresses in the file.<!--在内存中的两个virtual address之间的差值一定是和在文件中的virtual address的差值是相对的-->
The difference between the virtual address of any segment in memory and the corresponding
virtual address in the file is thus a single constant value for any one executable or shared object
in a given process<!--因此我们可以得出这样的一个结论：对于一个指定的进程，在它的内存image和file image中，在任何段中两个virtual address之间的差值是相同的-->. This difference is the **base address**<!--这个差值就是base address-->. One use of the base address is to relocate
the memory image of the program during dynamic linking<!--base address的用途之一就是在dynamic linking阶段取重定位memory image-->.
An executable or shared object file's base address is calculated during execution from three
values: the virtual memory load address, the maximum page size, and the lowest virtual address
of a program's loadable segment. To compute the base address, one determines the memory
address associated with the lowest  p_vaddr value for a  PT_LOAD  segment<!--首先确认对PT_LOAD segment的最低的p_vaddr对应的memory address-->. This address is
truncated to the nearest multiple of the maximum page size<!--然后将这个memory address调整为maximum page size的整数倍-->. The corresponding  p_vaddr value
itself is also truncated to the nearest multiple of the maximum page size<!--然后将p_vaddr也调整为maximum page size的整数倍-->. The base address is
the difference between the truncated memory address and the truncated  p_vaddr  value<!--base  address就是两个调整后的值的差值-->.

一个executable file或shared object file的base address是在执行过程中根据三个值计算而来的：

1. the virtual memory load address装入地址
2. the maximum page size
3. the lowest virtual address of a program's loadable segment





# Q&A

1. base address有何用？