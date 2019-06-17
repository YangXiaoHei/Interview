#include <stdio.h>
#include <math.h>

int count_num_of_digit(int digit)
{
    if (digit < 0)
        return 0;

    if (digit == 1)
        return 10;

    return 9 * pow(10, digit - 1);
}

int beg_num_of_digit(int digit)
{
    if (digit == 0)
        return 0;

    return pow(10, digit - 1);
}

int digit_of_num_seq(int idx)
{
    int i = 1;
    while (idx > count_num_of_digit(i)) {
        idx -= count_num_of_digit(i) * i;
        i++;
    }

    int num = beg_num_of_digit(i) + idx / i;
    int exclude = i - idx % i - 1;
    while (exclude--)
        num /= 10;
    return num % 10;
}

int main(int argc, char *argv[])
{
    printf("%d\n", digit_of_num_seq(1001));
}
