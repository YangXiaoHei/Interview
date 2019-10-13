#include "ds.h"

int xpow(int n, int exp)
{
    int base = n;
    int res = 1;
    while (exp) {
        if (exp & 1) 
            res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

int count_1(int n)
{
    if (n < 1)
        return 0;

    int len = get_num_width(n);
    if (len == 1)
        return 1;

    int tmp = xpow(10, len - 1);
    int first = n / tmp;
    int first_cnt = first == 1 ? n % tmp + 1 : tmp;
    int other_cnt = first * (len - 1) * (tmp / 10);
    return first_cnt + other_cnt + count_1(n % tmp);
}

int get1(int n)
{
    int cnt = 0;
    while (n) {
        if (n % 10 == 1)
            cnt++;
        n /= 10;
    }
    return cnt;
}
int check(int n)
{
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += get1(i);    
    }
    return total;
}

int main()
{
    for (int i = 1; i < 10000; i++) {
        if (check(i) != count_1(i)) {
            printf("i = %d\n", i);
            break;
        }
    }    
}
