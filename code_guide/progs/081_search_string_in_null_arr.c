#include "ds.h"

int search(char *arr[], int size, char *target)
{
    if (!arr || size <= 0 || !target || !*target)
        return -1;

    int lo = 0, hi = size - 1;
    int mid = 0;
    int res = -1;
    int cmp = 0;
    int i = 0;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (arr[mid]) {
            if ((cmp = strcmp(arr[mid], target)) == 0) {
                res = mid;
                hi = mid - 1;
            } else if (cmp > 0) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } else {
            i = mid;
            while (!arr[i] && --i >= lo);
            if (i < lo || (cmp = strcmp(arr[i], target)) < 0) {
                lo = mid + 1;
            } else {
                res = cmp == 0 ? i : res; 
                hi = mid - 1;
            }
        }
    }
    return res;
}

int main(int argc, char *argv[])
{
    char *arr[] = { "1", NULL, "2", NULL, "2", "2", NULL, "2", NULL, "3", NULL, NULL, "4", "5", NULL, NULL, NULL, NULL, "6", NULL, "7", NULL, "8", "9", NULL, NULL };
    int size = sizeof(arr) / sizeof(arr[0]);
    int idx = search(arr, size, argv[1]);
    if (idx >= 0)
        printf("idx=%d string is %s\n", idx, arr[idx]);
    else
        printf("%d\n", idx);
}
