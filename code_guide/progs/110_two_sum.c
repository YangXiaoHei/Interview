#include "ds.h"

void two_sum(int *arr, int size, int key)
{
    if (!arr || size <= 0)
        return;

    int lo = 0, hi = size - 1;
    while (lo < hi) {
        int val = arr[lo] + arr[hi];
        if (val == key && (lo == 0 || arr[lo] != arr[lo - 1])) {
            printf("(%d %d)\n", arr[lo], arr[hi]);
            lo++, hi--;
            continue;
        } 

        if (val < key)
            lo++;
        else
            hi--;
    }
}

int main()
{
    int arr[] = { -8, -4, -3, 0, 1, 2, 4, 5, 8, 9 };
    /* int arr[] = { 1, 1, 1, 9 }; */
    int size = sizeof(arr) / sizeof(arr[0]);
    two_sum(arr, size, 10);
}
