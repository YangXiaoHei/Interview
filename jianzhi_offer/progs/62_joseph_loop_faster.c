#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int joseph_loop(int n, int k)
{
    /* f(n) = (f(n - 1) + m) % n */
    
    int last = 0;
    for (int i = 2; i <= n; i++)
        last = (last + k) % i;
    return last;
}

int main(int argc, char *argv[])
{
    int n = randWithRange(5, 20);
    int r = randWithRange(1, 15);
    printf("n = %-3d r = %-3d\n", n, r);
    printf("%d\n", joseph_loop(n, r));
}
