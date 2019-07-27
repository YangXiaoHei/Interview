#include "ds.h"

int h = 0;

void helper(int n, const char *from, const char *mid, const char *to)
{
    if (n == 1) {
        printf("move from %s to %s (%d)\n", from, to, h++);
        return;
    }
    helper(n - 1, from, to, mid);
    helper(1, from, mid, to);
    helper(n - 1, mid, from, to);
}

void hanoi(int n)
{
    if (n < 0)
        return;

    helper(n, "left", "mid", "right");
}

int main(int argc, char *argv[])
{
    int n = 0;
    scanf("%d", &n);
    hanoi(n); 
}
