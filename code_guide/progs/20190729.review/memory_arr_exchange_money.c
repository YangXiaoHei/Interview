#include "ds.h"

int exchange_money_core(int *money, int size, int idx, int aim, int *map, int r, int c)
{
    if (idx >= size) {
        map[idx * c + aim] = aim == 0 ? 1 : -1;
        return aim == 0 ? 1 : 0;
    }

    int res = 0;
    for (int i = 0; i * money[idx] <= aim; i++) {
        int v = map[idx * c + aim];
        if (v != 0) 
            res += v == -1 ? 0 : v;
        else 
            res += exchange_money_core(money, size, idx + 1, aim - i * money[idx], map, r, c);
    } 
    map[idx * c + aim] = res == 0 ? -1 : res;
    return res;
}

int exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
        return 0;

    int *map = malloc(sizeof(int) * (size + 1) * (aim + 1));
    memset(map, 0, sizeof(int) * (size + 1) * (aim + 1));
    int res = exchange_money_core(money ,size, 0, aim, map, size + 1, aim + 1);
    free(map);
    return res;
}

int main(int argc, char *argv[])
{
    int money[] = { 10, 15, 20, 1 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim;
    scanf("%d", &aim);
    int res = exchange_money(money, size, aim);
    printf("res = %d\n", res);    
}
