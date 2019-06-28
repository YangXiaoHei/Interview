#include <stdio.h>
#include "tool.h"

int add(int a, int b)
{
    int sum = 0;
    int carry = 0;
    do {
        sum = a ^ b;
        carry = (a & b) << 1;
        a = sum;
        b = carry;
    } while (carry);

    return sum;
}

int main(int argc, char *argv[])
{
    int a = randWithRange(0, 100);
    int b = randWithRange(0, 100);

    printf("%d %d\n", a + b,  add(a, b));
}
