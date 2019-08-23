#include "ds.h"

int str2int(const char *str)
{
    if (!str || !*str)
        return -1;

    long res = 0;
    int sign = 0;

    if (*str < '0' || *str > '9') {
        if (*str == '-')
            sign = 1, str++;
        else if (*str != '+')
            return -1;
        else
            str++;
    }

    for (char *p = (char *)str; *p; p++) {
        if (*p < '0' || *p > '9')
            return -1;
        res = res * 10 + *p - '0';
        if ((!sign && res > 0x7fffffff) ||
             (sign && res > 0x80000000))
           return -1; 
    }
    return sign ? -res : res;
}

int main(int argc, char *argv[])
{
    printf("%d\n", str2int("1234567"));
    printf("%d\n", str2int("2147483647"));
    printf("%d\n", str2int("-2147483648"));
    printf("%d\n", str2int("2147483648"));
    printf("%d\n", str2int("-2147483649"));
    printf("%d\n", str2int("-1234"));
}
