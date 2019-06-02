#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int incr(char *num, size_t len, int k)
{
    int i = len - 1;
    int carry = k;
    int digit;
    while (i >= 0 && carry) {
        digit = num[i] - '0';
        digit += carry;
        carry = digit >= 10;
        num[i] = (carry ? 0 : digit) + '0';
        i--;
    }
    return i < 0 && carry;
}

void print_num(char *num)
{
    while (*num && *num == '0') num++;
    printf("%s\n", num);
}

void print_max_n_num(int n)
{
    char *num = malloc(n + 1);
    if (!num) exit(1);
    num[n] = 0;

    memset(num, '0', n);
    while (!incr(num, n, 1)) 
        print_num(num);
    free(num);
}

void test(void)
{
    char num[] = "0000";
    for (int i = 0; i < 10000; i++) {
        int t = incr(num, strlen(num), 1);
        printf("%d  %s\n", t, num);
    }
}

int main(int argc, char *argv[])
{
    print_max_n_num(10);
}
