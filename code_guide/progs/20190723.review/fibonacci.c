#include "ds.h"

long fibonacci(int n)
{
    if (n < 0)
        return 0;

    int arr[] = { 0, 1, 1, 2 };
    if (n <= 3)
        return arr[n];

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 40; i++)
        printf("fibonacci(%d) = %ld\n", i, fibonacci(i));
}
