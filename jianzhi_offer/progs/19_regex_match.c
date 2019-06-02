#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int match(const char *regex, const char *str)
{
    if (!*regex && !*str)
        return 1;

    if (*str && !*regex)
        return 0;

    if (regex[1] == '*') {
        if ((*regex != *str && *regex != '.') || !*str)
            return match(regex + 2, str);

        return match(regex + 2, str + 1) || 
               match(regex, str + 1) || 
               match(regex + 2, str);
    }

    if (*regex == *str || (*str && *regex == '.'))
        return match(regex + 1, str + 1);

    return 0;
}

int is_match(const char *regex, const char *str)
{
    if (!regex && !str)
        return 1;

    if (!!regex ^ !!str)
        return 0;

    return match(regex, str);
}

void test(const char *name, const char *str, const char *regex, int expected)
{
    if (is_match(regex, str) == expected)
        printf("succ\n");
    else
        printf("failed! str=%s regex=%s\n", str, regex);
}

int main(int argc, char *argv[])
{
    test("test01", "", "", 1);
    test("test02", "", ".*", 1);
    test("test03", "", ".", 0);
    test("test04", "", "c*", 1);
    test("test05", "a", ".*", 1);
    test("test06", "a", "a.", 0);
    test("test07", "a", "", 0);
    test("test08", "a", ".", 1);
    test("test09", "a", "ab*", 1);
    test("test10", "a", "ab*a", 0);
    test("test11", "aa", "aa", 1);
    test("test12", "aa", "a*", 1);
    test("test13", "aa", ".*", 1);
    test("test14", "aa", ".", 0);
    test("test15", "ab", ".*", 1);
    test("test16", "ab", ".*", 1);
    test("test17", "aaa", "aa*", 1);
    test("test18", "aaa", "aa.a", 0);
    test("test19", "aaa", "a.a", 1);
    test("test20", "aaa", ".a", 0);
    test("test21", "aaa", "a*a", 1);
    test("test22", "aaa", "ab*a", 0);
    test("test23", "aaa", "ab*ac*a", 1);
    test("test24", "aaa", "ab*a*c*a", 1);
    test("test25", "aaa", ".*", 1);
    test("test26", "aab", "c*a*b", 1);
    test("test27", "aaca", "ab*a*c*a", 1);
    test("test28", "aaba", "ab*a*c*a", 0);
    test("test29", "bbbba", ".*a*a", 1);
    test("test30", "bcbbabab", ".*a*a", 0);
}
