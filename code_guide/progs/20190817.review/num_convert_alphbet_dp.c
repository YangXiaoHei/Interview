#include "ds.h"

int num_convert_alphbet(const char *num)
{
    if (!num || !*num)
        return 0;

    if (num[0] == '0')
        return 0;

    int len = strlen(num);

    // 45086

    // dp[i] 表示以 num[i] 结尾的子串可以转换的组合数
    // dp[0] = 1 
    // dp[i] = dp[i - 1] -> 算作一种
    // 如果 dp[i] 和 dp[i - 1] 能组合成一个字母, 那么 dp[i] += dp[i - 2]
    // 最后 dp[len - 1] 即为所求
    // 对于 0 要单独处理
    int *dp = malloc(sizeof(int) * len);
    memset(dp, 0, sizeof(int) * len);
    dp[0] = 1;
    for (int i = 1; i < len; i++) {
        dp[i] = dp[i - 1];
        int n = (num[i - 1] - '0') * 10 + num[i] - '0';

        if (n == 0)  {
            dp[i] = 0; // 修正
        } else if (n < 10) { // 01, 02 ...
            dp[i] = i == 1 ? 0 : dp[i - 1];
        } else if (num[i] == '0') { // 10 20 30 40 ...
            if (n == 10 || n == 20) {
                dp[i] = i == 1 ? 1 : dp[i - 2];
            } else {
                dp[i] = 0;
                break;
            }
        } else if (n >= 11 && n <= 26) {  // 11 ~ 26
            dp[i] += i == 1 ? 1 : dp[i - 2]; 
        } 
    }
    int res = dp[len - 1];
    free(dp);
    return res;
}

int check(const char *num)
{
    if (!num)
        return 0;

    if (!*num)
        return 1;

    if (*num == '0')
        return 0;

    int res = check(num + 1);
    if (num[1] && (*num - '0') * 10 + num[1] - '0' <= 26)
        res += check(num + 2);
    return res;
}

char *gen_case(int len)
{
    char *str = malloc(len + 1);
    for (int i = 0; i < len; i++)
        str[i] = randWithRange(0, 10) + '0';
    str[len] = 0;
    return str;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 1000; i++) {
        char *str = gen_case(5);
        int n1 = num_convert_alphbet(str);
        int n2 = check(str);
        if (n1 != n2) {
            printf("n1 = %d n2 = %d %s\n", n1, n2, str);
            break;
        }
    }
}
