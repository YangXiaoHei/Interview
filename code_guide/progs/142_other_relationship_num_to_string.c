#include "ds.h"

int xpow(int n, int k)
{
    int res = 1;
    int base = n;
    while (k) {
        if (k & 1)
            res *= base;
        base *= base;
        k >>= 1;
    }
    return res;
}

int fun(int num, int k)
{
    int cnt;
    for (cnt = 1; cnt * k <= num; cnt++);
    return cnt - 1;
}

char* convert(char *arr, int k, int num)
{
    int i = 0;
    while (num >= xpow(k, i)) {
        num -= xpow(k, i++);
    }

    char *res = malloc(i + 1);
    memset(res, 0, i + 1);
    res[i] = 0;
    int width = i;
    i--;
    while (num) {
        int cnt = fun(num, xpow(k, i));
        res[width - i - 1] += cnt;
        num -= cnt * xpow(k, i);
        i--;
    }
    for (int i = 0; i < width; i++) {
        res[i] = arr[res[i]];
    }
    return res; 
}

int main()
{
    char arr[] = { 'A', 'B', 'C', 'D' };
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 1; i < 100; i++) {
        printf("i=%-4d --- %s\n", i, convert(arr, size, i));
    }
}
