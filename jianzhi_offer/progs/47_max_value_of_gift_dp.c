#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int max_value_of_gift(int *matrix, int row, int col)
{
    if (!matrix || row <= 0 || col <= 0)
        return 0;

    int *copy = malloc(sizeof(int) * row * col);
    memcpy(copy, matrix, sizeof(int) * row * col);

    int left = 0, up = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            left = 0;
            up = 0;

            if (i > 0)
                up = copy[(i - 1) * col + j];

            if (j > 0)
                left = copy[i * col + j - 1];

            copy[i * col + j] = max(up, left) + matrix[i * col + j];
        }
    }
    int max_val = copy[(row - 1) * col + col - 1];
    free(copy);
    return max_val;
}

void print_matrix(int *arr, int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) 
            printf("%-4d", arr[i * col + j]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int row = 20;
    int col = 20;
    int size = row * col;
    int *arr = arrayWithRange(size, 0, 100);
    print_matrix(arr, row, col);

    printf("%-3d\n", max_value_of_gift(arr, row, col));
}
