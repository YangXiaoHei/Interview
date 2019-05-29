#include <stdio.h>

int overflow(unsigned long x, unsigned long y)
{
    unsigned long sum = x + y;
    return sum < y;
}

unsigned long fibonacci(unsigned x, int *o)
{
    if (x <= 0) return 0;
    if (x == 1) return 1;

    unsigned long pre = 0, cur = 1;
    unsigned long next = 0;
    for (unsigned i = 2; i <= x; i++) {
        if (overflow(pre, cur)) {
            if (o) *o = 1;
            break;
        }
        next = pre + cur;
        pre = cur;
        cur = next;
    }
    return next;
}

int main(int argc, char *argv[])
{
    int overflow = 0;
    for (int i = 0; i < 100 && !overflow; i++) {
        printf("fibonacci(%-2d) = %20lu\n", i, fibonacci(i, &overflow));
    }
}
