#include "ds.h"

int str_convert_num(const char *str)
{
    if (!str || !*str || *str == '0')
        return 0;

    int len = strlen(str);
    int cur = str[len - 1] != '0'; 
    int next = 1;
    for (int i = len - 2; i >= 0; i--) {
        int num = (str[i] - '0') * 10 + str[i + 1] - '0';
        if (num < 10) {
            next = cur;
            cur = 0;
        } else if (num > 26) {
            next = cur;
        } else {
            int tmp = cur;
            cur += next;
            next = tmp;
        }
    }
    return cur;
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
