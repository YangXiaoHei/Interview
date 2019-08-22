#include "ds.h"

int match_core(const char *str, int slen, const char *exp, int elen, int si, int ei)
{
    if (ei == elen)
        return si == slen;

    if (ei == elen - 1 || exp[ei + 1] != '*')
        return si != slen && 
               (str[si] == exp[ei] || exp[ei] == '.') &&
               match_core(str, slen, exp, elen, si + 1, ei + 1);

    while (si != slen && (exp[ei] == '.' || exp[ei] == str[si])) {
        if (match_core(str, slen, exp, elen, si, ei + 2))
            return 1;
        si++;
    }
    return match_core(str, slen, exp, elen, si, ei + 2);
}

int match(const char *str, const char *exp)
{
    if (!str || !exp)
        return 0;
    
    int slen = strlen(str), elen = strlen(exp);
    return match_core(str, slen, exp, elen, 0, 0);
}

int main(int argc, char *argv[])
{
    printf("%d\n", match("aaaaaa", ".*"));
    printf("%d\n", match("abcdefg", ".*"));
    printf("%d\n", match("abcdefg", "ab.*"));
    printf("%d\n", match("aabbccdd", "a*b*c*d*"));
    printf("%d\n", match("aabbccdd", "a*.*.*d*"));
    printf("%d\n", match("aabbccdd", "aabbc..."));
}
