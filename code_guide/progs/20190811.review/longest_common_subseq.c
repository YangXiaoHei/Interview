#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

void longest_common_subseq(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return;

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int *dp = malloc(sizeof(int) * len1 * len2);
    memset(dp, 0, sizeof(int) * len1 * len2);

    dp[0 * len2 + 0] = str1[0] == str2[0];
    for (int i = 1; i < len2; i++) 
        dp[0 * len2 + i] = max(dp[0 * len2 + i - 1], str1[0] == str2[i]);

    for (int i = 1; i < len1; i++)
        dp[i * len2 + 0] = max(dp[(i - 1) * len2 + 0], str1[i] == str2[0]);

    matrix_print_(dp, len1, len2);

    for (int i = 1; i < len1; i++) {
        for (int j = 1; j < len2; j++) {
            dp[i * len2 + j] = max(dp[(i - 1) * len2 + j], dp[i * len2 + j - 1]);
            if (str1[i] == str2[j]) 
                dp[i * len2 + j] = max(dp[(i - 1) * len2 + j - 1] + 1, dp[i * len2 + j]);
        }
    }

    matrix_print_(dp, len1, len2);

    int newlen = dp[(len1 - 1) * len2 + len2 - 1];
    char *newstr = malloc(newlen + 1);
    newstr[newlen] = 0;
    int i = len1 - 1, j = len2 - 1;
    int idx = newlen - 1;
    while (idx >= 0) {
        if (i > 0 && dp[i * len2 + j] == dp[(i - 1) * len2 + j])
            i--;
        else if (j > 0 && dp[i * len2 + j] == dp[i * len2 + j - 1])
            j--;
        else {
            newstr[idx--] = str1[i];
            i--, j--;
        }
    }
    printf("%s\n", newstr);
    free(dp);
    free(newstr);
}

int main(int argc, char *argv[])
{
    const char *str1 = "ABBBBBBCCDDD";
    const char *str2 = "AAABCDDE";
    longest_common_subseq(str1, str2);        
}
