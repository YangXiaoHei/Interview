#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int succ_len = 0;
int visited[5][5];

int find_path(char matrix[5][5], int row, int col, int i, int j, char *word)
{
    if (i < 0 || i >= row || j < 0 || j >= row) 
        return 0;

    if (visited[i][j]) 
        return 0;

    if (strlen(word) == succ_len) 
        return 1;

    int has_path = 0;
    if (i >= 0 && i < row && j >= 0 && j < col && matrix[i][j] == word[succ_len]) {
        succ_len++;
        visited[i][j] = 1;

         has_path = find_path(matrix, row, col, i - 1, j, word) ||
                       find_path(matrix, row, col, i + 1, j, word) ||
                       find_path(matrix, row, col, i, j - 1, word) ||
                       find_path(matrix, row, col, i, j + 1, word);

        if (!has_path) {
            succ_len--;
            visited[i][j] = 0;
        }
    }

    return has_path;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            visited[i][j] = 0;

    char matrix[5][5] = {
        {'a', 'b', 'c', 'q', 'e'},
        {'b', 'c', 'g', 'e', 'p'},
        {'a', 'e', 'c', 'd', 'e'},
        {'f', 'b', 'c', 'e', 'g'},
        {'a', 't', 'e', 'd', 'e'},
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf("%-3c", matrix[i][j]);
        printf("\n");
    }

    printf("%d\n", find_path(matrix, 5, 5, 0, 0, "abcecde"));
}


