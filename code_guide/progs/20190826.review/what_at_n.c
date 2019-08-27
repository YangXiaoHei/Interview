#include "ds.h"

int beg_of_digit(int n)
{
    if (n == 1)
        return 0;

    return pow(10, n - 1);
}

int num_of_digit(int n)
{
    if (n == 1)
        return 10;

    int res = pow(10, n) - 1 - beg_of_digit(n) + 1;
    res *= n;
    return res;
}

char what(int n)
{
    if (n < 1)
        return 0;

    int d = 1;
    int num = num_of_digit(d);
    while (n > num) {
        n -= num;
        num = num_of_digit(++d); 
    }
    int beg = beg_of_digit(d);
    int acc = n / d - 1;
    int final = beg + acc;
    int m = n % d;
    char res = 0;
    if (m) {
        final++;
        int r = d - m;
        while (r--)
            final /= 10;
    }
    return final % 10 + '0';
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 1000; i++) 
        printf("%c ", what(i));
}
