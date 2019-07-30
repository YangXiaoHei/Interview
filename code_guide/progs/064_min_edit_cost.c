#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_edit_cost(const char *str1, int len1, const char *str2, int len2, int ic, int dc, int rc)
{
    if (!str1 || !str2 || !*str1 || !*str2 || len1 <= 0 || len2 <= 0)
        return 0;

    int *dp = malloc(sizeof(int) * (len1 + 1) * (len2 + 1));
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * (len1 + 1) * (len2 + 1));

    dp[0 * (len2 + 1) + 0] = 0;

    for (int i = 1; i <= len2; i++) 
        dp[0 * (len2 + 1) + i] = ic * i;

    for (int i = 1; i <= len1; i++)
        dp[i * (len2 + 1) + 0] = dc * i;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1])
                dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + j - 1];
            else
                dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + j - 1] + rc;

            dp[i * (len2 + 1) + j] = min(dp[i * (len2 + 1) + j], dp[(i - 1) * (len2 + 1) + j] + dc);
            dp[i * (len2 + 1) + j] = min(dp[i * (len2 + 1) + j], dp[i * (len2 + 1) + j - 1] + ic);
        }
    }

    matrix_print_(dp, len1 + 1, len2 + 1);

    int res = dp[len1 * (len2 + 1) + len2];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int ic = 5, dc = 3, rc = 2;
    const char *str1 = "ab12cd3";
    const char *str2 = "abcdf";
    int cost = min_edit_cost(str1, strlen(str1), str2, strlen(str2), ic, dc, rc);
    printf("cost = %d\n", cost);
}
