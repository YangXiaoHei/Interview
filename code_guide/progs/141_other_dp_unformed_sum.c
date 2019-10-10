#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_unformed_sum(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int minv = 2147483647;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        minv = min(arr[i], minv);
    }

    int *dp = malloc(sum + 1);
    memset(dp, 0, sum + 1);

    dp[0] = 1;
    for (int i = 0; i < size; i++) {
        for (int j = sum; j >= arr[i]; j--) {
            if (dp[j - arr[i]])
                dp[j] = 1;
        }
    }
    int res = 0;
    for (int i = minv; i <= sum; i++) {
        if (!dp[i]) {
            res = i;
            break;
        }
    }
    free(dp);
    return res;
}

int main()
{
    int arr[] = { 3, 2, 5 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", min_unformed_sum(arr, size));
}
