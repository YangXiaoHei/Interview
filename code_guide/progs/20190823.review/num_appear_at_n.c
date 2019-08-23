#include "ds.h"

int beg_of_digit(int n)
{
    if (n <= 0)
        return 0;

    if (n == 1)
        return 0;

    return pow(10, n - 1);
}

int num_of_digit(int n)
{
    if (n <= 0)
        return 0;
    int end = beg_of_digit(n + 1);
    int beg = beg_of_digit(n);
    return (end - beg) * n; 
}

int digits_of_num(int n)
{
    int res = 0;
    while (n) {
        n /= 10;
        res++;
    }
    return res;
}

int fun(int n)
{
    // 0 1 2 3 4 5 6 7 8 9
    // 1 0 1 2 1 3 1 4 1 5
    // 1 6 
    if (n < 1)
        return 0;
    
    int digit = 1;
    int num = num_of_digit(digit);
    while (n > num) {
        n -= num;
        num = num_of_digit(++digit);
    }

    int f = beg_of_digit(digit) + n / digit;
    int m = n % digit;
    if (m == 0)
        return f % 10;

    f++;
    int r = digits_of_num(f) - m;
    while (r--)
        f /= 10;

    return f % 10;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 1000; i++) 
        printf("%2d", fun(i));
    printf("\n");
}
