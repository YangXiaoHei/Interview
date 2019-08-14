#include "ds.h"

char *new_char(const char *str, int k)
{
    if (!str || !*str || k < 0)
        return NULL;

    int len = strlen(str);
    if (k > len - 1)
        return NULL;

    int cnt = 0;
    for (int i = k - 1; i >= 0; i--) {
        if (str[i] >= 'a' && str[i] <= 'z')
            break;
        cnt++;
    }

    if (cnt & 1) {
        char *buf = malloc(3);
        buf[0] = str[k - 1];
        buf[1] = str[k];
        buf[2] = 0;
        return buf;
    }

    if (str[k] < 'a' || str[k] > 'z') {
        char *buf = malloc(3);
        buf[0] = str[k];
        buf[1] = str[k + 1];
        buf[2] = 0;
        return buf;
    }

    char *buf = malloc(2);
    buf[0] = str[k];
    buf[1] = 0;
    return buf;
}

int main(int argc, char *argv[])
{
    const char *str = "aaABCDEcBCg";
    for (int i = 0; i < strlen(str); i++)
        printf("%s\n", new_char(str, i));
}
