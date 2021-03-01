#include <stdio.h>

int func2(int c, int d)
{
    d += 1;

    return c + d;
}

int func1(int a, int b)
{
    a += 1;
    
    return func2(a, b);
}

int main()
{
    int a = 2;
    int b = 6;

    int d = func1(a, b);

    printf("sum: %d\n", d);

    return 0;
}
