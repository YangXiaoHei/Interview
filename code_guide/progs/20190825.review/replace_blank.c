#include "ds.h"

char *replace_blank(const char *str)
{
    if (!str || !*str)
        return NULL;
    int cnt = 0;
    int len = 0;
    for (char *p = (char *)str; *p; p++, len++)
        if (*p == ' ')
            cnt++;

    int total_alloc = len + cnt * 2;
    char *newstr = malloc(total_alloc + 1);
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            k += snprintf(newstr + k, total_alloc + 1 - k, "%%20");
        } else {
            newstr[k++] = str[i];
        }
    }
    newstr[k] = 0;
    return newstr;
}

int main(int argc, char *argv[])
{
    printf("%s\n", replace_blank("12345 "));
    printf("%s\n", replace_blank(" 12345 "));
    printf("%s\n", replace_blank(" 12  3 4 5 "));
}
