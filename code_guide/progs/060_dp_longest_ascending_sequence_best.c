#include "ds.h"

int binary_search(int *arr, int size, int key)
{
    int lo = 0, hi = size - 1;
    int ge = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= key)
            lo = mid + 1;
        else {
            ge = mid;
            hi = mid - 1;
        }
    }
    return ge;
}

int *longest_ascending_sequence(int *arr, int size, int *reslen)
{
    if (!arr || size <= 0)
        return 0;

    int *dp = malloc(sizeof(int) * size);
    memset(dp, 0, sizeof(int) * size);

    int *ends = malloc(sizeof(int) * size);
    memset(ends, 0, sizeof(int) * size);

    int hi = 0;
    dp[0] = 1;
    ends[hi++] = arr[0];

    int maxi = 0;
    for (int i = 1; i < size; i++) {
        int ge_idx = binary_search(ends, hi, arr[i]);
        if (ge_idx == -1) {
            ends[hi++] = arr[i];
            dp[i] = hi;
        } else {
            ends[ge_idx] = arr[i];
            dp[i] = ge_idx + 1;
        }
        if (dp[i] > dp[maxi])
            maxi = i;
    }
    free(ends);

    int *res = malloc(sizeof(int) * hi);
    int cur = hi - 1;
    int idx = maxi;
    res[cur--] = arr[maxi];
    for (int i = idx - 1; i >= 0; i--) {
        if (arr[i] <= arr[idx] && dp[i] == dp[idx] - 1) {
            res[cur--] = arr[i];
            idx = i;
        }
    }
    *reslen = hi;
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 1, 30);
    printArray(arr, size);
    int reslen = 0;
    int *res = longest_ascending_sequence(arr, size, &reslen);
    printArray(res, reslen);
}
