#include <stdio.h>

double powh(double x, unsigned exp)
{
    if (exp == 0)
        return 1;

    double sum = 1;
    double tmp = x;
    while (exp) {
        if (exp & 1)
            sum *= tmp;
        tmp *= tmp;
        exp >>= 1;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 40; i++) 
        printf("%.3f\n", powh(2, i));
}
