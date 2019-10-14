#include "ds.h"

int search_rotate(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    if (size == 1)
        return arr[0];

    int lo = 0, hi = size - 1;
    while (lo < hi) {
        if (arr[lo] < arr[hi])
            return arr[lo];

        // 只有两个元素的情况下, arr[lo] >= arr[hi], 直接返回 arr[hi]
        // 避免死循环
        // 比如 { 7, 1 }  
        if (lo == hi - 1)
            return arr[hi];

        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > arr[lo]) {
            lo = mid;
            continue;
        }

        if (arr[mid] < arr[hi]) {
            hi = mid;
            continue;
        }

        // arr[lo] == arr[mid] == arr[hi]
        while (lo < mid) {
            if (arr[lo] == arr[mid])
                lo++;
            // case : 2 2 1 2 2 2 2 
            else if (arr[lo] < arr[mid])
                return arr[lo];
            // case : 2 3 1 2 2 2 2 
            else  {
                hi = mid;
                break;
            }
        }
        // 若因为 lo == mid 跳出，说明是这种 case
        // 2 2 2 2 1 2 2
        // 那么继续在 mid ~ hi 这个区域做二分
    }
    return arr[lo];
}

void shift(int *arr, int size, int k) 
{
    if (k == 0 || k % size == 0)
        return;

    k %= size;

    int i = 0, j = size - 1;
    while (i < j) 
        swap(arr + i++, arr + j--);

    i = k, j = size - 1;
    while (i < j)
        swap(arr + i++, arr + j--);

    i = 0, j = k - 1;
    while (i < j)
        swap(arr + i++, arr + j--);
}

int main()
{
    int size = 6;
    int *arr = arrayWithRange(size, 0, 3);
    sort(arr, size);
    int k = randWithRange(0, size);
    shift(arr, size, k);
    int res = search_rotate(arr, size);
    printArray(arr, size);
    printf("result = %d\n", res);
    free(arr);
}
