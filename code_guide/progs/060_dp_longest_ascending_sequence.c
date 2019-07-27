#include "ds.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int *get_dp(int *arr, int size, int *maxi)
{
    int *dp = malloc(sizeof(int) * size);
    memset(dp, 0, sizeof(int) * size);
    
    *maxi = 1;
    for (int i = 0; i < size; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + 1);

            if (dp[i] > *maxi)
                *maxi = i;
        }
    }

    return dp;
}

int *longest_ascending_sequence(int *arr, int size, int *reslen)
{
    if (!arr || size <= 0)
        return NULL;

    int idx = 0;
    int *dp = get_dp(arr, size, &idx);
    int len = dp[idx];
    int *res = malloc(sizeof(int) * len);
    int cur = len - 1;
    *reslen = len;
    res[cur--] = arr[idx];
    for (int i = idx - 1; i >= 0; i--) {
        if (arr[i] < arr[idx] && dp[i] == dp[idx] - 1) {
            res[cur--] = arr[i];
            idx = i;
        }
    }
    return res;
}

int main(int argc, char *argv[])
{
    int arr[] = { 2, 1, 5, 3, 6, 4, 8, 9, 7 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, size);
    int reslen = 0;
    int *res = longest_ascending_sequence(arr, size, &reslen);
    printArray(res, reslen);
}
