#include "ds.h"

int is_match_core(const char *str, int slen, const char *exp, int elen, int si, int ei)
{
    if (ei == elen)
        return si == slen;

    if (ei + 1 == elen || exp[ei + 1] != '*')
        return si != slen &&
               (str[si] == exp[ei] || exp[ei] == '.') &&
               is_match_core(str, slen, exp, elen, si + 1, ei + 1);

    while (si != slen && (str[si] == exp[ei] || exp[ei] == '.')) {
        if (is_match_core(str, slen, exp, elen, si, ei + 2))
            return  1;
        si++;
    }
    return is_match_core(str, slen, exp, elen, si, ei + 2);
}

int is_match(const char *str, const char *exp)
{
    if (!exp || !str)
        return 0;

    int slen = strlen(str), elen = strlen(exp);
    return is_match_core(str, slen, exp, elen, 0, 0);
}

int main(int argc, char *argv[])
{
    printf("%d\n", is_match("", "")); 
    printf("%d\n", is_match("abc", "a.c")); 
    printf("%d\n", is_match("abc", "a.*c")); 
    printf("%d\n", is_match("abbbbc", "a.*c")); 
    printf("%d\n", is_match("abbbbc", "a..*c")); 
    printf("%d\n", is_match("abbbbc", "ab.*c")); 
    printf("%d\n", is_match("abbbbc", "abc.*c")); 
}
