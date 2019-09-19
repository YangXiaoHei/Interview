#include "ds.h"

int add(int a, int b)
{
    int c = 0;
    while (b) {
        c = a ^ b;
        b = (a & b) << 1;
        a = c;
    } 
    return a;
}

int sub(int a, int b)
{
    return add(a, add(~b, 1));
}

int main()
{
    printf("%d\n", sub(-2147483647, 1));
    printf("%d\n", sub(-2147483647, -1));
    printf("%d\n", sub(1, -2147483647));
}
