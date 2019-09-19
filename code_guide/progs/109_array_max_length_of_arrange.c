#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int max_length(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;

    ht *h = ht_create();

    int len = 0;
    int maxv = 0, minv = 0;
    for (int i = 0; i < size; i++) {
        minv = 2147483647;
        maxv = -2147483647-1;
        for (int j = i; j < size; j++) {
            if (ht_contain(h, arr[j]))
                break;
            ht_insert(h, arr[j], 1);
            minv = min(arr[j], minv); 
            maxv = max(arr[j], maxv);
            if (maxv - minv == j - i)
                len = max(len, j - i + 1);
        }
        ht_clear(h);
    }
    ht_release(&h);
    return len;
}


int main()
{
    int arr[] = { 5, 5, 3, 2, 6, 4, 3 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, size);
    printf("%d\n", max_length(arr, size));
}
