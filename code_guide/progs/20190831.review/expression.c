#include "ds.h"

int e(const char *str, int desired, int l, int r)
{
    if (l == r)
        return (desired && str[l] == '1') || (!desired && str[l] == '0');

    int res = 0;
    for (int i = l + 1; i < r; i++) {
        switch(str[i]) {
            case '&' : {
               if (desired) {
                    res += e(str, 1, l, i - 1) * e(str, 1, i + 1, r);
               } else {
                    res += e(str, 0, l, i - 1) * e(str, 0, i + 1, r); 
                    res += e(str, 1, l, i - 1) * e(str, 0, i + 1, r); 
                    res += e(str, 0, l, i - 1) * e(str, 1, i + 1, r);
               }
            } break;
            case '^' : {
               if (desired) {
                    res += e(str, 1, l, i - 1) * e(str, 0, i + 1, r); 
                    res += e(str, 0, l, i - 1) * e(str, 1, i + 1, r);
               } else {
                    res += e(str, 1, l, i - 1) * e(str, 1, i + 1, r); 
                    res += e(str, 0, l, i - 1) * e(str, 0, i + 1, r); 
               }
            } break;
            case '|' : {
               if (desired) {
                    res += e(str, 1, l, i - 1) * e(str, 0, i + 1, r); 
                    res += e(str, 0, l, i - 1) * e(str, 1, i + 1, r); 
                    res += e(str, 1, l, i - 1) * e(str, 1, i + 1, r);
               } else {
                    res += e(str, 0, l, i - 1) * e(str, 0, i + 1, r); 
               }
            } break;
        }
    }
    return res;
}

int expressiong(const char *str, int desired)
{
    if (!str || !*str)
        return 0;

    return e(str, desired, 0, strlen(str) - 1);
}

int main()
{
    printf("%d\n", expressiong("1^0|1", 1));
    printf("%d\n", expressiong("1^0|0|1", 0));
}
