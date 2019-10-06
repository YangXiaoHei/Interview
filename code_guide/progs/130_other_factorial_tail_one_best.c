#include "ds.h"

int tail_one(int n)
{
    if (n < 1)
        return -1;
    int cnt = 0;
    int tmp = n;
    while (tmp) {
        tmp &= tmp - 1;
        cnt++;
    }
    return n - cnt;
}

int main()
{
    for (int i = 1; i <= 100; i++)
        printf("%d! tail one %d\n", i, tail_one(i));
}
