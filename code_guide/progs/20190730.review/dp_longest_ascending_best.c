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

void longest_asc_seq(int *arr, int size)
{
    int *dp = malloc(sizeof(int) * size);
    if (!dp) exit(1);

    int *ends = malloc(sizeof(int) * size);
    if (!ends) exit(1);
    int hi = 0;

    dp[0] = 1;
    ends[hi++] = arr[0];

    int dpmax = 0;
    for (int i = 1; i < size; i++) {
        int geidx = binary_search(ends, hi, arr[i]);
        if (geidx == -1) {
            ends[hi++] = arr[i];
            dp[i] = hi;
        } else {
            ends[geidx] = arr[i];
            dp[i] = geidx + 1;
        }

        if (dp[i] > dp[dpmax])
            dpmax = i;
    }

    int len = dp[dpmax];
    int *seq = malloc(sizeof(int) * len);
    int cur = len - 1;
    int idx = dpmax;
    seq[cur--] = arr[idx];
    for (int i = idx - 1; i >= 0; i--) {
        if (arr[i] <= arr[idx] && dp[i] == dp[idx] - 1) {
            seq[cur--] = arr[i]; 
            idx = i;
        }
    }
    printArray(seq, len);
    free(seq);
    free(dp);
    free(ends);
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 20);
    printArray(arr, size);
    longest_asc_seq(arr, size);
}
