#include <stdio.h>
#include <stdlib.h>
#include "tool.h"
#include <time.h>

int count(int *a, int size, int lo, int mid)
{
    int cnt = 0;
    for (int i = 0; i < size; i++)
        if (a[i] >= lo && a[i] <= mid)
            cnt++;
    return cnt;
}

int find_duplicate(int *a, int size)
{
    if (!a || size <= 1)
        return -1;

    int n = size - 1;
    int lo = 1, hi = n;
    while (1) {
        int mid = (lo + hi) >> 1;
        int cnt = count(a, size, lo, mid);
        int should = mid - lo + 1;
        if (cnt <= should) {
            lo = mid + 1;
        } else if (lo == mid) {
            return lo;
        } else {
            hi = mid;
        }
    }
    exit(1);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int n = 5;
    int size = n + 1;
    int *array = arrayWithRange(size, 1, n);
    printArray(array, size);
    printf("%d\n", find_duplicate(array, size));
}
