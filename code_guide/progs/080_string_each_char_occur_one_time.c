#include "ds.h"

int each_one_time(const char *str)
{
    int count[256] = { 0 };
    for (char *p = (char *)str; *p; p++) {
        if (count[*p])
            return 0;
        count[*p]++;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    printf("%d\n", each_one_time("abcdefghijklmn"));
    printf("%d\n", each_one_time("abcdabdcefgalsdf"));
}
