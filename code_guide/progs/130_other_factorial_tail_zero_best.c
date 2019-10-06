#include "ds.h"

int zero(int n)
{
    if (n < 5)
        return 0;

    int res = 0;
    while (n) {
        n /= 5;
        res += n;
    }
    return res;
}

int main()
{
    for (int i = 1; i <= 100; i++) {
        printf("%d! tail zero %d\n", i, zero(i));
    }
}
