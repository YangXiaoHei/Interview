#include "ds.h"

int find(int *arr, int r, int c, int key)
{
    if (!arr || r <= 0 || c <= 0)
        return 0;

    int i = 0, j = c - 1;
    while (i < r && j >= 0) {
        int val = arr[i * c + j];
        if (val == key)
            return 1;

        if (key > val) 
            i++;
        else
            j--;
    }
    return 0;
}

int main()
{
    int r = 4, c = 4;
    int arr[] = {
        0, 1, 2, 5,
        2, 3, 4, 7,
        4, 4, 4, 8,
        5, 7, 7, 9
    };
    int key;
    scanf("%d", &key);
    printf("%d\n", find(arr, r, c, key));
}
