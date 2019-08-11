#include "ds.h"

char* reverse(char *beg, char *end)
{
    char *head = beg;
    while (beg < end) {
        char t = *beg;
        *beg = *end;
        *end = t;
        beg++, end--;
    } 
    return head;
}

char *reverse_part(char *str, int k) 
{
    int len = strlen(str);
    if (k > len)
        return str;

    reverse(str, str + k - 1);
    reverse(str + k, str + len - 1);
    reverse(str, str + len - 1);
    return str;
}

int main(int argc, char *argv[])
{
    char str[] = "123456789";
    printf("%s\n", reverse_part(str, 3));
}
