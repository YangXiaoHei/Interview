#include "ds.h"

int valid(const char *str)
{
    if (!str || !*str)
        return 0;

    int status = 0;
    for (char *p = (char *)str; *p; p++) {
        if (*p != '(' && *p != ')')
            return 0;

        if (*p == ')' && --status < 0)
            return 0;

        if (*p == '(')
            status++;
    }
    return status == 0;
}

int main(int argc, char *argv[])
{
    {
        const char *str = "(()";
        printf("%d\n", valid(str));
    }
    {
        const char *str = "()";
        printf("%d\n", valid(str));
    }
    {
        const char *str = "()())(()";
        printf("%d\n", valid(str));
    }
    {
        const char *str = "((((((()))))))))))";
        printf("%d\n", valid(str));
    }
}
