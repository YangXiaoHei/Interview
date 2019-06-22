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
    for (; i < len; i++)
        if (arr[str[i]] == 1)
            break;

    return str[i];
}

int main(int argc, char *argv[])
{
    const char *str = "abaccdeff";
    printf("%-3c\n", find_only_one(str, strlen(str)));
}
