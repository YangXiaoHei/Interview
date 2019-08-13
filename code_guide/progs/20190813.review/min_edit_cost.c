#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_edit_cost(const char *str1, const char *str2, int ic, int dc, int rc)
{
    if (!str1 || !str2 || !*str1 || !*str2 || ic < 0 || dc < 0 || rc < 0)
        return -1;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int *dp = malloc(sizeof(int) * (len1 + 1) * (len2 + 1));

    dp[0 * (len2 + 1) + 0] = 0;
    for (int i = 1; i <= len2; i++)
        dp[0 * (len2 + 1) + i] = ic * i;

    for (int i = 1; i <= len1; i++)
        dp[i * (len2 + 1) + 0] = dc * i;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i] != str2[j])
                dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + j - 1] + rc;
            else
                dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + j - 1];

            dp[i * (len2 + 1) + j] = min(dp[i * (len2 + 1) + j], dp[(i - 1) * (len2 + 1) + j] + dc);
            dp[i * (len2 + 1) + j] = min(dp[i * (len2 + 1) + j], dp[i * (len2 + 1) + j - 1] + ic);
        }
    }

    int res = dp[len1 * (len2 + 1) + len2];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    const char *str1 = "abc";
    const char *str2 = "adc";
    int ic = 2, rc = 100, dc = 5;
    printf("%d\n", min_edit_cost(str1, str2, ic, dc, rc));
}
