#include "ds.h"

char* remove_k_zero(char *str, int k)
{
    if (!str || !*str || k < 0)
        return str;

    int match = 0;
    char *p;
    int flag = 0;
    int len = 0;
    for (p = str; *p; p++, len++) {
        if (*p == '0') {
            match++;
        } else {
            if (match == k) {
                char *q = p - 1;
                for (int j = k; j > 0; j--)
                    *q-- = 0;
                flag = 1;
            }
            match = 0;
        }
    }
    if (match == k) {
        char *q = p - 1;
        for (int j = k; j > 0; j--)
            *q-- = 0;
        flag = 1;
    }
    if (!flag) return str;

    int j = 0;
    for (int i = 0; i < len; i++)
       if (str[i])
          str[j++] = str[i]; 
    str[j] = 0;
    return str;

}

int main(int argc, char *argv[])
{
    {
        // 123450600007
        char str[] = "123004005060000700";
        printf("%s\n", remove_k_zero(str, 2));    
    }
    {
        char str[] = "1234000506000";
        printf("%s\n", remove_k_zero(str, 2));    
    }

}
