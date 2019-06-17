#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tool.h"

char last_buf[8192];
char cur_buf[8192];
void combinate_smallest_num_core(int *arr, int size, int idx)
{
    if (idx == size) {
        int len = 0;
        for (int j = 0; j < size; j++) {
            assert(len < sizeof(cur_buf));
            len += snprintf(cur_buf + len, sizeof(cur_buf) - len, "%zd", arr[j]);
        } 
        if (!*last_buf) 
            memcpy(last_buf, cur_buf, len);
        else if (strcmp(cur_buf, last_buf) < 0) 
            memcpy(last_buf, cur_buf, len);
        return;
    }

    for (int i = idx; i < size; i++) {
        swap(arr + i, arr + idx);
        combinate_smallest_num_core(arr, size, idx + 1);
        swap(arr + i, arr + idx);
    }
}

void combinate_smallest_num(int *arr, int size)
{
    if (!arr || size <= 0)
       return; 

    for (int i = 0; i < size; i++)
        if (arr[i] < 0)
            return;

    combinate_smallest_num_core(arr, size, 0);
    printf("the smallest combination is %s\n", last_buf);
}

int main(int argc, char *argv[])
{
    int size = 7;
    int *arr = arrayWithRange(size, 0, 50);
    combinate_smallest_num(arr, size);
}
