#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

char *add(const char *num1, const char *num2, char *buf, int buflen)
{
    if (!num1 || !num2 || !*num1 || !*num2)
        return NULL;

    int len1 = strlen(num1), len2 = strlen(num2);
    int carry = 0;
    int i = len1 - 1, j = len2 - 1;
    
    int k = max(len1, len2) + 1 - 1;
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
        memcpy(buf, buf + 1, max(len1, len2));
        buf[max(len1, len2)] = 0;
    }
    return buf;
}

int main(int argc, char *argv[])
{
    char buf[100];
    int size = sizeof(buf);
    printf("%s\n", add("123", "456", buf, size));
    printf("%s\n", add("999", "1", buf, size));
    printf("%s\n", add("999", "999", buf, size));
}
