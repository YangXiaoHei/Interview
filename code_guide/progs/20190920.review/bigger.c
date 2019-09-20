#include "ds.h"

int bigger(int a, int b)
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

}
