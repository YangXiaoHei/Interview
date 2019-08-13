#include "ds.h"

long fibonacci(int n)
{
    if (n <= 1)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 100; i++)
        printf("fibonacci(%d) = %-3ld\n", i, fibonacci(i));
}
