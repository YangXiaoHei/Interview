#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int valid(const char *beg, const char *end)
{
    int status = 0;
    for (char *p = (char *)beg; p != end; p++) {
        if (*p != ')' && *p != '(')
            return 0;

        if (*p == ')' && --status < 0)
            return 0;

        if (*p == '(')
            status++;
    }
    return status == 0;
}

int longest_pair(const char *str)
{
    if (!str || !*str)
        return 0;

    int len = strlen(str);
    int *dp = malloc(sizeof(int) * len);
    memset(dp, 0, sizeof(int) * len);
    int res = 0;
    for (int i = 1; i < len; i++) {
        if (str[i] == ')') {
            int pre = i - dp[i - 1] - 1;
            if (pre >= 0 && str[pre] == '(')
                dp[i] = dp[i - 1] + 2 + (pre > 0 ? dp[pre - 1] : 0);
        }
        res = max(res, dp[i]);
    }
    free(dp);

    char buf[100];
    for (int i = 0; i <= len - res; i++) {
        if (valid(str + i, str + i + res)) {
            memcpy(buf, str + i, res);
            buf[res] = 0;
            printf("%s\n", buf);
            break;
        }
    } 
    return res;
}

int main(int argc, char *argv[])
{
    printf("%d\n", longest_pair(")()()((("));
    printf("%d\n", longest_pair("))()(())()"));
}
