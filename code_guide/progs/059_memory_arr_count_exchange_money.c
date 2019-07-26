#include "ds.h"

void xprint(int *a, int r, int c)
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%3d", a[i * c + j]);
        printf("\n");
    }
}

int count_exchange_money_core(int *money, int size, int idx, int aim, int *map, int r, int c)
{
    if (idx >= size) {
        map[idx * c + aim] = aim == 0 ? 1 : -1;
        return aim == 0 ? 1 : 0;
    }

    int res = 0;
    for (int i = 0; i * money[idx] <= aim; i++) {
        int t = map[(idx + 1) * c + aim - i * money[idx]];
        if (t != 0)
            res += (t == -1 ? 0 : t);
        else
            res += count_exchange_money_core(money, size, idx + 1, aim - i * money[idx], map, r, c);
    }

    map[idx * c + aim] = res == 0 ? -1 : res;
    return res;
}

int count_exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
        return 0;

    int *map = malloc(sizeof(int) * (size + 1) * (aim + 1));
    memset(map, 0, sizeof(int) * (size + 1) * (aim + 1));
    int res = count_exchange_money_core(money, size, 0, aim, map, size + 1, aim + 1);
    xprint(map, size + 1, aim + 1);
    free(map);
    return res;
}

int main(int argc, char *argv[])
{
    int money[] = { 5, 10, 25, 1 };
    int aim = 10;
    int size = sizeof(money) / sizeof(money[0]);
    printf("%d\n", count_exchange_money(money, size, aim));
}
