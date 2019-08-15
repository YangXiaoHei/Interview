#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_cut_times(const char *str)
{
    if (!str || !*str)
        return 0;
    int len = strlen(str);
    char *p = malloc(len * len);
    memset(p, 0, len * len);

    int *dp = malloc(sizeof(int) * (len + 1));
    dp[len] = -1;
    for (int i = len - 1; i >= 0; i--) {
        dp[i] = 2147483647;
        for (int j = i; j < len; j++) {
            if (str[i] == str[j] && (j - i < 2 || p[(i + 1) * len + j - 1])) {
                p[i * len + j] = 1;
                dp[i] = min(dp[i], dp[j + 1] + 1);
            }
        }
    }
    int res = dp[0];
    free(dp);
    free(p);
    return res;
}

int main(int argc, char *argv[])
{
    {
        const char *str = "ABCDEDCBA";
        printf("min cut times : %d\n", min_cut_times(str));
    }
    {
        const char *str = "ABCDEDCB";
        printf("min cut times : %d\n", min_cut_times(str));
    }
}
