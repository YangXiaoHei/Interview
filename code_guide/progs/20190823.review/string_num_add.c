#include "ds.h"

int add(const char *str)
{
    if (!str || !*str)
        return 0;

    int sum = 0, n = 0, sign = 0;
    for (char *p = (char *)str; *p; p++) {
        if (*p == '-') {
            sign = !sign;
        } else if (*p < '0' || *p > '9') {
            n = sign ? -n : n;
            sum += n;
            n = 0, sign = 0;
        } else {
            n = n * 10 + *p - '0';
        }
    }
    n = sign ? -n : n;
    sum += n;
    return sum;
}

int main(int argc, char *argv[])
{
    printf("%d\n", add("A-1B--2C--D6E"));
    printf("%d\n", add("AE2DC33"));
}
