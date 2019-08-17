#include "ds.h"

int is_cross(const char *str1, const char *str2, const char *aim)
{
    if (!str1 || !str2 || !*str1 || !*str2 || !aim || !*aim)
        return 0;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = strlen(aim);
    if (len1 + len2 != len)
        return 0;

    int *dp = malloc(sizeof(int) * (len2 + 1));
    memset(dp, 0, sizeof(int) * (len2 + 1));
    dp[0] = 1;

    for (int j = 1; j <= len2; j++) {
        if (aim[j - 1] != str2[j - 1])
            break;
        dp[j] = 1;
    }

    for (int i = 1; i <= len1; i++) {
        dp[0] = aim[i - 1] == str1[i - 1];
        for (int j = 1; j <= len2; j++) {
           dp[j] = 
              (aim[i + j - 1] == str1[i - 1] && dp[j]) ||
              (aim[i + j - 1] == str2[j - 1] && dp[j - 1]); 
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
    const char *aim = "A12B";
    printf("%d\n", is_cross(str1, str2, aim));
}
