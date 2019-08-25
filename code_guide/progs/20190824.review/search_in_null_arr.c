#include "ds.h"

int search(const char *arr[], int size, const char *key)
{
    if (!arr || size <= 0 || !key || !*key)
        return -1;

    int lo = 0, hi = size - 1;
    int cmp = 0;
    int res = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (!arr[mid]) {
            int i = mid;
            while (--i >= lo && !arr[i])
                i--;
            if (i < lo || (cmp = strcmp(arr[i], key)) < 0) {
                lo = mid + 1;
            } else {
                res = cmp == 0 ? i : res;
                hi = mid - 1;
            }
        } else {
            cmp = strcmp(arr[mid], key);
            if (cmp >= 0) {
                res = cmp == 0 ? mid : res;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
    }
    return res;
}

int main(int argc, char *argv[])
{
    const char *arr[] = { "1", NULL, "2", NULL, "2", "2", NULL, "2", NULL, "3", NULL, NULL, "4", "5", NULL, NULL, NULL, NULL, "6", NULL, "7", NULL, "8", "9", NULL, NULL };
    int size = sizeof(arr) / sizeof(arr[0]);
    int idx = search(arr, size, argv[1]);
    if (idx >= 0)
        printf("idx=%d string is %s\n", idx, arr[idx]);
    else
        printf("%d\n", idx);
}
