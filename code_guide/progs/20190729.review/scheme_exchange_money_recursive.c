#include "ds.h"

int exchange_money_core(int *money, int size, int idx, int aim)
{
    if (idx >= size) 
        return aim == 0 ? 1 : 0;
    
    int res = 0;
    for (int i = 0; i * money[idx] <= aim; i++) 
        res += exchange_money_core(money, size, idx + 1, aim - i * money[idx]);
    return res;
}

int exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
        return 0;

    return exchange_money_core(money, size, 0, aim);
}

int main(int argc, char *argv[])
{
    int money[] = { 5, 15, 10, 20 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim;
    scanf("%d", &aim);
    int res = exchange_money(money, size, aim);
    printf("res = %d\n", res);
}
