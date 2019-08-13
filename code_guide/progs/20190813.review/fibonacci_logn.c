#include "ds.h"

void fibonacci_core(int n, long *C)
{
    n--;
    long res[] = { 1, 0, 0, 1 };
    long D[4] = { 0 };
    while (n) {
        if (n & 1) {
            matrix_mul(res, 2, 2, C, 2, 2, D, 2, 2);
            memcpy(res, D, sizeof(long) * 4);
        }
        matrix_mul(C, 2, 2, C, 2, 2, D, 2, 2);
        memcpy(C, D, sizeof(long) * 4);

        n >>= 1;
    }
    memcpy(C, res, sizeof(long) * 4);
}

long fibonacci(int n)
{
    if (n <= 1)
        return 1;

    long C[] = { 1, 1, 1, 0 };
    fibonacci_core(n, C);
    return C[0 * 2 + 0] + C[1 * 2 + 0];
}

int main(int argc, char *argv[])
{
    int i = 100000000;
    BENCHMARK(
                printf("fibonacci(%d) = %-3ld\n", i, fibonacci(i));
            );
}
