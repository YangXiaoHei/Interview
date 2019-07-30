#include "ds.h"

void hanoi_core(int n, const char *from, const char *buffer,  const char *to)
{
    if (n == 1) {
        printf("move %s to %s\n", from, to);
        return;
    }

    hanoi_core(n - 1, from, to, buffer);
    hanoi_core(1, from, buffer, to);
    hanoi_core(n - 1, buffer, from, to);
}

void hanoi(int n)
{
    if (n < 1)
        return;

    hanoi_core(n, "left", "mid", "right");
}

int main(int argc, char *argv[])
{
    hanoi(4);
}
