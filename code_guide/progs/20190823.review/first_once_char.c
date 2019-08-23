#include "ds.h"

char first_once(const char *a)
{
    if (!a || !*a)
        return 0;

    int map[256] = { 0 };
    for (char *p = (char *)a; *p; p++)
        map[*p]++;

    char c = 0;
    for (char *p = (char *)a; *p; p++)
        if (map[*p] == 1) {
            c = *p;
            break;
        }
    return c;
}

int main(int argc, char *argv[])
{
    printf("%c\n", first_once("abcdacccb"));
}
