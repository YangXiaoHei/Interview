#include "ds.h"

int count_exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
        return 0;

    int *dp = malloc(sizeof(int) * size * (aim + 1));
    memset(dp, 0, sizeof(int) * size * (aim + 1));
    for (int i = 0; i < size; i++)
        dp[i * (aim + 1) + 0] = 1;

    for (int i = 1; i * money[0] <= aim; i++)
        dp[0 * (aim + 1) + i * money[0]] = 1;

    for (int i = 1; i < size; i++) {
        for (int j = 1; j <= aim; j++) {
            int num = 0;
            for (int k = 0; k * money[i] <= j; k++)
                num += dp[(i - 1) * (aim + 1) + j - k * money[i]];
            dp[i * (aim + 1) + j] = num;
        }
    }

    matrix_print_(dp, size, aim + 1);
    int res = dp[(size - 1) * (aim + 1) + aim];
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
