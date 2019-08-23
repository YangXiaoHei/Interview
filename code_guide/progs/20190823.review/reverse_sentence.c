#include "ds.h"

void reverse_word(char *beg, char *end)
{
    if (beg == end)
        return;

    while (beg < end) {
        char t = *beg;
        *beg = *end;
        *end = t;
        beg++, end--;
    }
}

char* reverse(char *str)
{
    if (!str || !*str)
        return str;

    int len = strlen(str);
    reverse_word(str, str + len - 1);

    char *beg = NULL, *end = NULL;
    char *p = str;
    while (*p && *p == ' ') p++;
    for (; *p; p++) {
        if (*p != ' ') {
            beg = !beg ? p : beg;
            end = p;
        } else {
            reverse_word(beg, end);
            beg = end = NULL;
        }
    }

    if (beg && end)
        reverse_word(beg, end);

    return str;
}

int main(int argc, char *argv[])
{
    {
        char str[] = "you love I !";
        printf("%s\n", reverse(str));
    }
    {
        char str[] = "67890   12345";
        printf("%s\n", reverse(str));
    }
}
