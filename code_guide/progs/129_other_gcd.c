#include "ds.h"

int gcd(int m, int n)
{
    return n == 0 ? m : gcd(n, m % n);
}

int xgcd(int m, int n)
{
    int q, r;
    while (n) {
        q = m / n;
        r = m % n;
        m = n;
        n = r;
    }
    return m;
}


int main()
{
    int a = randWithRange(1, 100);
    int b = randWithRange(1, 100);
    printf("%d %d gcd : %d xgcd : %d\n", a, b, gcd(a, b), xgcd(a, b));
}
