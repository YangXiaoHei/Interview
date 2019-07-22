#include "ds.h"

long fast_pow(long x, long p)
{
    long tmp = x;
    long res = 1;
    while (p) {
        if (p & 1)
            res *= tmp;
        tmp *= tmp;
        p >>= 1;
    }
    return res;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 20; i++)
        printf("2^%d = %ld\n", i, fast_pow(2, i));
}
