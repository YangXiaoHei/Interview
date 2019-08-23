#include "ds.h"

char *delete_dup(char *a)
{
    if (!a || !*a)
        return NULL;

    char map[256] = { 0 };
    int len = strlen(a);

    for (int i = 0; i < len; i++)
        map[a[i]]++;

    for (int i = 0; i < len; i++)
        if (map[a[i]] > 1)
            a[i] = 0;

    int j = 0;
    for (int i = 0; i < len; i++)
        if (a[i])
            a[j++] = a[i];
    a[j] = 0;
    return a;
}

int main(int argc, char *argv[])
{
    {
        char a[] = "abcde";
        printf("%s\n", delete_dup(a));
    }
    {
        char a[] = "aabbcc";
        printf("%s\n", delete_dup(a));
    }
    {
        char a[] = "aabbcc";
        printf("%s\n", delete_dup(a));
    }
}
