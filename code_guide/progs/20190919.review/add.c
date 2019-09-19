#include "ds.h"

int add(int a, int b)
{
    int c = 0;
    while (b) {
        c = a ^ b;
        b = (a  & b) << 1;
        a = c;
    }
    return a;
}

int main()
{
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (i + j != add(i, j)) {
                printf("%d %d\n", i, j);
                return -1;
            }
        }
    }
}
