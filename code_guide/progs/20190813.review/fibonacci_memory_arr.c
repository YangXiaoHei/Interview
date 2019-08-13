#include "ds.h"

long fibonacci_core(int n, ht *h)
{
    if (n <= 1)
        return 1;

    if (ht_contain(h, n))
        return ht_get(h, n);

    long res1 = 0;
    if (ht_contain(h, n - 1))
        res1 = ht_get(h, n - 1);
    else {
        res1 = fibonacci_core(n - 1, h);
        ht_insert(h, n - 1, res1);
    }

    long res2 = 0;
    if (ht_contain(h, n - 2))
        res2 = ht_get(h, n - 2);
    else {
        res2 = fibonacci_core(n - 2, h);
        ht_insert(h, n - 2, res2);
    }

    long res = res1 + res2;
    ht_insert(h, n, res);
    return res;
}

long fibonacci(int n)
{
    ht *h = ht_create();
    long res = fibonacci_core(n, h);
    ht_release(&h);
    return res;
}

int main(int argc, char *argv[])
{
    int i = 100000; // 再多就栈溢出了
    BENCHMARK(
                printf("fibonacci(%d) = %-3ld\n", i, fibonacci(i));
            );
}
