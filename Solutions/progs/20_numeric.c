#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int scan_ui(char **str)
{
    char *old = *str;
    char *p = *str;
    while (*p && *p >= '0' && *p <= '9')
        p++;
    *str = p;
    return p > old; 
}

int scan_i(char **str)
{
    char *p = *str;
    if (*p == '+' || *p == '-')
        p++;
    *str = p;
    return scan_ui(str);
}

int is_numeric(char *str)
{
    int numeric = scan_i(&str);

    if (*str == '.') {
        ++str;
        numeric = scan_ui(&str) || numeric;
    }

    if (*str == 'e' || *str == 'E') {
        ++str;
        numeric = scan_i(&str) && numeric;
    }

    return numeric && !*str;
}

int main(int argc, char *argv[])
{
    printf("%d\n", is_numeric("+100"));
    printf("%d\n", is_numeric("-100"));
    printf("%d\n", is_numeric("3.141515"));
    printf("%d\n", is_numeric("-1E-16"));
    printf("%d\n", is_numeric("12e-9"));
}
