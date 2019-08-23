#include "ds.h"

char *delete_a_in_b(char *a, char *b)
{
    if (!a || !b)
        return NULL;

    if (!*b || !*a)
        return a;

    int blen = strlen(b);
    char map[256] = { 0 };
    for (char *p = b; *p; p++)
        map[*p] = 1;

    int alen = strlen(a);
    for (int i = 0; i < alen; i++) 
        if (map[a[i]])
            a[i] = 0;

    int j = 0;
    for (int i = 0; i < alen; i++)
        if (a[i])
            a[j++] = a[i];
    a[j] = 0;
    return a;
}

int main(int argc, char *argv[])
{
    {
        char a[] = "12345";
        char *b = "135";
        printf("%s\n", delete_a_in_b(a, b));
    }
    {
        char a[] = "111111";
        char *b = "1";
        printf("%s\n", delete_a_in_b(a, b));
    }
    {
        char a[] = "1111111211111";
        char *b = "1";
        printf("%s\n", delete_a_in_b(a, b));
    }
}
