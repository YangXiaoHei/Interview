#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_num(char *n)
{
    while (*n && *n == '0') n++;
    printf("%s\n", n);
}

void print_core(char *num, int n, int idx)
{
    if (idx == n - 1) {
        print_num(num);
        return;
    }

    for (int i = 0; i < 10; i++) {
        num[idx + 1] = i + '0';
        print_core(num, n, idx + 1);
    }
}

void print_max_n_num(int n)
{
    if (n <= 0)
        return;

    char *num = malloc(n + 1);
    if (!num) exit(1);
    num[n] = 0;

    for (int i = 0; i < 10; i++) {
        num[0] = i + '0';
        print_core(num, n, 0);
    }

    free(num);
}

int main(int argc, char *argv[])
{
    print_max_n_num(4);
}
