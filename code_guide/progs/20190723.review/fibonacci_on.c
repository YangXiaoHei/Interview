#include "ds.h"

long fibonacci(int n)
{
    if (n < 0)
        return 0;

    int arr[] = { 0, 1, 1, 2 };
    if (n <= 3)
        return arr[n];

    long prev = 1, res = 1, tmp = 0;
    for (int i = 3; i <= n; i++) {
        tmp = res;
        res += prev;
        prev = res;
    }
    return res;
}

int main(int argc, char *argv[])
{
    BENCHMARK(
                long res = fibonacci(1000000000);
                printf("res = %ld\n", res);
             );
}
