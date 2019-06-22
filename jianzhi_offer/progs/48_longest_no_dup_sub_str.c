#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tool.h"

int longest_no_dup_length(char *str, int len)
{
    int max_len = 0;
    int cur_len = 0;

    int beg = 0, end = 0;

    char map[26];
    for (int i = 0; i < 26; i++)
        map[i] = -1;

    for (int i = 0; i < len; i++) {
        int prev_idx = map[str[i] - 'a'];
        if (prev_idx < 0 || i - prev_idx > cur_len) 
            cur_len++;
        else {
            if (cur_len > max_len) {
                max_len = cur_len;
                end = i - 1;
                beg = i - max_len;
            }

            cur_len = i - prev_idx;
        }
        map[str[i] - 'a'] = i;
    }
    if (cur_len > max_len) {
        max_len = cur_len;
        end = len - 1;
        beg = len - max_len;
    }

    str[end + 1] = 0;
    printf("max_len=%-3d max_str=%s\n", max_len, str + beg);

    return max_len;
}

int main(int argc, char *argv[])
{
    /* 初始化 26 个字母数组 */
    char alphabet[26];
    for (int i = 0; i < 26; i++)
        alphabet[i] = i + 'a';    

    /* 构建字符串 */
    int size = 10;
    char str[64];
    for (int i = 0; i < size; i++)
        str[i] = alphabet[randWithRange(0, 26)];
    str[size] = 0;
    printf("%s\n", str);

    longest_no_dup_length(str, size);
}
