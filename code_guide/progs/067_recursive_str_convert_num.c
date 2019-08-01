#include "ds.h"

int str_convert_num(const char *str)
{
    if  (!str)
        return 0;

    if (!*str)
        return 1;

    if (*str == '0')
        return 0;

    int res = 0;
    res = str_convert_num(str + 1);
    if (str[1] && (str[0] - '0') * 10 + str[1] - '0' <= 26)
        res += str_convert_num(str + 2);
    return res;
}

int main(int argc, char *argv[])
{
    printf("%d\n", str_convert_num("123"));
    printf("%d\n", str_convert_num("1101"));
    printf("%d\n", str_convert_num("01"));
    printf("%d\n", str_convert_num("10"));
    printf("%d\n", str_convert_num("9999"));
    printf("%d\n", str_convert_num("1999"));
}
