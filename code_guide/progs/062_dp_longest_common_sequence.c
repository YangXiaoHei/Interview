#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int *get_dp(const char *str1, int len1, const char *str2, int len2)
{
    int *dp = malloc(sizeof(int) * len1 * len2);
    memset(dp, 0, sizeof(int) * len1 * len2);
    
    dp[0 * len2 + 0] = str1[0] == str2[0] ? 1 : 0;
    for (int i = 1; i < len1; i++) 
        dp[i * len2 + 0] = max(dp[(i - 1) * len2 + 0], str1[i] == str2[0] ? 1 : 0);

    for (int i = 1; i < len2; i++)
        dp[0 * len2 + i] = max(dp[0 * len2 + i - 1], str2[i] == str1[0] ? 1 : 0);

    for (int i = 1; i < len1; i++) {
        for (int j = 1; j < len2; j++) {
            dp[i * len2 + j] = max(dp[(i - 1) * len2 + j], dp[i * len2 + j - 1]);
            if (str1[i] == str2[j])
                dp[i * len2 + j] = max(dp[i * len2 + j], dp[(i - 1) * len2 + j - 1] + 1);
        }
    }
    return dp;
}

char *longest_common_str(const char *str1, int len1, const char *str2, int len2)
{
    if (!str1 || !str2 || len1 <= 0 || len2 <= 0)
        return NULL;

    int *dp = get_dp(str1, len1, str2, len2);

    matrix_print_(dp, len1, len2);

    int maxlen = dp[(len1 - 1) * len2 + len2 - 1];
    char *lstr = malloc(maxlen + 1);
    memset(lstr, 0, maxlen + 1);

    int idx = maxlen - 1;
    int i = len1 - 1;
    int j = len2 - 1;
    while (idx >= 0) {
        int v = dp[i * len2 + j];
        if (i > 0 && v == dp[(i - 1) * len2 + j])
            i--;
        else if (j > 0 && v == dp[i * len2 + j - 1])
            j--;
        else {
            lstr[idx--] = str1[i];
            i--;
            j--; 
        }
    }
    free(dp);
    return lstr;
}

int main(int argc, char *argv[])
{
    const char *str1 = "1A2C3D4B56";
    printf("%s\n", str1);
    int len1 = strlen(str1);
    const char *str2 = "B1D23CA45B6A";
    printf("%s\n", str2);
    int len2 = strlen(str2);
    char *str = longest_common_str(str1, len1, str2, len2);
    printf("%s\n", str);
}
