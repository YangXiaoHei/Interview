#include <stdio.h>
#include <stdlib.h>
#include "tool.h"
#include <time.h>
#include <sys/time.h>

int count(int *a, int size, int lo, int mid)
{
    int cnt = 0;
    for (int i = 0; i < size; i++)
        if (a[i] >= lo && a[i] <= mid)
            cnt++;
    return cnt;
}

int find_dup(int *a, int size, int lo, int hi)
{
    if (!a || size <= 1 || lo >= hi)
        return -1;

    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        int cnt = count(a, size, lo, mid);
        printf("lo=%d mid=%d hi=%d cnt=%d\n", lo, mid, hi, cnt);
        if (lo == hi) {
            if (cnt > 1)
                return lo;
            break;
        }

        if (cnt <= mid - lo + 1) 
            lo = mid + 1;
        else 
            hi = mid;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int array[100];
    int size = 100;
    parseArray(array, &size, "4 4 4 4 4");
    printArray(array, size);
    printf("%d\n", find_dup(array, size, 1, 4));
}
