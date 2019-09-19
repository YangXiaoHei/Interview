#include "ds.h"

int count_1(int a)
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
    printf("%d\n", count_1(3));
    printf("%d\n", count_1(15));
    printf("%d\n", count_1(1));
    printf("%d\n", count_1(9));
}
