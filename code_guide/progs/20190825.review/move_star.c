#include "ds.h"

char *move(char *str)
{
    if (!str || !*str)
        return NULL;

    int len = strlen(str);
    int k = len - 1;
    for (int i = len - 1; i >= 0; i--)
        if (str[i] != '*')
            str[k--] = str[i];
    while (k >= 0)
        str[k--] = '*';
    return str;
}

/* 这种方案不可行，因为会改变非 * 字符的顺序
 * char *move(char *str)
 * {
 *     if (!str || !*str)
 *         return NULL;
 * 
 *     int len = strlen(str);
 *     int i = 0, j = len - 1;
 *     int lo = 0, hi = len - 1;
 *     while (1) {
 *         while (i < hi && str[i] == '*') i++;
 *         while (j > lo && str[j] != '*') j--;
 *         if (i >= j) break;
 *         char t = str[i];
 *         str[i] = str[j];
 *         str[j] = t;
 *     }
 *     return str;
 * }
 */

int main(int argc, char *argv[])
{
    {
        char str[] = "a*b*c***defghijk*lmn**";
        printf("%s\n", move(str));
    }
}
