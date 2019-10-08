#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int rand1_100(void)
{
    return rand() % 100 + 1;
}

int randx2()
{
    int r1 = rand1_100();
    int r2 = rand1_100();
    return max(r1, r2);
}

int randxk(int k)
{
    int maxv = -2147483647-1;
    while (k--) 
        maxv = max(maxv, rand1_100());
    return maxv;
}

void test2(int times, int x, int k)
{
    int stat[2] = { 0 };
    for (int i = 0; i < times; i++) {
        int r = randxk(k);
        if (r <= x)
            stat[0]++;
        else
            stat[1]++;
    }
    double s = 1;
    while (k--)
        s *= (x * 1.0 / 100);
    printf("standard : %.5f\n", s);
    printf("%.5f %.5f\n", stat[0] * 1.0 / times, stat[1] * 1.0 / times);
}
void test(int times, int x)
{
    int stat[2] = { 0 };
    for (int i = 0; i < times; i++) {
        int r = randx2();
        if (r <= x)
            stat[0]++;
        else
            stat[1]++;
    }
    printf("standard : %.5f\n", (x * 1.0 / 100) * (x * 1.0 / 100));
    printf("%.5f %.5f\n", stat[0] * 1.0 / times, stat[1] * 1.0 / times);
}

int main()
{
    test(100000, 30);
    test2(100000, 50, 6);
}
