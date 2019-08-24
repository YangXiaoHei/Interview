#include "ds.h"

char *replace(const char *str, const char *from, const char *to)
{
    if (!str || !*str || !from || !*from || !to)
        return (char *)str; // dont care

    int len = strlen(str), flen = strlen(from), tlen = 0;
    char *buf = malloc(len + 1);
    snprintf(buf, len + 1, "%s", str);
    printf("old: %s\n", buf);
    printf("from : %s\n", from);
    printf("to   : %s\n", to);

    int cnt = 0;
    for (int i = 0; i < len; ) {
        if (strncmp(buf + i, from, flen) == 0) {
            cnt++;
            char *p = buf + i + flen - 1;
            for (int j = flen; j > 0; j--)
                *p-- = 0;
            i += flen;
        } else 
            i++;
    }

    // 没有匹配, 不需要做任何替换
    if (!cnt) 
        return (char *)str; // dont care

    tlen = strlen(to);
    int reslen = 0;
    char *res = NULL;
    reslen = len + cnt * (tlen - flen);
    res = malloc(reslen + 1);
    int k = 0;
    for (int i = 0; i < len;) {
        if (buf[i]) {
            res[k++] = buf[i++];   
        } else {
            memcpy(res + k, to, tlen); 
            k += tlen;
            i += flen;
        }
    }
    res[k] = 0;
    free(buf);
    return res;
}

int main(int argc, char *argv[])
{
    printf("new: %s\n\n", replace("123xxx456yy7o8oo9ppp", "ppp", "A"));    
    printf("new: %s\n\n", replace("123xxx456yy7o8oo9ppp", "p", "ABC"));    
    printf("new: %s\n\n", replace("123xxx456yy7o8oo9ppp", "p", ""));    
    printf("new: %s\n\n", replace("123xxx456yy7o8oo9ppp", "o", "III"));    
    printf("new: %s\n\n", replace("123xxx456yy7o8oo9ppp", "o", ""));    
    printf("new: %s\n\n", replace("123xxx456yy7o8oo9ppp", "xx", ""));    
    printf("new: %s\n\n", replace("123xxx456yy7o8oo9ppp", "123", ""));    
    printf("new: %s\n\n", replace("aaab", "aab", ""));    
}
