#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_edit_cost(const char *str1, int len1, const char *str2, int len2, int ic, int dc, int rc)
{
    if (!str1 || !str2 || !*str1 || !*str2 || len1 <= 0 || len2 <= 0)
        return 0;

    int *dp = malloc(sizeof(int) * (len2 + 1));
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * (len2 + 1));

    dp[0] = 0;
    for (int i = 1; i <= len2; i++) 
        dp[i] = ic * i; 

    int prev = 0;
    for (int i = 1; i <= len1; i++) {
        prev = dp[0];
        dp[0] = i * dc;
        for (int j = 1; j <= len2; j++) {
            int tmp = dp[j];
            if (str1[i - 1] == str2[j - 1])
                dp[j] = prev;
            else
                dp[j] = prev + rc;

            dp[j] = min(dp[j], dp[j - 1] + ic);
            dp[j] = min(dp[j], tmp + dc);
            prev = tmp;
        }
    }

    int res = dp[len2];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    const char *str1 = "ab12cd3";
    const char *str2 = "abcdf";
    int ic = 5, dc = 3, rc = 2;    
    int res = min_edit_cost(str1, strlen(str1), str2, strlen(str2), ic, dc, rc);
    printf("res = %d\n", res);
}
