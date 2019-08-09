#include "ds.h"

char* statistic(const char *str, char *buf, int buflen)
{
    if (!str || !*str || !buf || buflen <= 0)
        return NULL;

    int l = 0;
    int len = strlen(str);
    int count = 1;
    for (int i = 1; i < len; i++) {
        if (str[i] != str[i - 1]) {
            l += snprintf(buf + l, buflen - l, "%c_%d_", str[i - 1], count);
            count = 1;
        } else {
            count++;
        }   
    }
    l += snprintf(buf + l, buflen - l, "%c_%d", str[len - 1], count);
    return buf;
}

int main(int argc, char *argv[])
{
    char buf[100];
    printf("%s\n", statistic("aaabbbcccd", buf, sizeof(buf)));
    printf("%s\n", statistic("abcdefg", buf, sizeof(buf)));
    printf("%s\n", statistic("abbcccddddeeeeeffffggghhi", buf, sizeof(buf)));
}
