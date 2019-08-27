#include "ds.h"

char *delete_contain(char *a, const char *b)
{
    if (!a || !b || !*a || !*b)
        return NULL;

    int map[256] = { 0 };
    for (char *p = (char *)b; *p; p++)
        map[*p]++;

    char *q = a;
    for (char *p = a; *p; p++)
        if (!map[*p])
            *q++ = *p;
    *q = 0;
    return a;
}

int main(int argc, char *argv[])
{
    char a[] = "abbbccc";
    const char *b = "bc";
    printf("%s\n", delete_contain(a, b));
}
