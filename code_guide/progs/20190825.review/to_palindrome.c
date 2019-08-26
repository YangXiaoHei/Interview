#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

char *to_palindrome(const char *str)
{
    if (!str || !*str)
        return NULL;

    int len = strlen(str);
    int *dp = malloc(sizeof(int) * len * len);
    dp[0 * len + 0] = 0;

    for (int j = 1; j < len; j++) {
        dp[j * len + j] = 0;
        for (int i = j - 1; i >= 0; i--) {
            if (j - i < 2)
                dp[i * len + j] = str[i] != str[j];
            else
                dp[i * len + j] = str[i] == str[j] ? 
                    dp[(i + 1) * len + j - 1] : 
                    1 + min(dp[(i + 1) * len + j], dp[i * len + j - 1]);
        }
    }

    int newlen = len + dp[0 * len + len - 1];
    char *newstr = malloc(newlen + 1);
    int ni = 0, nj = newlen - 1; 
    int oi = 0, oj = len - 1;
    while (oi <= oj) {
        if (str[oi] == str[oj]) {
            newstr[ni++] = newstr[nj--] = str[oi];
            oi++, oj--;
        } else if (dp[(oi + 1) * len + oj] < dp[oi * len + oj - 1]) {
            newstr[ni++] = newstr[nj--] = str[oi];
            oi++;
        } else {
            newstr[ni++] = newstr[nj--] = str[oj];
            oj--;
        }
    }
    free(dp);
    newstr[newlen] = 0;
    return newstr;
}


int main(int argc, char *argv[])
{
    printf("%s\n", to_palindrome("abc"));
    printf("%s\n", to_palindrome("aba"));
    printf("%s\n", to_palindrome("abcbda"));
}
