#include <stdio.h>
#include <stdlib.h>

int translate_num_to_string_core(char *str, int len)
{
    int *dp = malloc(sizeof(int) * len);
    int cnt = 0;
    dp[len - 1] = 1;
    for (int i = len - 2; i >= 0; i--) {
        int num = (str[i] - '0') * 10 + str[i + 1] - '0';
        if (num >= 10 && num <= 25) 
            dp[i] = dp[i + 1] + ((i != len - 2) ? dp[i + 2] : 1);
        else 
            dp[i] = dp[i + 1];
    }
    int result = dp[0];
    free(dp);
    return result;
}

int translate_num_to_string(int num)
{
    char buf[128];
    int len = snprintf(buf, sizeof(buf), "%d", num);
    return translate_num_to_string_core(buf, len);
}

int main(int argc, char *argv[])
{
    printf("%d\n", translate_num_to_string(123));
    printf("%d\n", translate_num_to_string(126));
    printf("%d\n", translate_num_to_string(9999));
    printf("%d\n", translate_num_to_string(1234));
    printf("%d\n", translate_num_to_string(12211));
}
