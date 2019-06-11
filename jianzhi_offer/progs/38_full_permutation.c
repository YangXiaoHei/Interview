#include <stdio.h>

void swap(char *p, char *q)
{
    char tmp = *p;
    *p = *q;
    *q = tmp;
}

void full_permutation_core(char *str, char *b)
{
    if (!*b) {
        printf("%s\n", str);
        return;
    }

    for (char *c = b; *c; c++) {
        swap(b, c);
        full_permutation_core(str, b + 1);
        swap(b, c);
    }
}

void full_permutation(char *str)
{
    if (!str)
        return;
    full_permutation_core(str, str);
}

int main(int argc, char *argv[])
{
    char str[] = "abcd";
    full_permutation(str);
}
