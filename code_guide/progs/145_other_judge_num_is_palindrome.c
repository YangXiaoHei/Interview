#include "ds.h"

int is_palindrome(int n)
{
    if (n == -2147483647-1)
        return 0;

    if (n / 10 == 0)
        return 1;

    n = n < 0 ? -n : n;
    int help = 1;
    int tmp = n;
    while (tmp / 10) {
        help *= 10;
        tmp /= 10;
    }
    while (n) {
        if (n / help != n % 10)
            return 0;
        n = (n % help) / 10;
        help /= 100;
    }
    return 1;
}

int main()
{
    printf("%d\n", is_palindrome(-121));
    printf("%d\n", is_palindrome(121));
    printf("%d\n", is_palindrome(1221));
    printf("%d\n", is_palindrome(12321));
    printf("%d\n", is_palindrome(123421));
}
