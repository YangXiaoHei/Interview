#include "ds.h"

void reverse(char *beg, char *end)
{
    while (beg < end) {
        char t = *beg;
        *beg = *end;
        *end = t;
        beg++, end--;
    }
}

char *rotate(char *str, int k)
{
    if (!str || !*str || k < 0)
        return NULL;

    int len = strlen(str);
    if (k > len)
        return NULL;

    reverse(str, str + len - 1);
    reverse(str + len - k, str + len - 1);
    reverse(str, str + len - k - 1);
    return str;
}

int main(int argc, char *argv[])
{
    {
        char str[] = "123456";
        printf("%s\n", rotate(str, 2));
    }
    {
        char str[] = "123456";
        printf("%s\n", rotate(str, 6));
    }
}
