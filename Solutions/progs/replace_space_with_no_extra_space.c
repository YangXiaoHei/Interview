#include <stdio.h>
#include <string.h>

void replace_space(char *s, size_t len)
{
    if (!s || len == 0)
        return;

    int nspace = 0;
    for (int i = 0; i < len; i++)
        if (s[i] == ' ')
            nspace++;

    size_t newlen = len + 2 * nspace + 1;
    char *oldp = s, *newp = s;
    oldp += len;
    newp += newlen;
    *newp-- = 0;

    while (len--) {
        if (*oldp == ' ') {
            *newp-- = '0';
            *newp-- = '2';
            *newp-- = '%';
            oldp--;
        } else
            *newp-- = *oldp--;
    }
}

int main(int argc, char *argv[])
{
    char s[128] = "1 2 3 4 ";
    replace_space(s, strlen(s));
    printf("%s\n", s);
}
