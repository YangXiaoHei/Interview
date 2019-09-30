#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int subarr_max(int *arr, int size)
{
    int cur = 0, maxsum = -2147483647-1;
    for (int i = 0; i < size; i++) {
        cur += arr[i];
        maxsum = max(maxsum, cur);
        cur = cur < 0 ? 0 : cur;
    }
    return maxsum;
}

int submatrix_max(int *matrix, int r, int c)
{
    int *help = malloc(sizeof(int) * c);
    int res = 0;
    int tmp = 0;
    // 必须以哪一行开头
    for (int k = 0; k < r; k++) {
        memset(help, 0, sizeof(int) * c);

        // 0 ~ 1, 0 ~ 2, ... 1 ~ 2, 1 ~ 3, ... 2 ~ 3, 2 ~ 4, ...
        for (int i = k; i < r; i++) {
            for (int j = 0; j < c; j++) {
                help[j] += matrix[i * c + j];
            }
            tmp = subarr_max(help, c);
            res = max(tmp, res);
        } 
    }
    free(help);
    return res;
}

int main()
{
    {
        int matrix[] = {
            -1, -1, -1,
            -1,  2,  2,
            -1, -1, -1
        };
        int r = 3, c = 3;
        printf("%d\n", submatrix_max(matrix, r, c));
    }
    {
        int matrix[] = {
            -90, 48, 78,
            64, -40, 64,
            -81, -7, 66
        };
        int r = 3, c = 3;
        printf("%d\n", submatrix_max(matrix, r, c));
    }
}
