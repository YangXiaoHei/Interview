#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

long hash(long key) { return key; }

int merge(ht *h, int l, int r)
{
    l = l - ht_get(h, l) + 1;
    r = r + ht_get(h, r) - 1;

    int len = r - l + 1;
    ht_insert(h, l, len);
    ht_insert(h, r, len);
    return len;
}

int longest_consecutive(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;

    ht *h = ht_create(hash);
    int maxv = 0;
    for (int i = 0; i < size; i++) {
        if (ht_contain(h, arr[i]))
            continue;

        ht_insert(h, arr[i], 1);
        if (ht_contain(h, arr[i] - 1))
            maxv = max(maxv, merge(h, arr[i] - 1, arr[i]));
        if (ht_contain(h, arr[i] + 1))
            maxv = max(maxv, merge(h, arr[i], arr[i] + 1));
    }
    return maxv;
}

int main(int argc, char *argv[])
{
    int arr[] = { 100, 1, 200, 3, 2, 4, 5 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, size);
    printf("%d\n", longest_consecutive(arr, size));
}
