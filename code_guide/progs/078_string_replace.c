#include "ds.h"

char * replace(const char *str, const char *from, const char *to, char *buf, int buflen)
{
    int len = strlen(str);
    int flen = strlen(from);
    int tlen = strlen(to);
    int count = 0;
    snprintf(buf, buflen, "%s", str);
    for (int i = 0; i < len; ) {
        if (strncmp(buf + i, from, flen) == 0) {
            count++;
            char *p = buf + i + flen - 1;
            int j = flen;
            while (j--)
                *p-- = 0;
            i += flen;
        } else
            i++;
    } 

    // 不会有任何替换发生
    if (count == 0)
        return buf;

    int total_len = 0;
    if (flen > tlen) {
        if (buflen < len) {
            printf("underflow\n");
            return buf;
        }

        total_len = len - count * (flen - tlen);
        for (int i = 0, j = 0; j < total_len;) {
            if (buf[i]) {
               buf[j++] = buf[i++];
            } else {
                while (i < len && !buf[i]) i++;
                for (char *p = (char *)to; *p; p++)
                    buf[j++] = *p;
            } 
        }
    } else {
        total_len = len + count * (tlen - flen);
        if (total_len >= buflen) {
            printf("overflow\n");
            return buf;
        }
        for (int j = total_len - 1, i = len - 1; j >= 0;) {
            if (buf[i]) {
                buf[j--] = buf[i--];
            } else {
                while (i >= 0 && !buf[i]) i--;
                for (int k = tlen - 1; k >= 0; k--)
                    buf[j--] = to[k];
            }
        }
    }
    buf[total_len] = 0;
    return buf;
}

int main(int argc, char *argv[])
{
    char buf[100];
    int size = sizeof(buf);
    printf("%s\n", replace("123456123456123", "123", "x", buf, size));
    printf("%s\n", replace("123456123456123", "123", "xxxx", buf, size));
    printf("%s\n", replace("123456123456123", "123", "xxx", buf, size));
    printf("%s\n", replace("123456123456123", "123", "", buf, size));
    printf("%s\n", replace("123456123456123", "123456123456123", "", buf, size));
    printf("%s\n", replace("123456123456123", "123456123456123", "666", buf, size));
    printf("%s\n", replace("123456123456123", "666", "999", buf, size));
    printf("%s\n", replace("aaab", "aab", "999", buf, size));
}
