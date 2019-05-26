#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_space(char *s, char *buf, size_t buflen)
{
    if (!s || !buf || buflen <= 0)
        return -1;

    int nspace = 0;
    size_t len = strlen(s);
    for (int i = 0; i < len; i++)
       if (s[i] == ' ')
          nspace++;
    size_t newlen = len + 2 * nspace + 1;
    char *news = malloc(newlen);
    if (!news) return -1;
    char *newp = news, *oldp = s;
    while (*oldp) {
        if (*oldp == ' ') {
            memcpy(newp, "%20", 3);
            newp += 3;
            oldp++;
        } else {
            *newp++ = *oldp++;
        }
    } 
    *newp = 0;
    size_t copylen = buflen < newlen ? buflen - 1 : newlen; 
    memcpy(buf, news, copylen);
    buf[buflen - 1] = 0;
    free(news);
    return 0;
}

int main(int argc, char *argv[])
{
    char *s = "1 2   3 4 ";
    char buf[128];
    replace_space(s, buf, 128);
    printf("%s\n", buf);
}


