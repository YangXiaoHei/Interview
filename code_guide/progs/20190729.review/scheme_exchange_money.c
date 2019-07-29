#include "ds.h"

int exchange_money(int *money, int size, int aim)
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
            dp[i * (aim + 1) + j] = dp[(i - 1) * (aim + 1) + j];
            if (j - money[i] >= 0)
                dp[i * (aim + 1) + j] += dp[i * (aim + 1) + j - money[i]];
        }
    }
    int res = dp[(size - 1) * (aim + 1) + aim];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int money[] = { 1, 5, 15, 20, 10 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim;
    scanf("%d", &aim);
    int res = exchange_money(money, size, aim);
    printf("res = %d\n", res);
}
