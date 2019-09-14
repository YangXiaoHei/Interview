#include "ds.h"

int add(int a, int b)
{
    int c = 0;
    while (b) {
        c = a ^ b;
        b = (a & b) << 1;
        a = c;
    }
    return a;
}

int mul(int a, int b)
{
    int c = 0;
    int t;
    unsigned ub = (unsigned)b;
    while (ub) {
        t = ((int)(ub & 1) << 31) >> 31;
        t &= a;
        c = add(c, t);
        a <<= 1;
        ub >>= 1;
    }
    return c;
}

int main()
{
    for (int i = -100; i <= 100; i++) {
        for (int j = -100; j <= 100; j++) {
            if (i * j != mul(i, j)) {
                printf("error i=%d j=%d\n", i, j);
                return -1;
            }
        }
    }
}
