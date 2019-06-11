#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char buf[8192] = { 0 };
int n = 0;

void full_combination_core(const char *str, int len, int l, int idx)
{
    if (l > len) 
        return;

    if (idx == 0) {
        printf("%s\n", buf);
        return;
    }

    buf[n++] = str[l];
    full_combination_core(str, len, l + 1, idx - 1);
    buf[--n] = 0;
    full_combination_core(str, len, l + 1, idx);
}

void full_combination(const char *str, int n)
{
    int len = strlen(str);
    assert(len < sizeof(buf));
    for (int i = 1; i <= n; i++)
        full_combination_core(str, len, 0, i);
}

int main(int argc, char *argv[])
{
    full_combination("abcde", 5);    
}
