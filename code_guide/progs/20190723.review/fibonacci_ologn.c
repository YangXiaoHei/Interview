#include "ds.h"

void matrix_test(void)
{
    long *A = matrix_gen(2, 4);
    matrix_print(A, 2, 4);
    long *B = matrix_gen(4, 1);
    matrix_print(B, 4, 1);
    long C[2] = { 0 };
    matrix_mul(A, 2, 4, B, 4, 1, C, 2, 1);
    matrix_print(C, 2, 1);
}

void fibonacci_helper(long *A, int p)
{
    long res[4] = { 1, 0, 0, 1 };
    long tmp[4] = { 0 };
    memcpy(tmp, A, sizeof(long) * 4);

    long trans[4] = { 0 };
    while (p) {
        if (p & 1) {
            matrix_mul(res, 2, 2, tmp, 2, 2, trans, 2, 2); 
            memcpy(res, trans, sizeof(long) * 4);
        }
        matrix_mul(tmp, 2, 2, tmp, 2, 2, trans, 2, 2);
        memcpy(tmp, trans, sizeof(long) * 4);

        p >>= 1;
    }
    memcpy(A, res, sizeof(long) * 4);
}

long fibonacci(int n)
{
    if (n < 0)
        return 0;
    int arr[] = { 0, 1, 1, 2 };
    if (n <= 3)
        return arr[n];

    long A[] = { 1, 1, 1, 0 };
    fibonacci_helper(A, n - 2);
    return A[0 * 2 + 0] + A[1 * 2 + 0];
}

void fun_test(void)
{
    for (int i = 0; i < 40; i++)
        printf("fibonacci(%d) = %ld\n", i, fibonacci(i));
}

int main(int argc, char *argv[])
{
    BENCHMARK(
                long n = fibonacci(1000000000);
                printf("%ld\n", n);
             );
}
