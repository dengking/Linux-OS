# Dangling pointer

dangling pointer和我们平时所说的wild pointer是同一个意思；

## 维基百科[Dangling pointer](https://en.wikipedia.org/wiki/Dangling_pointer)	







## Dangling pointer素材

D:\github\dengking\programming-language-theory\programming-language\docs\C-family-language\C++\Library\Standard-library\Utility-library\Dynamic-memory-management\Smart-pointers\unique_ptr\unique_ptr.md

Lifetime:[Lifetime](https://en.cppreference.com/w/c/language/lifetime) 

```c



int* foo(void) {

   int a = 17; // a has automatic storage duration

​    return &a;

}  // lifetime of a ends

int main(void) {

​    int* p = foo(); // p points to an object past lifetime ("dangling pointer")

​    int n = *p; // undefined behavior

}

```





### geeksforgeeks [Dangling, Void , Null and Wild Pointers](https://www.geeksforgeeks.org/dangling-void-null-wild-pointers/)