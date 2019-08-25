#include "ds.h"

int parenthese_pair(const char *str)
{
    if (!str || !*str)
        return 0;

    int status = 0;
    for (char *p = (char *)str; *p; p++) {
        if (*p != '(' && *p != ')')
            continue;

        if (*p == '(')
            status++;

        if (*p == ')' && --status < 0)
           return 0; 
    }
    return 1;
}

int main()
{
    printf("%d\n", parenthese_pair("()()((()))"));
    printf("%d\n", parenthese_pair("()()(()))"));
    printf("%d\n", parenthese_pair("(((((())))))"));
}
