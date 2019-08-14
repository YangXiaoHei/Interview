#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int longest_nodup_substr(const char *str)
{
    if (!str || !*str)
        return 0;

    int map[256];
    memset(map, -1, sizeof(int) * 256);

    int pre = -1;
    int cur = 0;
    int len = strlen(str);
    int res = 0;
    for (int i = 0; i < len; i++) {
        pre = max(pre, map[str[i]]);
        cur = i - pre;
        res = max(cur, res);
        map[str[i]] = i;
    }
    return res; 
}

int main(int argc, char *argv[])
{
    const char *str = "abcdbaieab";
    printf("%d\n", longest_nodup_substr(str));
}
