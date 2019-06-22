#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete_dup_char(char *str)
{
    int arr[256] = { 0 };
    char *p = str, *q = str;
    while (1) {
        while (*q && arr[*q]) q++;
        if (!*q) {
            *p = 0;
            break;
        }

        arr[*q]++;
        *p++ = *q++;
    }
}

int main(int argc, char *argv[])
{
    char str[] = "googleeeaaaabbbeeedddccc";
    delete_dup_char(str);
    printf("%s\n", str);
}
