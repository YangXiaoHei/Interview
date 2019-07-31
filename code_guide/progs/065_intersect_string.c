#include "ds.h"

int is_intersect(const char *str1, int len1, const char *str2, int len2, const char *aim, int aimlen)
{
    if (!str1 || !str2 || !*str1 || !*str2 || len1 <= 0 || len2 <= 0)
        return 0;

    if (len1 + len2 != aimlen)
        return 0;

    int *dp = malloc(sizeof(char) * (len1 + 1) * (len2 + 1));
    if (!dp) exit(1);
    memset(dp, 0, sizeof(char) * (len1 + 1) * (len2 + 1));

    dp[0 * (len2 + 1) + 0] = 0;
    for (int i = 1; i <= len2; i++) {
        if (str2[i - 1] != aim[i - 1])
            break;
        dp[0 * (len2 + 1) + i] = 1;
    }

    for (int i = 1; i <= len1; i++) {
        if (str1[i - 1] != aim[i - 1])
            break;
        dp[i * (len2 + 1) + 0] = 1;
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            dp[i * (len2 + 1) + j] = 
                (str1[i - 1] == aim[i + j - 1] && dp[(i - 1) * (len2 + 1) + j]) ||
                (str2[j - 1] == aim[i + j - 1] && dp[i * (len2 + 1) + j - 1]);
        }
    }

    int res = dp[len1 * (len2 + 1) + len2];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    const char *str1 = "AB";
    const char *str2 = "12";
    char *aim = "1A2B";
    aim = "A2B1";
    printf("%d\n", is_intersect(str1, strlen(str1), str2, strlen(str2), aim, strlen(aim)));
}
