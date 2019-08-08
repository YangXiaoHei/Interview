#include "ds.h"

void remove_k_zero(char *str, int k)
{
    if (!str || !*str || k <= 0)
        return;

    int start = -1, count = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '0') {
            start = start == -1 ? i : start;
            count++;
        } else {
            if (count == k) {
                while (count--)
                    str[start++] = 0;
            }
            start = -1;
            count = 0;
        }
    }
    if (count == k) {
        while (count--)
            str[start++] = 0;
    }

    char *p = str, *q = str;
    while (1) {
        while (q - str < len && !*q) q++;
        if (q - str >= len) break;
        while (*q) *p++ = *q++;
    }
    *p = 0;
}

int main(int argc, char *argv[])
{
    {
        char str[] = "a0000b000c000defg0hi000j000k0000pppp000";
        remove_k_zero(str, 3);
        printf("%s\n", str);
    }
    {
        char str[] = "000";
        remove_k_zero(str, 3);
        printf("%s\n", str);
    }
}
