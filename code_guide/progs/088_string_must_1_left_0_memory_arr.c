#include "ds.h"

long must_1_left_0_core(int i, int n, ht *h)
{
    if (i == n)
        return 1;

    if (i == n - 1)
        return 2;

    if (ht_contain(h, i))
        return ht_get(h, i);

    long res1 = 0;
    if (ht_contain(h, i + 1))
        res1 = ht_get(h, i + 1);
    else {
        res1 = must_1_left_0_core(i + 1, n, h);
        ht_insert(h, i + 1, res1);
    }

    long res2 = 0;
    if (ht_contain(h, i + 2))
        res2 = ht_get(h, i + 2);
    else {
        res2 = must_1_left_0_core(i + 2, n, h);
        ht_insert(h, i + 2, res2);
    }

    long res = res1 + res2;
    ht_insert(h, i, res);
    return res;
}

long must_1_left_0(int n)
{
    ht *h = ht_create();
    long res = must_1_left_0_core(1, n, h); 
    ht_release(&h);
    return res;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 80; i++)
        printf("res(%d) = %-3ld\n", i, must_1_left_0(i));
}
