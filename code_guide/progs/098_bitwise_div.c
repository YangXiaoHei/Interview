#include "ds.h"

#ifndef INT_MIN
#define INT_MIN (-2147483647-1)
#endif

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

int sub(int a, int b)
{
    return add(a, add(~b, 1));
}

int mul(int a, int b)
{
    int t = 0;
    int c = 0;
    unsigned ub = (unsigned)b;
    while (ub) {
        t = (((int)(ub & 1) << 31) >> 31); 
        t &= a;
        c = add(c, t);
        a <<= 1;
        ub >>= 1;
    }
    return c;
}

int xdiv_core(int a, int b)
{
    int sa = (a >> 31) & 1;
    int sb = (b >> 31) & 1;
    a = sa ? add(~a, 1) : a;
    b = sb ? add(~b, 1) : b;

    int c = 0;
    for (int i = 31; i >= 0; i = sub(i, 1)) {
        if ((a >> i) >= b) {
            c |= (1 << i);
            a = sub(a, b << i);
        }
    }
    return sa ^ sb ? add(~c, 1) : c;
}

int xdiv(int a, int b)
{
    if (b == 0)
        return 0;

    if (a == INT_MIN && b == INT_MIN)
        return 1;

    if (b == INT_MIN)
        return 0;

    if (a == INT_MIN) {
        int rest = xdiv_core(add(a, 1), b);
        return add(rest, xdiv_core(sub(a, mul(rest, b)), b));
    }

    return xdiv_core(a, b);
}

int main()
{
    int a = INT_MIN;
    for (int b = 1; b < 10000; b++)  {
        if (a / b != xdiv(a, b)) {
            printf("a=%d b=%d\n", a, b);
            break;
        }
    }

    for (int i = -1000; i <= 1000; i++) {
        for (int j = -1000; j <= 1000; j++) {
            if (j == 0)
                continue;
            printf("i=%d j=%d\n", i, j);
            if (i / j != xdiv(i, j)) {
                printf("error i=%d j=%d\n", i, j);
                return -1;
            }
        }
    } 
}
