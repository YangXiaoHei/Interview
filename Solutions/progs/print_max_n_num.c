#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void incr(char *num, size_t len, int k)
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
}

void print_max_n_num(int n)
{
    char *num = malloc(n + 1);
    if (!num) exit(1);
    num[n] = 0;

    char *max = malloc(n + 1);
    if (!max) exit(1);
    max[n] = 0;

    memset(num, '0', n);
    memset(max, '9', n);
    while (strcmp(max, num) != 0)  {
        incr(num, n, 1);
        printf("%s\n", num);
    }
    free(num);
}

void test(void)
{
    char num[] = "00000";
    for (int i = 0; i < 1000; i++) {
        incr(num, strlen(num), 1);
        printf("%s\n", num);
    }
}

int main(int argc, char *argv[])
{
    print_max_n_num(5);
}
