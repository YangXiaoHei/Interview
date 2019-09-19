#include "ds.h"

#ifndef INT_MIN
#define INT_MIN -2147483647-1
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int xabs(int a) { return a < 0 ? -a : a; }

int xdiv(int a, int b)
{
    if (b == 0)
        return 0;

    if (a == INT_MIN && b == -1)
        return INT_MAX;

    unsigned t = a == INT_MIN ? 0x80000000 : xabs(a);
    unsigned d = b == INT_MIN ? 0x80000000 : xabs(b);
    unsigned res = 0;
    for (int i = 31; i >= 0; i--) {
        if ((t >> i) >= d) {
            res |= ((unsigned)1 << i);
            t -= (d << i);
        }
    }
    if (res == 0x80000000)
        return INT_MIN;

    return (a ^ b) < 0 ? -(int)res : (int)res;
}

int main()
{
    printf("%d\n", xdiv(15, 3));
    printf("%d\n", xdiv(-15, 3));
}
