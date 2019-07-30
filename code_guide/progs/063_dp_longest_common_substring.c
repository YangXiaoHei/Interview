#include "ds.h"

void longest_common_string(const char *str1, int len1, const char *str2, int len2)
{
    if (!str1 || !*str1 || !str2 || !*str2 || len1 <= 0 || len2 <= 0)
        return;

    int *dp = malloc(sizeof(int) * len1 * len2);
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * len1 * len2);

    for (int i = 0; i < len1; i++) 
        dp[i * len2 + 0] = str1[i] == str2[0]; 

    for (int i = 1; i < len2; i++) 
        dp[0 * len2 + i] = str1[0] == str2[i];

    for (int i = 1; i < len1; i++) 
        for (int j = 1; j < len2; j++) 
            dp[i * len2 + j] = str1[i] != str2[j] ? 0 : dp[(i - 1) * len2 + j - 1] + 1;

    matrix_print_(dp, len1, len2);

    int maxlen = 0;
    int maxi = 0;
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            if (dp[i * len2 + j] > dp[maxi * len2 + j]) {
                maxi = i;
                maxlen = dp[i * len2 + j];
            }
        }
    }
    char *buf = malloc(maxlen + 1);
    buf[maxlen] = 0;
    memcpy(buf, str1 + len1 - maxlen, maxlen);
    printf("%s\n", buf);
    free(buf);
    free(dp);
}

char *gen_random_str(int len)
{
    if (len <= 0)
        return NULL;

    char *str = malloc(len + 1);
    int *arr = arrayWithRange(len, 0, 26);
    str[len] = 0;
    for (int i = len - 1; i >= 0; i--)
        str[i] = 'a' + arr[i];
    free(arr);
    return str;
}

int main(int argc, char *argv[])
{
    char *str1 = "zzzzzzzabcde";
    char *str2 = "zzxbcdef";
    longest_common_string(str1, strlen(str1), str2, strlen(str2));
}
