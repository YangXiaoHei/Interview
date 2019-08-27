#include "ds.h"

int shortest(const char *str1, const char *str2)
{
    if (!str1 || !*str1 || !str2 || !*str2)
        return -1;

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len2 > len1)
        return -1;

    int map[256] = { 0 };
    for (char *p = (char *)str2; *p; p++)
        map[*p]++;

    int left = 0, right = 0;
    int match = len2;
    int res = 2147483647;
    while (right < len1) {
        map[str1[right]]--;
        if (map[str1[right]] >= 0)
            match--; 

        if (match == 0) {
            while (map[str1[left]] < 0)
                map[str1[left++]]++;

            int tmp = right - left + 1;
            if (tmp < res)
                res = tmp;

            match++;
            map[str1[left++]]++;
        }
        right++;
    }
    return res == 2147483647 ? -1 : res;
}

int main()
{
    printf("%d\n", shortest("abcde", "ac"));
    printf("%d\n", shortest("12345", "344"));
}
