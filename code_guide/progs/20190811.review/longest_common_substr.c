#include "ds.h"

int longest_common_substr(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return 0;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int *dp = malloc(sizeof(int) * len1 * len2);
    memset(dp, 0, sizeof(int) * len1 * len2);

    dp[0 * len2 + 0] = *str1 == *str2;
    for (int i = 1; i < len2; i++)
        dp[0 * len2 + i] = str1[0] == str2[i];

    for (int i = 1; i < len1; i++)
        dp[i * len2 + 0] = str1[i] == str2[0];

    for (int i = 1; i < len1; i++) 
        for (int j = 1; j < len1; j++) 
            if (str1[i] == str2[j])
                dp[i * len2 + j] = dp[(i - 1) * len2 + j - 1] + 1;

    /* matrix_print_(dp, len1, len2); */

    int max = 0, maxi = 0;
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            if (dp[i * len2 + j] > max) {
                max = dp[i * len2 + j];
                maxi = i;
            }
        }
    }

    char *buf = malloc(max + 1);
    buf[max] = 0;
    memcpy(buf, str1 + maxi - max + 1, max);
    printf("%s\n", buf);

    free(dp);
    return max;
}

int main(int argc, char *argv[])
{
    {
        const char *str1 = "abcde";
        const char *str2= "bebcd";
        longest_common_substr(str1, str2);
    }
    {
        const char *str1 = "AB12345";
        const char *str2= "C123D456E";
        longest_common_substr(str1, str2);
    }
    {
        const char *str1 = "1A2B3C4D";
        const char *str2= "12345";
        longest_common_substr(str1, str2);
    }
}
