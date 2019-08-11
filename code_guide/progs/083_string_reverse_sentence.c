#include "ds.h"

char * reverse(char *beg, char *end)
{
    char *head = beg;
    while (beg < end) {
        char t = *beg;
        *beg = *end;
        *end = t;
        beg++; end--;
    }
    return head;
}

char* reverse_sentence(char *str)
{
    int len = strlen(str);
    reverse(str, str + len - 1);

    char *beg = NULL, *end = NULL;
    for (int i = 0; i < len;) {
        if (str[i] != ' ') {
            beg = !beg ? str + i : beg;
            end = str + i;
            i++;
        } else {
           reverse(beg, end);
           beg = end = NULL; 
           while (i < len && str[i] == ' ') i++;
        }
    }
    if (beg && end)
        reverse(beg, end);
    return str;
}

int main(int argc, char *argv[])
{
    char buf[] = "789 1234 hello world yes ok";
    printf("%s\n", reverse_sentence(buf));
}
