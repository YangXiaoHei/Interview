#include "ds.h"

int only_once(const char *str)
{
    if (!str || !*str)
        return 0;

    char map[256] = { 0 };
    for (char *p = (char *)str; *p; p++) {
        if (map[*p])
            return 0;
        map[*p]++;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    printf("%d\n", only_once("aabbcc"));
    printf("%d\n", only_once("abc"));
}
