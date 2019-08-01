#include "ds.h"

int str_convert_num(const char *str)
{
    if (!str || !*str || *str == '0')
        return 0;

    int len = strlen(str);
    int *dp = malloc(sizeof(int) * len);
    memset(dp, 0, sizeof(int) * len);

    dp[len - 1] = str[len - 1] != '0';

    for (int i = len - 2; i >= 0; i--) {
        int num = (str[i] - '0') * 10 + str[i + 1] - '0';
        if (num < 10)
            dp[i] = 0;
        else if (num > 26)
            dp[i] = dp[i + 1];
        else
            dp[i] = dp[i + 1] + (i == len - 2 ? 1 : dp[i + 2]); 
    }
    int res = dp[0];
    free(dp);
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
