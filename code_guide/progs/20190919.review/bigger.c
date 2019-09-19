#include "ds.h"

int bigger(int a, int b)
{
    int sa = a >> 31;
    int sb = b >> 31;
    if (sa ^ sb) 
        return (~sa & a) | (~sb & b);

    int t = a - b;
    t >>= 31;
    return (t & b) | (~t & a);
}

int main()
{
    printf("%d\n", bigger(1, 2));
    printf("%d\n", bigger(2, 1));
    printf("%d\n", bigger(2147483647, -2147483647-1));
    printf("%d\n", bigger(-1, -9));
    printf("%d\n", bigger(-9, -2147483647-1));
}
