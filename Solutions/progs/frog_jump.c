#include <stdio.h>

unsigned long total_ways(unsigned floors)
{
    if (floors <= 1) return 1;
    if (floors == 2) return 2;

    unsigned long pre = 1, cur = 2, next = 0;
    for (unsigned i = 3; i <= floors; i++) {
        next = pre + cur;
        pre = cur;
        cur = next;
    }
    return next;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 50; i++) 
        printf("frog jump %d floors have %lu ways\n", i, total_ways(i));
}
