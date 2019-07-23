#include "ds.h"

void fibonacci_helper(long *A, int p)
{
    long res[4] = { 1, 0, 0, 1 }; // 单位矩阵
    long tmp[4]; 
    memcpy(tmp, A, sizeof(long) * 4);
    long B[4] = { 0 }; 

    while (p) {
        if (p & 1) {
            matrix_mul(res, 2, 2, tmp, 2, 2, B, 2, 2);
            memcpy(res, B, sizeof(long) * 4);
        }
        matrix_mul(tmp, 2, 2, tmp, 2, 2, B, 2, 2);
        memcpy(tmp, B, sizeof(long) * 4);

        p >>= 1;
    }
    memcpy(A, res, sizeof(long) * 4);
}

int fibonacci(int n)
{
    int res[4] = { 0, 1, 1, 2 };
    if (n <= 3)
        return res[n];

    long A[] = { 1, 1, 1, 0 };
    fibonacci_helper(A, n - 2);
    return A[0 * 2 + 0] + A[1 * 2 + 0];
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 40; i++)
        printf("i = %d fibonacci = %d\n", i, fibonacci(i));
}
