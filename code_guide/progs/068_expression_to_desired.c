#include "ds.h"

int is_valid(const char *str, int len)
{
    if (!(len & 1))
        return 0;

    for (int i = 0; i < len; i += 2)
        if (str[i] != '0' && str[i] != '1')
            return 0;

    for (int i = 1; i < len; i += 2)
        if (str[i] != '&' && str[i] != '|' && str[i] != '^')
            return 0;

    return 1;
}

int f(const char *str, int desired, int l, int r)
{
    if (r == l) {
        if (*str == '1')
            return desired ? 1 : 0;
        else
            return desired ? 0 : 1;
    }

    int res = 0;
    if (desired) {
        for (int i = l + 1; i <= r; i += 2) {
            switch(str[i]) {
                case '^' : {
                    res += f(str, 1, l, i - 1) * f(str + i + 1, 0, i + 1, r);
                    res += f(str, 0, l, i - 1) * f(str + i + 1, 1, i + 1, r);
               } break;
               case '&' : {
                    res += f(str, 1, l, i - 1) * f(str + i + 1, 1, i + 1, r);
               } break;
                case '|' : {
                    res += f(str, 1, l, i - 1) * f(str + i + 1, 0, i + 1, r);
                    res += f(str, 0, l, i - 1) * f(str + i + 1, 1, i + 1, r);
                    res += f(str, 1, l, i - 1) * f(str + i + 1, 1, i + 1, r);
               } break;
            }
        }
    } else {
        for (int i = l + 1; i <= r; i += 2) {
            switch(str[i]) {
                case '^' : {
                    res += f(str, 1, l, i - 1) * f(str + i + 1, 1, i + 1, r);
                    res += f(str, 0, l, i - 1) * f(str + i + 1, 0, i + 1, r);
               } break;
               case '&' : {
                    res += f(str, 0, l, i - 1) * f(str + i + 1, 1, i + 1, r);
                    res += f(str, 1, l, i - 1) * f(str + i + 1, 0, i + 1, r);
                    res += f(str, 0, l, i - 1) * f(str + i + 1, 0, i + 1, r);
               } break;
                case '|' : {
                    res += f(str, 0, l, i - 1) * f(str + i + 1, 0, i + 1, r);
               } break;
            }
        }
    }
    return res;
}

int expression_to_desired(const char *str, int desired)
{
    if (!str || !*str)
        return 0;

    int len = strlen(str);
    if (!is_valid(str, len)) {
        printf("invalid expression\n");
        return 0;
    }
    return f(str, desired, 0, len - 1);
}

int main(int argc, char *argv[])
{
    const char *str = "1^0|0|1";
    int desired = 1;
    printf("res = %d\n", expression_to_desired(str, desired));
}
