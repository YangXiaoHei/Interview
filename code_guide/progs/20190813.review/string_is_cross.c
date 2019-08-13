#include "ds.h"

int is_cross(const char *str1, const char *str2, const char *aim)
{
    if (!str1 || !str2 || !aim || !*str1 || !*str2 || !*aim)
        return 0;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len3 = strlen(aim);
    if (len1 + len2 != len3)
        return 0;

    int *dp = malloc(sizeof(int) * (len1 + 1) * (len2 + 1));
    memset(dp, 0, sizeof(int) * (len1 + 1) * (len2 + 1));
    dp[0 * (len2 + 1) + 0] = 1;

    for (int i = 1; i <= len2; i++) {
        if (aim[i - 1] != str2[i - 1])
            break;
        dp[0 * (len2 + 1) + i] = 1;
    }

    for (int i = 1; i <= len1; i++) {
        if (aim[i - 1] != str1[i - 1])
            break;
        dp[i * (len2 + 1) + 0] = 1;
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            char c = aim[i + j - 1];
            if (c == str1[i - 1])
                dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + j];
            else if (c == str2[j - 1])
                dp[i * (len2 + 1) + j] = dp[i * (len2 + 1) + j - 1];
        }
    }

    int res = dp[len1 * (len2 + 1) + len2];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    {
        const char *str1 = "AB";
        const char *str2 = "12";
        const char *aim = "AB12";
        printf("%d\n", is_cross(str1, str2, aim));
    }
    
    {
        const char *str1 = "AB";
        const char *str2 = "12";
        const char *aim = "A1B2";
        printf("%d\n", is_cross(str1, str2, aim));
    }
    {
        const char *str1 = "AB";
        const char *str2 = "12";
        const char *aim = "1A2B";
        printf("%d\n", is_cross(str1, str2, aim));
    }
    {
        const char *str1 = "AB";
        const char *str2 = "12";
        const char *aim = "2B1A";
        printf("%d\n", is_cross(str1, str2, aim));
    }
}
