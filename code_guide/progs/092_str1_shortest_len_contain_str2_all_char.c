#include "ds.h"

int shortest_len(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return 0;

    int map[256] = { 0 };
    int len1 = strlen(str1), len2 = strlen(str2);
    for (int i = 0; i < len2; i++)
        map[str2[i]]++;

    int left = 0, right = 0, match = len2;
    int minlen = 2147483647;

    while (right < len1) {
        map[str1[right]]--;
        if (map[str1[right]] >= 0)
            match--;

        if (match == 0) {
            while (map[str1[left]] < 0) 
                map[str1[left++]]++;

            int newlen = right - left + 1;
            if (newlen < minlen)
                minlen = newlen;

            map[str1[left++]]++;
            match++;
        }
        right++;
    }
    return minlen == 2147483647 ? 0 : minlen;
}

int main(int argc, char *argv[])
{
    const char *str1 = "adabbca";
    const char *str2 = "abc";
    printf("%d\n", shortest_len(str1, str2));    
}
