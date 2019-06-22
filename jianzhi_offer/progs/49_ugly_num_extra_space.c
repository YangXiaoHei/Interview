#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int ugly_num(int idx)
{
    if (idx <= 0)
        return 1;

    int *tmp = malloc(sizeof(int) * (idx + 1));

    tmp[0] = 1;
    int next_ugly_idx = 1;

    int *p2 = tmp;
    int *p3 = tmp;
    int *p5 = tmp;
    
    while (next_ugly_idx <= idx) {
        int minv = min(*p2 * 2, *p3 * 3, *p5 * 5);
        tmp[next_ugly_idx] = minv;

        while (*p2 * 2 <= tmp[next_ugly_idx])
            p2++;
        while (*p3 * 3 <= tmp[next_ugly_idx])
            p3++;
        while (*p5 * 5 <= tmp[next_ugly_idx])
            p5++;

        ++next_ugly_idx;
    }
    int val = tmp[idx];
    free(tmp);
    return val; 
}

int main(int argc, char *argv[])
{
    printf("%-5d\n", ugly_num(1500));
}
