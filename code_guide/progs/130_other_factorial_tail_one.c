#include "ds.h"

int tail_one(int n)
{
    if (n < 1)
        return -1;
    int res = 0;
    while (n) {
        n /= 2;
        res += n;
    }
    return res;
}

int main()
{
    for (int i = 0; i < 100; i++) {
        printf("%d! tail one %d\n", i, tail_one(i));
    }
}
