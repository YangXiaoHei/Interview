#include "ds.h"

int is_intersect(const char *str1, int len1, const char *str2, int len2, const char *aim, int aimlen)
{
    if (!str1 || !str2 || !aim || len1 <= 0 || len2 <= 0 || aimlen <= 0)
        return 0;

    if (len1 + len2 != aimlen)
        return 0;

    int *dp = malloc(sizeof(char) * (len2 + 1));
    memset(dp, 0, sizeof(char) * (len2 + 1));

    dp[0] = 1;

    for (int i = 1; i <= len2; i++) {
        if (str2[i - 1] != aim[i - 1])
            break;
        dp[i] = 1;
    }

    for (int i = 1; i <= len1; i++) {
        dp[0] = dp[0] && str1[i - 1] == aim[i - 1];
        for (int j = 1; j <= len2; j++) {
            dp[j] = 
                (str1[i - 1] == aim[i + j - 1] && dp[j]) ||
                (str2[j - 1] == aim[i + j - 1] && dp[j - 1]);
        }
    }

    int res = dp[len2];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    const char *str1 = "AB";
    const char *str2 = "12";
    char *aim = "AB12";
    aim = "1B2A";
    printf("%d\n", is_intersect(str1, strlen(str1), str2, strlen(str2), aim, strlen(aim)));
}
