#include "ds.h"

int jump_game(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;

    // 合法性校验
    for (int i = 0; i < size; i++)
        if (arr[i] <= 0)
            return 0;

    int *dp = malloc(sizeof(int) * size);
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * size);

    dp[0] = 0;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (i - j <= arr[j]) {
                dp[i] = dp[j] + 1;
                break;
            }
        }
    }

    int res = dp[size - 1];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int card[] = { 3, 2, 3, 1, 1, 4 };
    int size = sizeof(card) / sizeof(card[0]);
    printArray(card, size);
    printf("%d\n", jump_game(card, size));
}
