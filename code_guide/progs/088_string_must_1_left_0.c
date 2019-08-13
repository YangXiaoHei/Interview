#include "ds.h"

int must_1_left_0_core(int i, int n)
{
    if (i == n)
        return 1;

    if (i == n - 1)
        return 2;

    return must_1_left_0_core(i + 1, n) + must_1_left_0_core(i + 2, n);
}

int must_1_left_0(int n)
{
    return must_1_left_0_core(1, n);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 10; i++) 
        printf("%-3d\n", must_1_left_0(i));
}
