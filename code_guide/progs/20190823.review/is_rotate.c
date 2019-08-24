#include "ds.h"

int kmp(const char *str, const char *match)
{
    // next array
    int mlen = strlen(match); 
    int *next = malloc(mlen);
    next[0] = -1, next[1] = 0;
    int i = 2, j = 0;
    int ch = 0;
    while (i < mlen) {
        if (match[i - 1] == match[ch])
            next[i++] = ++ch;
        else if (ch > 0)
            ch = next[ch];
        else
            next[i++] = 0;
    }

    // 利用 next 数组加速查找
    int slen = strlen(str);
    i = 0; 
    while (i < slen && j < mlen) {
        if (str[i] == match[j])
            i++, j++;
        else if (next[j] == -1)
            i++;
        else
            j = next[j];
    }
    free(next);
    return j == mlen ? i - j : -1;
}

int is_rotate(const char *str1, const char *str2)
{
    int len1 = strlen(str1), len2 = strlen(str2);
    if (len1 != len2)
        return 0;

    char *buf = malloc(len1 + len1 + 1);
    snprintf(buf, len1 + len1 + 1, "%s%s", str1, str1);
    int res = kmp(buf, str2);
    free(buf);
    return res > 0;
}

int main(int argc, char *argv[])
{
    printf("%d\n", is_rotate("12345", "34512"));
    printf("%d\n", is_rotate("12345", "345126"));
}
