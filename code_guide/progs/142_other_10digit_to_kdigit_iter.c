#include "ds.h"

int xpow(int k, int exp)
{
    if (exp < 0)
        return -1;

    int res = 1;
    int base = k;
    while (exp) {
        if (exp & 1)
            res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

char* kdigit(int N, int k)
{
    int size = 0;
    for (size = 0; xpow(k, size) <= N; ++size);

    char *arr = malloc(size + 1);
    int idx = 0;
    while (N) {
        arr[idx++] = N % k + '0';
        N /= k;
    }
    arr[idx] = 0;

    int i = 0, j = idx - 1;
    while (i < j) {
        char t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
        i++, j--;
    }
    return arr;
}

int main()
{
    printf("%s\n", kdigit(72, 3));
    printf("%s\n", kdigit(72, 4));
    printf("%s\n", kdigit(72, 5));
    printf("%s\n", kdigit(72, 6));
    printf("%s\n", kdigit(72, 7));
}
