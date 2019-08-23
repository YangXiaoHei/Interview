#include "ds.h"

int is_anagram(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return 0;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 != len2)
        return 0;

    int map[256] = { 0 };
    for (char *p = (char *)str2; *p; p++)
        map[*p]++;

    for (char *p = (char *)str1; *p; p++) 
        if (map[*p]-- < 0)
            return 0;

    return 1;
}

int main(int argc, char *argv[])
{
    printf("%d\n", is_anagram("abc", "cab"));
    printf("%d\n", is_anagram("aabccdd", "acdabcd"));
    printf("%d\n", is_anagram("aabccdd", "cdabcd"));
}
