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

int main()
{
    for (int i = -1000; i <= 1000; i++) {
        for (int j = -1000; j <= 1000; j++) {
            if (i + j != add(i, j)) {
                printf("i=%d j=%d\n", i, j);
                return -1;
            }
        }
    }
}
