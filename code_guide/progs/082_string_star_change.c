#include "ds.h"

char *change_star(char *str)
{
    int len = strlen(str);
    int j = len - 1;
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] != '*')
           str[j--] = str[i]; 
    }
    while (j--)
        str[j] = '*';
    return str;
}

int main(int argc, char *argv[])
{
    char buf[] = "*123**4*5**6**";
    printf("%s\n", change_star(buf));
}
