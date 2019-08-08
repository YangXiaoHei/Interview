#include "ds.h"

int kmp(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return -1;

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len2 > len1)
        return -1;

    int *next = malloc(sizeof(int) * len2);
    next[0] = -1;
    next[1] = 0;
    int ch = 0;
    for (int i = 2; i < len2;) {
        if (str2[ch] == str2[i])
            next[i++] = ++ch;
        else if (ch > 0)
            ch = next[ch];
        else
            next[i++] = 0;
    }

    int si = 0, pi = 0;
    while (si < len1 && pi < len2) {
        if (str1[si] == str2[pi])
            si++, pi++;
        else if (next[pi] == -1)
            si++;
        else
            pi = next[pi];
    }
    free(next);
    return pi == len2 ? si - pi : -1;
}

int is_rotation(const char *str1, const char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 != len2)
        return 0;

    char *str = malloc(2 * len1 + 1);
    snprintf(str, 2 * len1 + 1, "%s%s", str1, str1);
    int res = kmp(str, str2) != -1;
    free(str);
    return res;
}

int main(int argc, char *argv[])
{
    printf("%d\n", is_rotation("1234", "4123"));
    printf("%d\n", is_rotation("45123", "51234"));
}
