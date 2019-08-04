#include "ds.h"

int is_deformation(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return 0;

    int len1 = strlen(str1), len2 = strlen(str2);
    if (len1 != len2)
        return 0;

    // 统计字符的数目
    int h[256] = { 0 };
    for (char *p = (char *)str1; *p; p++)
        h[*p]++;

    for (char *p = (char *)str2; *p; p++)
        if (h[*p]-- == 0)
            return 0;

    return 1;
}

int main(int argc, char *argv[])
{
    char str1[100], str2[100];
    while (scanf("%s %s", str1, str2) != EOF)
       printf("is deformation : %d\n", is_deformation(str1, str2)); 
}
