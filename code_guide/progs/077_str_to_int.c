#include "ds.h"

int str_to_int(const char *str)
{
    if (!str || !*str)
        return 0;

    int sign = 0;
    if (*str == '-')
        sign = 1;

    while (*str && (*str < '0' || *str > '9'))
        str++;

    if (!*str)
        return -1;

    long res = 0;
    for (char *p = (char *)str; *p && (*p >= '0' && *p <= '9'); p++) {
        res = res * 10 + *p - '0';
        if (!sign && res > 0x7fffffff)
            return 0x7fffffff;
    }
    res = sign ? -res : res;
    if (sign && res > 0x80000000)
        return 0x80000000;
    return res;
}

int main(int argc, char *argv[])
{
    printf("%d\n", str_to_int("12345678"));
    printf("%d\n", str_to_int("-12345678"));
    printf("%d\n", str_to_int("2147483647"));
    printf("%d\n", str_to_int("-2147483648"));
    printf("%d\n", str_to_int("2147483648"));
    printf("%d\n", str_to_int("-2147483649"));
    printf("%d\n", str_to_int("21474836.123"));
}
