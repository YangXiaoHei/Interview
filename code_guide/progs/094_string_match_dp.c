#include "ds.h"

int match(const char *str, const char *exp)
{
    if (!str || !exp)
        return 0;

    int slen = strlen(str), elen = strlen(exp);
    if (slen == 0 && elen == 0)
        return 1;

    int *dp = malloc(sizeof(int) * (slen + 1) * (elen + 1));
    memset(dp, 0, sizeof(int) * (slen + 1) * (elen + 1));

    // init dp
    dp[slen * (elen + 1) + elen] = 1;
    for (int j = elen - 2; j >= 0; j -= 2) 
        if (exp[j] != '*' && exp[j + 1] == '*')
            dp[slen * (elen + 1) + j] = 1;
        else
            break;

    // init dp
    if (elen > 0 && slen > 0)
        if (exp[elen - 1] == '.' || exp[elen - 1] == str[slen - 1])
            dp[(slen - 1) * (elen + 1) + elen - 1] = 1;

    for (int i = slen - 1; i >= 0; i--) {
        for (int j = elen - 2; j >= 0; j--) {
            if (exp[j + 1] != '*')
                dp[i * (elen + 1) + j] = (str[i] == exp[j] || exp[j] == '.') &&
                                         dp[(i + 1) * (elen + 1) + j + 1];
            else {
                int si = i;
                while (si != slen && (exp[j] == str[i] || exp[j] == '.')) {
                    if (dp[si * (elen + 1) + j + 2]) {
                        dp[i * (elen + 1) + j] = 1;
                        break;
                    }
                    si++;
                }
                if (!dp[i * (elen + 1) + j])
                    dp[i * (elen + 1) + j] = dp[si * (elen + 1) + j + 2];
            }
        }
    }
    /* matrix_print_(dp, elen + 1, slen + 1); */
    int res = dp[0 * (elen + 1) + 0];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    printf("%d\n", match("abc", "abc"));
    printf("%d\n", match("abc", "a.c"));
    printf("%d\n", match("abc", ".*"));
    printf("%d\n", match("abc", ".*.*c"));
    printf("%d\n", match("abc", "x*.*.*b*c*"));
}
