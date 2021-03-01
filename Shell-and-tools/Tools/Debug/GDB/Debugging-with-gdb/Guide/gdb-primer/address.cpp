#include <stdio.h>
#include <stdlib.h>

int global_init_a=1;
int global_uninit_a;
static int static_global_init_a=1;
static int static_global_uninit_a;
const int const_global_a=1;

int global_init_b=1;
int global_uninit_b;
static int static_global_init_b=1;
static int static_global_uninit_b;
const int const_global_b=1;
/*上面全部为全局变量，main函数中的为局部变量*/
int main()
{
int local_init_a=1;
int local_uninit_a;
static int static_local_init_a=1;
static int static_local_uninit_a;
const int const_local_a=1;

int local_init_b=1;
int local_uninit_b;
static int static_local_init_b=1;
static int static_local_uninit_b;
const int const_local_b=1;

int * malloc_p_a;
void * malloc_p_b;

malloc_p_a=(int *)malloc(sizeof(int));
malloc_p_b = malloc(100*1024*1024);
printf("\n         &global_init_a=%p \t  global_init_a=%d\n",&global_init_a,global_init_a);
printf("       &global_uninit_a=%p \t global_uninit_a=%d\n",&global_uninit_a,global_uninit_a);

printf("  &static_global_init_a=%p \t static_global_init_a=%d\n",&static_global_init_a,static_global_init_a);

printf("&static_global_uninit_a=%p \t  static_global_uninit_a=%d\n",&static_global_uninit_a,static_global_uninit_a);

printf("        &const_global_a=%p \t const_global_a=%d\n",&const_global_a,const_global_a);


printf("\n         &global_init_b=%p \t global_init_b=%d\n",&global_init_b,global_init_b);

printf("       &global_uninit_b=%p \t global_uninit_b=%d\n",&global_uninit_b,global_uninit_b);

printf("  &static_global_init_b=%p \t static_global_init_b=%d\n",&static_global_init_b,static_global_init_b);

printf("&static_global_uninit_b=%p \t static_global_uninit_b=%d\n",&static_global_uninit_b,static_global_uninit_b);

printf("        &const_global_b=%p \t const_global_b=%d\n",&const_global_b,const_global_b);

            

printf("\n          &local_init_a=%p \t local_init_a=%d\n",&local_init_a,local_init_a);

printf("        &local_uninit_a=%p \t local_uninit_a=%d\n",&local_uninit_a,local_uninit_a);

printf("   &static_local_init_a=%p \t static_local_init_a=%d\n",&static_local_init_a,static_local_init_a);

printf(" &static_local_uninit_a=%p \t static_local_uninit_a=%d\n",&static_local_uninit_a,static_local_uninit_a);

printf("         &const_local_a=%p \t const_local_a=%d\n",&const_local_a,const_local_a);


printf("\n          &local_init_b=%p \t  local_init_b=%d\n",&local_init_b,local_init_b);

printf("        &local_uninit_b=%p \t local_uninit_b=%d\n",&local_uninit_b,local_uninit_b);

printf("   &static_local_init_b=%p \t static_local_init_b=%d\n",&static_local_init_b,static_local_init_b);

printf(" &static_local_uninit_b=%p \t static_local_uninit_b=%d\n",&static_local_uninit_b,static_local_uninit_b);

printf("         &const_local_b=%p \t const_local_b=%d\n",&const_local_b,const_local_b);


printf("             malloc_p_a=%p \t *malloc_p_a=%d\n",malloc_p_a,*malloc_p_a);

printf("             malloc_p_b=%p \n",malloc_p_b);

getchar();

return 0;
}
