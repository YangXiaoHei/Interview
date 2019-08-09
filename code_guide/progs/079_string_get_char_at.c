#include "ds.h"

char get_char_at(const char *str, int idx)
{
    if (!str || !*str || idx < 0)
        return 0;

    int count = 0;
    int read_char = 1;
    int sum = 0;
    char cur = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '_') {
            read_char = !read_char;
        } else if (read_char) {
            sum += count;
            if (sum > idx)
                return cur;
            cur = str[i];
            count = 0;
        } else {
            count = count * 10 + str[i] - '0';
        }
    }
    return sum + count > idx ? cur : 0;
}

int main(int argc, char *argv[])
{
    printf("%c\n", get_char_at("a_3_b_1_c_9_d_20_e_1", 5));
}
