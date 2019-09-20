#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int max_length(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    for (int i = 0; i < size; i++)
        arr[i] = arr[i] != 0 ? arr[i] : -1;

    int key = 0;
    int len = -2147483647-1;
    int sum = 0;
    ht *h = ht_create();
    ht_insert(h, 0, -1);

    for (int i = 0; i < size; i++) {
        sum += arr[i];
        if (ht_contain(h, sum - key))
            len = max(len, i - ht_get(h, sum - key));

        if (!ht_contain(h, sum))
            ht_insert(h, sum, i);
    }
    ht_release(&h);
    return len;
}

int main()
{
    int arr[] = { 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", max_length(arr, size));
}
