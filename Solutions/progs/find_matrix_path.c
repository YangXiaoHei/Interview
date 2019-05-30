#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int succ_len = 0;
int visited[5][5];

int find_path(char matrix[5][5], int row, int col, int i, int j, char *word)
{
    printf("---- i=%d j=%d\n", i, j);
    if (i < 0 || i >= row || j < 0 || j >= row) {
        printf("overbounds i=%d j=%d\n", i, j);
        return 0;
    }

    if (visited[i][j]) {
        printf("already visited i=%d j=%d\n", i, j);
        return 0;
    }

    if (strlen(word) == succ_len) {
        printf("final i=%d j=%d\n", i, j);
        return 1;
    } 

    int has_path = 0;
    if (i >= 0 && i < row && j >= 0 && j < col && matrix[i][j] == word[succ_len]) {
        succ_len++;
        printf("i=%d j=%d succ_len=%d\n", i, j, succ_len);
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

    /*
     * i=0 j=0 succ_len=1
     * overbounds i=-1 j=0
     * i=1 j=0 succ_len=2
     * already visited i=0 j=0
     * overbounds i=1 j=-1
     * i=1 j=1 succ_len=3
     * i=2 j=1 succ_len=4
     * already visited i=1 j=1
     * final i=3 j=1
     * already visited i=1 j=0
     * final i=1 j=2
     * overbounds i=0 j=-1
     * 0
     */
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


