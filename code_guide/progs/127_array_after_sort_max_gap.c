#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int max_gap(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int min_num = arr[0], max_num = arr[0];
    for (int i = 1; i < size; i++) {
        min_num = min(arr[i], min_num); 
        max_num = max(arr[i], max_num); 
    }

    if (min_num == max_num)
        return 0;

    int nbucket = size + 1;
    int *maxs = malloc(sizeof(int) * nbucket);
    int *mins = malloc(sizeof(int) * nbucket);
    int *has = malloc(sizeof(int) * nbucket);
    memset(has, 0, sizeof(int) * nbucket);

    for (int i = 0; i < size; i++) {
        int b = (int)((arr[i] - min_num * 1.0) * size / (max_num - min_num));
        maxs[b] = has[b] ? max(maxs[b], arr[i]) : arr[i];
        mins[b] = has[b] ? min(mins[b], arr[i]) : arr[i];
        has[b] = 1; 
    }

    int res = -2147483647-1;
    int lastmax = 0;
    int i = 0;
    while (i <= size) {
        if (has[i++]) {
            lastmax = maxs[i - 1];
            break;
        } 
    }

    for (; i <= size; i++) {
        if (has[i]) {
            res = max(res, mins[i] - lastmax);
            lastmax = maxs[i];
        }
    }
    free(maxs);
    free(mins);
    free(has);
    return res;
}

int main()
{
    {
        int arr[] = { 9, 3, 1, 10 };
        int size = sizeof(arr) / sizeof(arr[0]);
        printf("%d\n", max_gap(arr, size));
    }
    {
        int arr[] = { 5, 5, 5, 5 };
        int size = sizeof(arr) / sizeof(arr[0]);
        printf("%d\n", max_gap(arr, size));
    }
}
