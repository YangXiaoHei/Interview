#include <stdio.h>

int how_many_bit(int x, int y)
{
    int s = x ^ y;
    int n = 0;
    while (s) {
        n++;
        s &= (s - 1);
    }
    return n;
}

int main(int argc, char *argv[])
{
    printf("%d\n", how_many_bit(12, 15));
}
