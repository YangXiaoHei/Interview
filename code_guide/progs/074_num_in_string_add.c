#include "ds.h"

int string_add(const char *str)
{
    int res = 0, num = 0, sign = 0;
    for (char *p = (char *)str; *p; p++) {
        if (*p >= '0' && *p <= '9') {
            num = num * 10 + *p - '0';
            num = sign ? -num : num;
            sign = 0;
            printf("num=%d\n", num);
        } else if (*p == '-') {
            sign = !sign;
        } else {
            res += num;
            num = 0;
        }
    }
    if (num) {
        res += num;
        num = sign ? -num : num;
    }
    return res;
}

int main(int argc, char *argv[])
{
    printf("%d\n", string_add("A1CD2E33"));
}
