#include "ds.h"

void xswap(int *a, int *b)
{
    if (a == b)
        return;

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int main()
{
    int a = 1, b = 2;
    xswap(&a, &b);
    printf("%d %d\n", a, b);
}
