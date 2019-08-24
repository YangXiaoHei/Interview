#include "ds.h"

char what_at_k(const char *str, int k)
{
    if (!str || !*str || k < 0)
        return 0;
    int read_char = 1, read_num = 0;
    int n = 0;
    char c = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '_') {
            read_char = !read_char;
            read_num = !read_num;
        } else if (read_char) {
            if (k < n) 
                return c;
            k -= n;
            c = str[i];
            n = 0;
        } else if (read_num) {
            n = n * 10 + str[i] - '0';
        }
    }
    if (k < n)
        return c;
    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i <= 20; i++)
        printf("i = %d %c\n", i, what_at_k("a_3_b_4_c_5_d_6", i));
}
