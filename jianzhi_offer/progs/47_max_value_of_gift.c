#include <stdio.h>
#include "tool.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int max_value_of_matrix_core(int *matrix, int row, int col, int i, int j) 
{
    if (i < 0 || j < 0)
        return 0;

    int lbranch = max_value_of_matrix_core(matrix, row, col, i, j - 1);
    int ubranch = max_value_of_matrix_core(matrix, row, col, i - 1, j);
    return max(lbranch, ubranch) + matrix[i * col + j]; 
}

int max_value_of_matrix(int *matrix, int row, int col) 
{
    if (!matrix || row <= 0 || col <= 0)
        return 0;
    return max_value_of_matrix_core(matrix, row, col, row - 1, col - 1);
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
    int row = 4;
    int col = 4;
    int size = col * row;
    int *arr = arrayWithRange(size, 0, 20);
    print_matrix(arr, row, col);

    printf("%-3d\n", max_value_of_matrix(arr, row, col));

}
