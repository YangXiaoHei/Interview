#include "ds.h"

int *matrix_gen(int r, int c)
{
    int *m = malloc(sizeof(int) * (r * c));
    for (int i = 0; i < r; i++) 
        for (int j = 0; j < c; j++)
            m[i * c + j] = randWithRange(1, 6);
    return m;
}

void matrix_clr(int *A, int Ar, int Ac)
{
    memset(A, 0, sizeof(int) * (Ar * Ac));
}

// 首先实现一个靠谱的矩阵乘法函数, 结果矩阵内存由调用者分配
void matrix_mul(int *A, int Ar, int Ac, int *B, int Br, int Bc, int *C, int Cr, int Cc)
{
    // 把结果数组清理干净
    matrix_clr(C, Cr, Cc);
    if (Cr != Ar || Cc != Bc)
        return;

    for (int i = 0; i < Ar; i++) 
        for (int j = 0; j < Bc; j++) 
            for (int k = 0; k < Br; k++) 
                C[i * Bc + j] += A[i * Ac + k] * B[k * Bc + j]; 
}

// for debug
void matrix_print(int *A, int Ar, int Ac)
{
    for (int i = 0; i < Ar; i++) {
        for (int j = 0; j < Ac; j++) 
            printf("%-3d", A[i * Ac + j]);
        printf("\n");
    }
    printf("\n");
}

void fibonacci_helper(int *A, int p, int *C)
{
    int res[4] = { 1, 0, 0, 1 }; // 单位矩阵
    int tmp[4]; 
    memcpy(tmp, A, sizeof(int) * 4);
    int B[4] = { 0 }; 

    while (p) {
        if (p & 1) {
            matrix_mul(res, 2, 2, tmp, 2, 2, B, 2, 2);
            memcpy(res, B, sizeof(int) * 4);
        }
        matrix_mul(tmp, 2, 2, tmp, 2, 2, B, 2, 2);
        memcpy(tmp, B, sizeof(int) * 4);

        p >>= 1;
    }
    memcpy(C, res, sizeof(int) * 4);
}

int fibonacci(int n)
{
    int res[4] = { 0, 1, 1, 2 };
    if (n <= 3)
        return res[n];

    int A[] = { 1, 1, 1, 0 };
    int C[4];
    fibonacci_helper(A, n - 2, C);
    return C[0 * 2 + 0] + C[1 * 2 + 0];
}

void matrix_test(void)
{
    int *A = matrix_gen(2, 3);    
    matrix_print(A, 2, 3);
    int *B = matrix_gen(3, 1);
    matrix_print(B, 3, 1);
    int *C = matrix_gen(2, 1);
    matrix_clr(C, 2, 1);
    matrix_mul(A, 2, 3, B, 3, 1, C, 2, 1);
    matrix_print(C, 2, 1);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 40; i++)
        printf("i = %d fibonacci = %d\n", i, fibonacci(i));
}
