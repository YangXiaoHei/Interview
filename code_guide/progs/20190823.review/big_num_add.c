#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

char *big_num_add(const char *num1, const char *num2, char *buf, int buflen)
{
    int len1 = strlen(num1), len2 = strlen(num2);
    if (buflen < max(len1, len2) + 1 + 1)
        return NULL;

    int i = len1 - 1, j = len2 - 1;
    int carry = 0;
    int k = max(len1, len2);
    buf[k + 1] = 0;
    while (carry || i >= 0 || j >= 0) {
        int a = i >= 0 ? num1[i--] - '0' : 0;
        int b = j >= 0 ? num2[j--] - '0' : 0;
        int c = a + b + carry;
        carry = c >= 10;
        c %= 10;
        buf[k--] = c + '0';
    }
    if (k == 0) {
        memcpy(buf, buf + 1, max(len1, len2) + 1);
        buf[max(len1, len2)] = 0;
    }

    return buf;
}

int main(int argc, char *argv[])
{
    char buf[1000];
    printf("%s\n", big_num_add("1234", "6", buf, sizeof(buf)));
    printf("%s\n", big_num_add("1234", "9999", buf, sizeof(buf)));
    printf("%s\n", big_num_add("1234", "2222", buf, sizeof(buf)));
}
