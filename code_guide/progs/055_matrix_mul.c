#include "ds.h"

int *matrix_mul(int *A, int Ar, int Ac, int *B, int Br, int Bc)
{
    if (Ac != Br)
        return NULL;

    int *res = malloc(sizeof(int) * (Ar * Bc));
    memset(res, 0, sizeof(int) * (Ar * Bc));

    for (int i = 0; i < Ar; i++) 
        for (int j = 0; j < Bc; j++) {
            /* printf("res[%d][%d] = ", i, j); */
            for (int k = 0; k < Br; k++) {
                res[i * Bc + j] += A[i * Ac + k] * B[k * Bc + j];
                /*
                 * if (k < Br - 1)
                 *     printf("A[%d][%d] * B[%d][%d] + ", i, k, k, j);
                 * else
                 *     printf("A[%d][%d] * B[%d][%d]", i, k, k, j);
                 */
            }
            /* printf("\n"); */
        }
    return res;
}

int *gen_matrix(int r, int c)
{
    int *m = malloc(sizeof(int) * (r * c));
    for (int i = 0; i < r; i++) 
        for (int j = 0; j < c; j++)
            m[i * c + j] = randWithRange(1, 6);
    return m;
}

void print_matrix(int *m, int r, int c)
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) 
            printf("%-3d", m[i * c + j]);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int Ar = 2, Ac = 3, Br = 3, Bc = 2;
    int *A = gen_matrix(Ar, Ac);    
    print_matrix(A, Ar, Ac);
    int *B = gen_matrix(Br, Bc);
    print_matrix(B, Br, Bc);
    int *C = matrix_mul(A, Ar, Ac, B, Br, Bc);
    print_matrix(C, Ar, Bc);
}
