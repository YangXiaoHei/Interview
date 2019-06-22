#include <stdio.h>
#include <string.h>

char find_only_one(const char *str, int len)
{
    if (!str || !*str || len <= 0)
        return 0;

    int arr[256] = { 0 };
    for (int i = 0; i < len; i++)
        arr[str[i]]++;

    int i = 0;
    for (; i < 256; i++)
        if (arr[i] == 1)
            break;

    if (i == 256)
        return 0;

    return i;
}

int main(int argc, char *argv[])
{
    const char *str = "abaccdeff";
    printf("%-3c\n", find_only_one(str, strlen(str)));
}
