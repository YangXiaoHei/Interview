#include "ds.h"

int count_one(int a)
{
    int n = 0;
    while (a) {
        a &= a - 1;
        n++;
    }
    return n;
}

int main()
{
    printf("%d\n", count_one(15));
    printf("%d\n", count_one(3));
    printf("%d\n", count_one(7));
}
