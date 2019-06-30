#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int count_1(int m)
{
    int count = 0;
    while (m) {
        count += (m % 10) == 1;
        m /= 10;
    }
    return count;
}

int count_digit_of_1_check(int n)
{
    int count = 0;
    for (int i = 1; i <= n; i++)  {
        count += count_1(i); 
#ifdef DEBUG
        if (count_1(i))
            printf("%-3d\n", i);
#endif
    }
    return count;
}

int simple_atoi(const char *beg, const char *end)
{
    if (beg > end)
        return 0;

    int sum = 0;
    while (*beg && beg <= end)
        sum = sum * 10 + *beg++ - '0';
    return sum;
}

int pow10(int len)
{
    int sum = 1;
    while (len--)
        sum *= 10;
    return sum;
}

int count_digit_of_1_core(const char *beg, const char *end)
{
    int sum = 0;
    int c = 0;
    for (const char *cur = beg; cur <= end; cur++) {
        c = *cur - '0';
        if (cur == beg) {
            if (c == 1) 
               sum += simple_atoi(cur + 1, end) + 1;
            else
               sum += pow10(end - beg); 
        } else if (cur == end) {
            sum += simple_atoi(beg, end - 1);
            if (c > 0)
                sum++;
        } else {
            if (c == 0) 
                sum += simple_atoi(beg, cur - 1) * pow10(end - cur);
            else if (c == 1) 
                sum += simple_atoi(beg, cur - 1) * pow10(end - cur) + simple_atoi(cur + 1, end) + 1; 
            else 
                sum += (simple_atoi(beg, cur - 1) + 1) * pow10(end - cur);
        }
    }
    return sum;
}

int count_digit_of_1(int n)
{
    char buf[64];
    int len = snprintf(buf, sizeof(buf), "%d", n);
    return count_digit_of_1_core(buf, buf + len - 1);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 100000; i++) {
        int r = randWithRange(1, 200);
        int check = count_digit_of_1_check(r);
        int result = count_digit_of_1(r);
        if (check != result) 
            printf("r = %d | check %d result %d\n", r, check, result);
    }
}
