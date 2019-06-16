#include <stdio.h>

int n = 0;
int cnt = 0;

void dfs(unsigned a, unsigned b, unsigned c)
{
    if (b == (1 << n) - 1) {
        cnt++;
        return;
    }

    unsigned mask = (1 << n) - 1;
    unsigned d = ~(a | b | c);
    d &= mask;

    while (d) {
        unsigned ok = d & -d;
        dfs((a | ok) << 1, b | ok, (c | ok) >> 1);
        d -= ok;
    }
}

int main(int argc, char *argv[])
{
    for (n = 6; n <= 13; n++) {
        cnt = 0;
        dfs(0, 0, 0);
        printf("%d queen, total = %-3d\n", n, cnt);
    }
}
