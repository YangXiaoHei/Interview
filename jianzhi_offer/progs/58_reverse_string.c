#include <stdio.h>
#include <string.h>

void reverse_help(char *beg, char *end)
{
    if (beg == end)
        return;

    char *lo = beg < end ? beg : end;
    char *hi = lo == beg ? end : beg;
    while (lo < hi) {
        char tmp = *lo;
        *lo = *hi;
        *hi = tmp;
        ++lo;
        --hi;
    }
}

void reverse_string(char *str, int len)
{
    if (!str || !*str || len <= 1)
        return;
    reverse_help(str, str + len - 1);
    char *left = str, *right = str;
    while (1) {
        while (*right && *right == ' ')
            right++;
        if (!*(left = right))
            break;

        while (*right && *right != ' ')
            right++;
        reverse_help(left, right - 1);
        if (!*(left = right))
            break;
    }
}


int main(int argc, char *argv[])
{
    {
        char str[] = "I am a student.";
        reverse_string(str, strlen(str));
        printf("%s\n", str);
    }
    {
        char str[] = "I don't know either";
        reverse_string(str, strlen(str));
        printf("%s\n", str);
    }
    {
        char str[] = "reverse string test fuck";
        reverse_string(str, strlen(str));
        printf("%s\n", str);
    }
    {
        char str[] = "this is a good idea";
        reverse_string(str, strlen(str));
        printf("%s\n", str);
    }
}
