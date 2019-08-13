#include "ds.h"

void must_1_left_0_core(int n, long *C)
{
    long res[] = { 1, 0, 0, 1 };
    n -= 2;
    long tmp[4] = { 0 };
    while (n) {
        if (n & 1) {
            matrix_mul(res, 2, 2, C, 2, 2, tmp, 2, 2);
            memcpy(res, tmp, sizeof(long) * 4);
        }
        matrix_mul(C, 2, 2, C, 2, 2, tmp, 2, 2);
        memcpy(C, tmp, sizeof(long) * 4);

        n >>= 1;
    }
    memcpy(C, res, sizeof(long) * 4);
}

long must_1_left_0(int n)
{
    if (n <= 0)
        return -1;

    if (n == 1)
        return 1;

    if (n == 2)
        return 2;

    long C[] = { 1, 1, 1, 0 };
    must_1_left_0_core(n, C);
    return C[0 * 2 + 0] * 2 + C[1 * 2 + 0];
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 100; i++)
        printf("res(%d) = %-3ld\n", i, must_1_left_0(i));
}
