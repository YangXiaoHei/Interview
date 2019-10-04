#include "ds.h"

int zero(int n)
{
    int res = 0;
    for (int i = 5; i <= n; i += 5) {
        int cur = i;
        while (cur % 5 == 0) {
            res++;
            cur /= 5;
        }
    }
    return res;
}

int main()
{
    for (int i = 1; i <= 100; i++) {
        printf("%d! tail zero = %d\n", i, zero(i));
    }
}
