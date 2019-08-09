#include "ds.h"

char *replace_blank(char *buf, int buflen)
{
    int count = 0;
    for (int i = 0; i < buflen; i++)
        if (buf[i] == ' ')
            count++;

    int blen = strlen(buf);
    int len = blen + count * 2;
    for (int i = len - 1, j = blen - 1; j >= 0;) {
        if (buf[j] == ' ') {
            buf[i--] = '0';
            buf[i--] = '2';
            buf[i--] = '%';
            j--;
        } else
            buf[i--] = buf[j--];
    }
    buf[len] = 0;
    return buf;
}

int main(int argc, char *argv[])
{
    char buf[100];
    snprintf(buf, sizeof(buf), "a  b c  d ");
    printf("%s\n", replace_blank(buf, sizeof(buf)));
}
