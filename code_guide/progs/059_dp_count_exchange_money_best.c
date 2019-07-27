#include "ds.h"

int count_exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
        return 0;

    int *dp = malloc(sizeof(int) * (aim + 1));
    memset(dp, 0, sizeof(int) * (aim + 1));
    if (!dp) exit(1);

    dp[0] = 1;

    for (int i = 1; i * money[0] <= aim; i++)
        dp[i * money[0]] = 1;

    for (int i = 1; i < size; i++) 
        for (int j = 1; j <= aim; j++) 
            if (j - money[i] >= 0)
                dp[j] += dp[j - money[i]];

    matrix_print_(dp, 1, aim + 1);

    int res = dp[aim];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int money[] = { 5, 10, 25, 1 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim = 10;
    printf("aim = %d cnt = %d\n", aim, count_exchange_money(money, size, aim));
}
