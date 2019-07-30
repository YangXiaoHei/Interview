#include "ds.h"

void longest_common_substring(const char *str1, int len1, const char *str2, int len2)
{
    if (!str1 || !str2 || !*str1 || !*str2 || len1 <= 0 || len2 <= 0)
        return;

    int row = 0, col = len2 - 1;
    int max = 0, end = 0;
    while (row < len1) {
        int i = row, j = col;
        int len = 0;
        while (i < len1 && j < len2) {
            len = str1[i] != str2[j] ? 0 : len + 1;
            if (len > max) {
                max = len;
                end = i;
            }
            i++, j++;
        }
        if (col > 0)
            col--;
        else
            row++;
    }
    char *buf = malloc(max + 1);
    buf[max] = 0;
    memcpy(buf, str1 + len1 - max, max);
    printf("%s\n", buf);
}

int main(int argc, char *argv[])
{
    char *str1 = "azbcdef";
    char *str2 = "zzzabcdefoooo";
    longest_common_substring(str1, strlen(str1), str2, strlen(str2));
}
