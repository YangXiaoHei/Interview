#include <stdio.h>

int check(int i, int j, int k)
{
    int sum = 0;
    while (i) {
        sum += i % 10;
        i /= 10;
    }
    while (j) {
        sum += j % 10;
        j /= 10;
    }
    return sum <= k;
}

int find_grid(int *visited, int row, int col, int i, int j, int k)
{
    if (i < 0 || i >= row || j < 0 || j >= row)
        return 0;

    if (visited[i * row + j])
        return 0;

    if (!check(i, j, k)) 
        return 0;

    visited[i * row + j] = 1;

    return 1 + find_grid(visited, row, col, i - 1, j, k)
             + find_grid(visited, row, col, i + 1, j, k)
             + find_grid(visited, row, col, i, j - 1, k)
             + find_grid(visited, row, col, i, j + 1, k);
}

int robot_matrix_grid(int *visited, int row, int col, int i, int j, int k)
{
    if (!visited || row <= 0 || col <= 0 || i < 0 || i >= row || j < 0 || j >= col)
        return 0;

    return find_grid(visited, row, col, i, j, k);
}

int main(int argc, char *argv[])
{
    int v[40 * 40] = { 0 };
    robot_matrix_grid(v, 40, 40, 0, 0, 15);

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++)
            printf("%3d", v[i * 40 + j]);
        printf("\n");
    }
}


