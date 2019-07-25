#include "ds.h"

int count_exchange_money_core(int *money, int size, int idx, int aim)
{
    if (idx >= size) 
        return aim == 0 ? 1 : 0;

    int res = 0;
    for (int i = 0; i * money[idx] <= aim; i++)
        res += count_exchange_money_core(money, size, idx + 1, aim - money[idx] * i);

    return res;
}

int count_exchange_money(int *money, int size, int aim)
{
    return count_exchange_money_core(money, size, 0, aim);
}

int main(int argc, char *argv[])
{
    int money[] = { 5, 10, 25, 1 };
    int size = sizeof(money) / sizeof(money[0]);
    int k = randWithRange(0, 100);
    k = 10;
    printArray(money, size);
    printf("aim = %d\n", k);
    printf("total scheme count = %d\n", count_exchange_money(money, size, k));
}
