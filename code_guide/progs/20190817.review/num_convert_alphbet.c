#include "ds.h"

int num_convert_alphbet(const char *num)
{
    if (!num)
        return 0;

    if (!*num)
        return 1;

    if (*num == '0')
        return 0;

    int res = num_convert_alphbet(num + 1);
    if (num[1] && (*num - '0') * 10 + num[1] - '0' <= 26)
        res += num_convert_alphbet(num + 2);

    return res;
}

int main(int argc, char *argv[])
{
    // 1 2 2 1
    // 12 21
    // 1 2 21
    // 1 22 1
    // 12 2 1
    const char *str = "1221";
    printf("%d\n", num_convert_alphbet(str));
}
