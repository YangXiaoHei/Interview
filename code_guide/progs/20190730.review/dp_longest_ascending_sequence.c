#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

void longest_ascending_sequence(int *arr, int size)
{
    int *dp = malloc(sizeof(int) * size);
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * size);
    
    int dpmax = 0;
    dp[0] = 1;
    for (int i = 1; i < size; i++)  {
        dp[i] = 1;
        for (int j = 0; j < i; j++) 
            if (arr[j] <= arr[i]) 
                dp[i] = max(dp[i], dp[j] + 1);
        if (dp[i] > dp[dpmax])
            dpmax = i;
    }

    int len = dp[dpmax];
    int *sequence = malloc(sizeof(int) * len);
    if (!sequence) exit(1);

    int hi = len - 1;
    int idx = dpmax;
    sequence[hi--] = arr[dpmax];
    for (int i = idx - 1; i >= 0; i--) {
        if (arr[i] <= arr[idx] && dp[i] == dp[idx] - 1) {
            sequence[hi--] = arr[i];
            idx = i;
        }
    }

    printArray(sequence, len);

    free(dp);
    free(sequence);
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 20);
    printArray(arr, size);
    longest_ascending_sequence(arr, size);
}
