#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int max_length(int *arr, int size, int key)
{
    if (!arr || size <= 0)
        return -1;

    int l = 0, r = 0;
    int sum = arr[l];
    int len = -2147483647-1;
    while (r < size) {
        if (sum == key) {
            len = max(r - l + 1, len);
            sum -= arr[l++];
        } else if (sum < key) {
            sum += arr[++r];
        } else {
            sum -= arr[l++];
        }
    }
    return len;
}

int main()
{
    int arr[] = { 1, 2, 1, 1, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", max_length(arr, size, 3));
}
