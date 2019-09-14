#include "ds.h"

void xswap(int *a, int *b)
{
    if (a == b)
        return;

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int main(int argc, char *argv[])
{
    int a = 1;
    int b = 2;

    xswap(&a, &b);
    printf("%d %d\n", a, b);
}
