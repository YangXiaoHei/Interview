#include "ds.h"

int map[256] = { 0 };
int loc = 1;

char first_once(char c)
{
    if (map[c] > 0)
        map[c] = -1;
    else if (map[c] == 0)
        map[c] = loc++;

    char minc = 0;
    int midx = 2147483647;
    for (int i = 0; i < 256; i++) {
        if (map[i] > 0 && map[i] < midx) {
            midx = map[i];
            minc = i;
        }
    }
    return minc;
}

int main(int argc, char *argv[])
{
    const char *str = "google";
    for (char *p = (char *)str; *p; p++)
        printf("%c ", first_once(*p));
    printf("\n");
}
