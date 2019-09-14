#include "ds.h"

int big(int a, int b)
{
    int sa = a >> 31;
    int sb = b >> 31;
    if (sa ^ sb) 
        return (~sa & a) | (~sb & b); 

    int t = a - b;
    t >>= 31;
    return (~t & a) | (t & b);
}

int main()
{
    printf("%d\n", big(1, 3));
    printf("%d\n", big(5, 3));
    printf("%d\n", big(-1, 2147483647));
    printf("%d\n", big(1, -2147483647-1));
    printf("%d\n", big(-1, -2147483647-1));
    printf("%d\n", big(-1, -3));
}
