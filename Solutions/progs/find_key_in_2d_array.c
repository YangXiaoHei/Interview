#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_key_in_2d_array(int array[][4], int row, int col, int key)
{
    int i = 0, j = col - 1;
    int find = 0;
    while (i < row && j > 0) {
        int val = array[i][j];
        if (val == key) {
            find = 1;
            break;
        }

        if (key < val) --j;
        else           ++i;
    }
    return find;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int key = rand() % 16;
    int array[][4] = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}
    };
    printf("find %d in 2d array, result=%d\n",
            key, find_key_in_2d_array(array, 4, 4, key));
}
