#include "ds.h"

void longest_common_substr(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return;

    int len1 = strlen(str1);    
    int len2 = strlen(str2);

    int row = 0, col = len2 - 1;
    int i = row, j = col;
    int end = 0, max = 0;
    int len = 0;
    while (row < len1) {
        i = row;
        j = col;
        while (i < len1 && j < len2) {
            len = str1[i] == str2[j] ? len + 1 : 0;
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
    memcpy(buf, str1 + end - max + 1, max);
    printf("%s\n", buf);
}

int main(int argc, char *argv[])
{
    const char *str1 = "AB12345CD";
    const char *str2 = "1B34H12345DC";
    longest_common_substr(str1, str2);
}
