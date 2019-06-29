#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

typedef enum EN_ERR  {
    EN_ERR_OVERFLOW = 1,
    EN_ERR_INVALID_CHAR = 2
} EN_ERR;


int err_occur = 0;
int str_to_int_core(const char *str, int sign)
{
    long sum = 0;
    for (; *str; str++) {
        if (*str < '0' || *str > '9') {
            err_occur = EN_ERR_INVALID_CHAR;
            break;
        }

        sum = sum * 10 + *str - '0';
        if ((sign == 1 && sum > 0x7fffffff) || (sign == -1 && sum > 0x80000000)) {
            err_occur = EN_ERR_OVERFLOW;
            break;
        }
    }
    return !*str ? sum : 0;
}

int str_to_int(const char *str)
{
    err_occur = 0;
    int sign = 0;
    char c = *str;

    if (c >= '0' && c <= '9') {
        sign = 1;
    } else if (c == '+') {
        sign = 1;
        ++str;
    } else if (c == '-') {
        sign = -1;
        ++str;
    } else {
        err_occur = EN_ERR_INVALID_CHAR;
        return 0;
    }
    int result = str_to_int_core(str, sign);
    return result * sign;
}

int main(int argc, char *argv[])
{
    // 随机测试数据
    {
        int r = randWithRange(1000, 10000000);
        char buf[64];
        snprintf(buf, sizeof(buf), "%d", r);
        printf("r = %-3d, result = %-10d\n", r,  str_to_int(buf));
    }

    // 溢出测试
    {
        char *buf = "2147483648";
        printf("r = %s, result = %-10d\n", buf, str_to_int(buf));
        if (err_occur) 
            printf("err = %d\n", err_occur);

        buf = "-2147483648";
        printf("r = %s, result = %-10d\n", buf, str_to_int(buf));
        if (err_occur) 
            printf("err = %d\n", err_occur);

        buf = "-2147483649";
        printf("r = %s, result = %-10d\n", buf, str_to_int(buf));
        if (err_occur) 
            printf("err = %d\n", err_occur);
    }
}
