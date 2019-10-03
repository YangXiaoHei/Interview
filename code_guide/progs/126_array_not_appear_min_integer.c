#include "ds.h"

int not_appear(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int l = 0, r = size;
    while (l < r) {
        if (arr[l] == l + 1) {
            l++;
            printf("expend l to %d\n", l);
        } else if (arr[l] <= l || arr[l] > r || arr[arr[l] - 1] == arr[l]) {
            arr[l] = arr[--r];
            printf("shrink r to %d\n", r);
        } else {
            printf("swap %d %d\n", l, arr[l] - 1);
            swap(arr + l, arr + arr[l] - 1);
        }
        printf("l=%d r=%d \n", l, r);
    }
    return l + 1;
}

int main()
{
    int arr[] = { 3, 2, 2, 1, 4, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", not_appear(arr, size));
}
