#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char buf[8192] = { 0 };
int cur = 0;

void full_combination_core(const char *str, int len, int idx, int n)
{
    if (cur == n) {
        printf("%s\n", buf);
        return;
    }

    for (int i = idx; i < len; i++) {
        buf[cur++] = str[i];
        full_combination_core(str, len, i + 1, n);
        buf[--cur] = 0;
    }
}

void full_combination(const char *str, int n)
{
    int len = strlen(str);
    assert(len < sizeof(buf));
    full_combination_core(str, len, 0, n);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i <= 5; i++)
        full_combination("abcde", i);    
}
