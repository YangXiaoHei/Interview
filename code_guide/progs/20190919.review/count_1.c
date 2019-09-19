#include "ds.h"

int count_1(int a)
{
    unsigned ua = a;
    ua = (ua & 0x55555555) + ((ua >> 1) & 0x55555555);
    ua = (ua & 0x33333333) + ((ua >> 2) & 0x33333333);
    ua = (ua & 0x0f0f0f0f) + ((ua >> 4) & 0x0f0f0f0f);
    ua = (ua & 0x00ff00ff) + ((ua >> 8) & 0x00ff00ff);
    ua = (ua & 0x0000ffff) + ((ua >> 16) & 0x0000ffff);
    return ua;
}

int main()
{
    for (int i = 0; i < 20; i++)
        printf("%d\n", count_1(i));
}
