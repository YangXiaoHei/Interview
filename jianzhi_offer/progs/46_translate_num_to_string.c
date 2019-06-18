#include <stdio.h>
#include <stdlib.h>

int translate_num_to_str_core(char *num, int len, int idx)
{
    if (idx >= len - 1)
        return 1;

    int sum = (num[idx] - '0') * 10 + num[idx + 1] - '0';
    if (sum >= 10 && sum <= 25)
        return translate_num_to_str_core(num, len, idx + 1) + translate_num_to_str_core(num, len, idx + 2);
    return translate_num_to_str_core(num, len, idx + 1);
} 

int translate_num_to_str(int num)
{
    if (num < 0)
        return 0;

    char buf[128];
    int len = snprintf(buf, sizeof(buf), "%d", num);
    return translate_num_to_str_core(buf, len, 0);
}

int main(int argc, char *argv[])
{
    printf("%d\n", translate_num_to_str(123));
    printf("%d\n", translate_num_to_str(126));
    printf("%d\n", translate_num_to_str(9999));
    printf("%d\n", translate_num_to_str(1234));
    printf("%d\n", translate_num_to_str(12211));
}

