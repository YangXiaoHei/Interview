#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int max_length(int *arr, int size) 
{
    if (!arr || size <= 0)
        return -1;

    int *copy = malloc(sizeof(int) * size);
    memcpy(copy, arr, sizeof(int) * size);
    for (int i = 0; i < size; i++) 
        copy[i] = copy[i] == 0 ? copy[i] : (copy[i] > 0 ? 1 : -1);

    int len = -2147483647-1;
    ht *h = ht_create();
    ht_insert(h, 0, -1);
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += copy[i]; 
        if (ht_contain(h, sum))
            len = max(len, i - ht_get(h, sum));

        if (!ht_contain(h, sum))
            ht_insert(h, sum, i);
    }
    ht_release(&h);
    free(copy);
    return len;
}

int main()
{
    int arr[] = { -1, 1, 1, -1, 0, 1, -1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("len = %d\n", max_length(arr, size));
}
