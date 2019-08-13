#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_edit_cost(const char *str1, const char *str2, int ic, int dc, int rc)
{
    if (!str1 || !str2 || !*str1 || !*str2 || ic < 0 || dc < 0 || rc < 0)
        return -1;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int *dp = malloc(sizeof(int) * (len2 + 1));
    dp[0] = 0;
    int upleft = 0, tmp_upleft = 0;
    for (int i = 1; i <= len2; i++)
        dp[i] = i * ic;

    for (int i = 1; i <= len1; i++) {
        upleft = dp[0]; // 右上角 
        dp[0] = i * dc;
        for (int j = 1; j <= len2; j++) {
            tmp_upleft = dp[j]; // 下一次的右上角
            if (str1[i] != str2[j])
                dp[j] = upleft + rc;
            else
                dp[j] = upleft;

            dp[j] = min(dp[j], dp[j - 1] + ic);
            dp[j] = min(dp[j], tmp_upleft + dc);
            upleft = tmp_upleft;
        }
    }
    int res = dp[len2];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    const char *str1 = "abc123";
    const char *str2 = "adc23";
    int ic = 2, dc = 3, rc = 4;
    printf("%d\n", min_edit_cost(str1, str2, ic, dc, rc));
}
