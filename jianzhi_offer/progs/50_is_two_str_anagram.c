#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_anagram(const char *str1, int len1, const char *str2, int len2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return 0;

    if (len1 != len2)
        return 0;

    int arr[256] = { 0 };
    for (const char *p = str1; *p; p++)
        arr[*p]++;

    int cnt = 0;
    for (const char *p = str2; *p; p++)
        if (arr[*p])
            cnt++;
    return cnt == len2;
}

int main(int argc, char *argv[])
{
    {
        const char *str1 = "silent";
        const char *str2 = "listen";
        printf("%d\n", is_anagram(str1, strlen(str1), str2, strlen(str2)));
    }
    {
        const char *str1 = "evil";
        const char *str2 = "live";
        printf("%d\n", is_anagram(str1, strlen(str1), str2, strlen(str2)));
    }
    {
        const char *str1 = "ilent";
        const char *str2 = "listen";
        printf("%d\n", is_anagram(str1, strlen(str1), str2, strlen(str2)));
    }
}
