#include "ds.h"

long fibonacci(int n)
{
    if (n <= 1)
        return 1;

    long prev = 1, cur = 1, next = 2;
    for (int i = 2; i < n; i++) {
        prev = cur;
        cur = next;
        next = prev + cur;
    }
    return next;
}

int main(int argc, char *argv[])
{
    int i = 100000000;
    BENCHMARK(
                printf("fibonacci(%d) = %-3ld\n", i, fibonacci(i));
            );
}
