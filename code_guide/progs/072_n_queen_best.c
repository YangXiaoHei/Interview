#include "ds.h"

int n_queen_core(int n, unsigned a, unsigned b, unsigned c)
{
    if (b == (1 << n) - 1) 
        return 1;

    unsigned mask = (1 << n) - 1;
    unsigned d = ~(a | b | c);
    d &= mask;

    int res = 0;
    while (d) {
        unsigned ok = d & -d;
        res += n_queen_core(n, (a | ok) << 1, b | ok, (c | ok) >> 1);
        d -= ok;
    }
    return res;
}

int n_queen(int n)
{
    if (n < 0 || n >= 32)
        return 0;

    if (n == 1)
        return 1;

    return n_queen_core(n, 0, 0, 0);
}

int main(int argc, char *argv[])
{
    printf("%d\n", n_queen(16)); 
}
