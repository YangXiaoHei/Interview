#include "ds.h"

int kmp(const char *str, const char *pat)
{
    if (!str || !pat || !*str || !*pat)
        return -1;

    int slen = strlen(str);
    int plen = strlen(pat);
    if (plen > slen)
       return -1; 

    // 获取 next 数组
    int *next = malloc(sizeof(int) * plen);
    next[0] = -1;
    next[1] = 0;
    int ch = 0;
    for (int i = 2; i < plen;) {
        if (pat[ch] == pat[i])
            next[i++] = ++ch;
        else if (ch > 0)
            ch = next[ch];
        else
            next[i++] = 0;
    }

    // 利用 next 数组加速匹配
    int si = 0, pi = 0;
    while (si < slen && pi < plen) {
        if (str[si] == pat[pi])
            si++, pi++;
        else if (next[pi] == -1)
            si++;
        else
            pi = next[pi];
    }

    free(next);
    return pi == plen ? si - pi : -1;
}

int main(int argc, char *argv[])
{
    char str[100], pat[100];
    while (scanf("%s %s", str, pat) != EOF) 
        printf("index %d\n", kmp(str, pat));
}
