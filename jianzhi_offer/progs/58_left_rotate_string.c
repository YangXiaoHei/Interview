#include <stdio.h>
#include <string.h>
#include "tool.h"

void reverse_help(char *beg, char *end)
{
    if (beg == end)
        return;

    char *lo = beg < end ? beg : end;
    char *hi = lo == beg ? end : beg;

    while (lo < hi) {
        char t = *lo;
        *lo = *hi;
        *hi = t;
        lo++, hi--;
    }
}

void left_rotate(char *str, int len, int k)
{
    if (!str || !*str || len <= 0 || k < 0)
        return;

    if ((k %= len) == 0)
        return;
    
    reverse_help(str, str + len - 1);
    reverse_help(str, str + len - k - 1);
    reverse_help(str + len - k, str + len - 1);
}

int main(int argc, char *argv[])
{
    char str[] = "12345678";
    int r = randWithRange(1, 30);
    left_rotate(str, strlen(str), r);
    printf("r = %d, result = %s\n", r, str);
}
