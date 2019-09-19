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
    int res = 0;
    unsigned ub = b;
    while (ub) {
        if (ub & 1)
            res = add(res, a);
        a <<= 1; 
        ub >>= 1;
    }
    return res;
}

int main()
{
    printf("%d\n", mul(2, 10));
    printf("%d\n", mul(11, 12));
    printf("%d\n", mul(-11, 12));
}
