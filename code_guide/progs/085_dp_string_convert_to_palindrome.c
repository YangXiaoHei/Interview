#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

char *convert_to_palindrome(const char *str)
{
    int len = strlen(str);
    // dp table
    int *dp = malloc(sizeof(int) * len * len);
    memset(dp, 0, sizeof(int) * len * len);

    for (int j = 1; j < len; j++) {
        dp[(j - 1) * len + j] = str[j - 1] != str[j];
        for (int i = j - 2; i >= 0; i--) {
            if (str[i] == str[j])
                dp[i * len + j] = dp[(i + 1) * len + j - 1];
            else
                dp[i * len + j] = 1 + min(dp[(i + 1) * len + j], dp[i * len + j - 1]);
        }
    }
    /* matrix_print_(dp, len, len); */

    // convert by dp table
    int newlen = len + dp[0 * len + len - 1];
    char *newstr = malloc(newlen + 1);
    newstr[newlen] = 0;
    int i = 0, j = len - 1;
    int resl = 0, resr = newlen - 1;
    while (i <= j) {
        if (str[i] == str[j]) {
            newstr[resl++] = str[i++];
            newstr[resr--] = str[j--];
        } else if (dp[i * len + j - 1] < dp[(i + 1) * len + j]) {
            newstr[resl++] = str[j];
            newstr[resr--] = str[j];
            j--;
        } else {
            newstr[resl++] = str[i];
            newstr[resr--] = str[i];
            i++;
        }
    }
    return newstr;
}

int main(int argc, char *argv[])
{
    printf("%s\n", convert_to_palindrome("1232451"));
    printf("%s\n", convert_to_palindrome("12345"));
    printf("%s\n", convert_to_palindrome("1221"));
    printf("%s\n", convert_to_palindrome("918118"));
}
