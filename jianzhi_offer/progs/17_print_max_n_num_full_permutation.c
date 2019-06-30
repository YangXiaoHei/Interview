#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_no_leading_zero(const char *str)
{
    while (*str && *str == '0') str++;
    if (!*str)
        --str;
    printf("%s\n", str);
}

void print_max_n_core(char *str, int n, int idx)
{
    if (idx == n) {
        print_no_leading_zero(str);
        return;
    }

    for (int i = 0; i < 10; i++) {
        str[idx] = i + '0';
        print_max_n_core(str, n, idx + 1);
    }
}

void print_max_n(int n)
{
    if (n <= 0)
        return;

    char *str = malloc(n + 1);
    str[n] = 0;
    print_max_n_core(str, n, 0);
    free(str);
}


int main(int argc, char *argv[])
{
    print_max_n(6);
}
