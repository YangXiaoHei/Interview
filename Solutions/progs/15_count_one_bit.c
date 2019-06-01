#include <stdio.h>

int count_bit(int x)
{
    int n = 0;
    while (x) {
        n++;
        x &= x - 1;
    }
    return n;
}

int main(int argc, char *argv[])
{
    printf("%d\n", count_bit(3)); 
    printf("%d\n", count_bit(15)); 
    printf("%d\n", count_bit(13)); 
}
