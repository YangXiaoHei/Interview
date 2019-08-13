#include "ds.h"

long must_1_left_0(int n)
{
    if (n <= 0)
        return -1;

    if (n == 1)
        return 1;

    if (n == 2)
        return 2;

    long prev = 1, cur = 2, next = 3;
    for (int i = n - 2; i > 1; i--) {
        prev = cur;
        cur = next;
        next = prev + cur;
    }
    return next;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 100; i++)
        printf("res(%d) = %-3ld\n", i, must_1_left_0(i));
}
