#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* big_num_add(char *n1, size_t len1, char *n2, size_t len2)
{
    size_t rlen = (len1 > len2 ? len1 : len2) + 1 + 1; 
    char *result = malloc(rlen);
    if (!result) exit(1);
    result[rlen - 1] = 0;
    rlen--;

    long i = len1 - 1, j = len2 - 1;
    long k = rlen - 1;
    int carry = 0;
    int num1, num2, r;
    do {
        num1 = i >= 0 ? n1[i--] - '0' : 0;
        num2 = j >= 0 ? n2[j--] - '0' : 0;
        r = num1 + num2 + carry;
        r = r >= 10 ? (carry = 1, r % 10) : r;
        printf("num1=%d num2=%d r=%d carry=%d\n", num1, num2, r, carry);
        result[k--] = r + '0';
    } while (carry && (i >= 0 || j >= 0));

    if (carry)
        result[k] = 1 + '0';

    return result;
}

int main(int argc, char *argv[])
{
    char *num1 = "1239874234298217391873242399123991999";
    char *num2 = "19999999234234992349293492349293429492349324";

    printf("%s\n", big_num_add(num1, strlen(num1), num2, strlen(num2)));
}
