#include "ds.h"

int xpow(int n, int exp)
{
    if (exp < 0)
        return -1;

    int base = n;
    int res = 1;
    while (exp) {
        if (exp & 1)
            res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

int convert(char *arr, int size, const char *str, int len)
{
    int *help = malloc(256);
    memset(help, 0, 256);
    for (int i = 0; i < size; i++) {
        help[arr[i]] = i + 1;
    }
    int res = 0;
    for (int i = len - 1; i >= 0; i--) {
        res += help[str[len - i - 1]] * xpow(size, i);
    }
    free(help);
    return res; 
}

int main()
{
    char arr[] = { 'A', 'B', 'C', 'D' };
    int size = sizeof(arr) / sizeof(arr[0]);
    char str[128];
    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        printf("%d\n", convert(arr, size, str, len));
    } 
}
