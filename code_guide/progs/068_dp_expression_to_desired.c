#include "ds.h"

int is_valid(const char *str, int len)
{
    if (!(len & 1))
        return 0;

    for (int i = 0; i < len; i += 2)
        if (str[i] != '0' && str[i] != '1')
            return 0;

    for (int i = 1; i < len; i += 2)
        if (str[i] != '^' && str[i] != '&' && str[i] != '|')
            return 0;

    return 1;
}

int expression_to_desired(const char *str, int desired)
{
    if (!str || !*str)
        return 0;

    int len = strlen(str);
    if (!is_valid(str, len))
        return 0;

    int *t = malloc(sizeof(int) * len * len);
    int *f = malloc(sizeof(int) * len * len);
    memset(t, 0, sizeof(int) * len * len);
    memset(f, 0, sizeof(int) * len * len);

#define T(i, j) t[(i) * len + (j)]
#define F(i, j) f[(i) * len + (j)]

    T(0, 0) = str[0] == '1';
    F(0, 0) = str[0] == '0';

    for (int i = 2; i < len; i += 2) {
        T(i, i) = str[i] == '1';
        F(i, i) = str[i] == '0';

        for (int j = i - 2; j >= 0; j -= 2) {
            for (int k = j; k < i; k += 2) {
                printf("(i, j, k) = (%d, %d, %d)\n", i, j, k);
                switch(str[k + 1]) {
                    case '^' : {
                        T(j, i) += T(j, k) * F(k + 2, i) + F(j, k) * T(k + 2, i);
                        F(j, i) += F(j, k) * F(k + 2, i) + T(j, k) * T(k + 2, i);
                   } break;
                    case '&' : {
                        T(j, i) += T(j, k) * T(k + 2, i);
                        F(j, i) += F(j, k) * T(k + 2, i) + T(j, k) * F(k + 2, i) + F(j, k) * F(k + 2, i); 
                   } break;
                    case '|' : {
                        T(j, i) += T(j, k) * F(k + 2, i) + F(j, k) * T(k + 2, i) + T(j, k) * T(k + 2, i);
                        F(j, i) += F(j, k) * F(k + 2, i);
                   } break;
                }
            }
        }
    }

    int res = desired ? T(0, len - 1) : F(0, len - 1);
    free(t);
    free(f);
    return res;
}

int main(int argc, char *argv[])
{
    const char *str = "1^0|0|1";
    int desired = 0;
    printf("res = %d\n", expression_to_desired(str, desired));
}
