#include "ds.h"

int big(int a, int b)
{
    if ((a >> 31) ^ (b >> 31)) {
        return a >> 31 ? b : a;
    } else {
        int t = a - b;
        t >>= 31;
        return (~t & a) | (t & b);
    }
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
