#include "ds.h"

int digit(int n)
{
    int res = 0;
    while (n) {
        n /= 10;
        res++;
    }
    return res;
}

char *statistic(const char *str)
{
    int total_alloc = 0;
    int len = strlen(str);
    int cnt = 1;
    int diff = 0;
    for (int i = 1; i <= len; i++) {
        if (str[i] == str[i - 1]) {
            cnt++;
        } else {
            total_alloc += digit(cnt);
            cnt = 1;
            diff++;
        }
    }
    total_alloc += diff * 3 - 1;

    int k = 0;
    cnt = 1;
    total_alloc++;
    char *buf = malloc(total_alloc + 1);
    for (int i = 1; i <= len; i++) {
        if (str[i] == str[i - 1]) {
            cnt++;
        } else {
            k += snprintf(buf + k, total_alloc - k, "%c_%d_", str[i - 1], cnt);
            cnt = 1;
        }
    }
    return buf;
}

int main(int argc, char *argv[])
{
    printf("%s\n", statistic("aaa"));
    printf("%s\n", statistic("aaabcdeeeefffghiiijj"));
    printf("%s\n", statistic("a"));
    printf("%s\n", statistic("abcdefg"));
    printf("%s\n", statistic("aaaaaaaaaaaaaaabbbbbbbbbcccddaaaa"));
}
