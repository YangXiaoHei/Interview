#include <stdio.h>

double fuck(double x, unsigned exp)
{
    if (exp == 0)
        return 1;

    if (exp == 1)
        return x;

    double r = fuck(x, exp >> 1);
    r *= r;
    if (exp & 1)
        r *= x;
    return r;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 40; i++)
        printf("%.2f\n", fuck(2, i));
}
