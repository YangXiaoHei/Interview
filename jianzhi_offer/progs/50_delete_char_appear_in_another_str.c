#include <stdio.h>
#include <string.h>

void delete_char(char *str, const char *to_delete)
{
    if (!str || !*str || !to_delete || !*to_delete)
        return;

    int arr[256] = { 0 };
    const char *t = to_delete;
    while (*t)
        arr[*t++]++;

    char *p = str, *q = str;
    while (1) {
        while (*q && arr[*q]) q++;
        if (!*q) {
           *p = 0;
            break; 
        }
        *p++ = *q++;
    }
}


int main(int argc, char *argv[])
{
    char str[] = "We are Students.";
    char *to_del = "aeiou";

    delete_char(str, to_del);

    printf("%s\n", str);
}
