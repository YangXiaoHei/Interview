#include "ds.h"

void sink(char *str, int i, int size)
{
    char t = str[i - 1];
    while (i * 2 <= size) {
        int j = i * 2;
        if (j < size && str[j - 1] < str[j]) j++;
        if (t >= str[j - 1]) break;
        str[i - 1] = str[j - 1];
        i = j;
    }
    str[i - 1] = t;
}

void exch(char *str, int i, int j)
{
    char t = str[i - 1];
    str[i - 1] = str[j - 1];
    str[j - 1] = t;
}

void heap(char *str, int size)
{
    for (int i = size >> 1; i > 0; i--)
        sink(str, i, size);

    while (size > 1) {
        exch(str, 1, size--);
        sink(str, 1, size);
    }
}

int only_once(char *str)
{
    if (!str || !*str)
        return 0;

    int len = strlen(str);
    heap(str, len);
    for (int i = 1; i < len; i++) 
        if (str[i] == str[i - 1])
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    {
        char str[] = "aaabbbcc";
        printf("%d\n", only_once(str));
    }
    {
        char str[] = "abc";
        printf("%d\n", only_once(str));
    }
}
