#include "ds.h"

void two_sum(int *arr, int size, int f, int l, int r, int k)
{
    while (l < r) {
        int val = arr[l] + arr[r];
        if (val == k && (l == f + 1 || arr[l] != arr[l - 1])) {
            printf("(%d %d %d)\n", arr[f], arr[l], arr[r]);
            l++, r--;
            continue;
        }
        if (val < k)
            l++;
        else
            r--;
    }
}

void three_sum(int *arr, int size, int key)
{
    if (!arr || size <= 0)
        return;

    for (int i = 0; i < size; i++) {
        if (i == 0 || arr[i] != arr[i - 1]) 
            two_sum(arr, size, i, i + 1, size - 1, key - arr[i]);
    }
}

int main()
{
    int arr[] = { -8, -4, -3, 0, 1, 2, 4, 5, 8, 9 };
    int size = sizeof(arr) / sizeof(arr[0]);
    three_sum(arr, size, 10);
}
