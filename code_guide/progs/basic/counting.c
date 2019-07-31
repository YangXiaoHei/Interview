#include "ds.h"

void counting(int *arr, int size, int lo, int hi)
{
    if (!arr || size <= 1)
        return;

    int *cnt = malloc(sizeof(int) * (hi - lo + 1));
    memset(cnt, 0, sizeof(int) * (hi - lo + 1));
    
    for (int i = 0; i < size; i++)
        cnt[arr[i] - lo]++;

    int k = 0;
    for (int i = 0; i < hi - lo + 1; i++)
        while (cnt[i]) {
            arr[k++] = i + lo;
            cnt[i]--;
        }

    free(cnt);
}

int main(int argc, char *argv[])
{
    int lo = 100, hi = 400;
    int size = 100;
    int *arr = arrayWithRange(size, lo, hi + 1);
    counting(arr, size, lo, hi);
    if (!is_sorted(arr, size)) {
        printf("not sorted!\n");
        printArray(arr, size);
    }
}
