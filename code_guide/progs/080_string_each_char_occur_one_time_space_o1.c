#include "ds.h"

void sink(char *arr, int k, int size)
{
    char t = arr[k - 1];
    while (k * 2 <= size) {
        int j = k * 2;
        if (j < size && arr[j - 1] < arr[j]) j++;
        if (t >= arr[j - 1]) break;
        arr[k - 1] = arr[j - 1];
        k = j;
    } 
    arr[k - 1] = t;
}

void exch(char *arr, int i, int j)
{
    char tmp = arr[i - 1];
    arr[i - 1] = arr[j - 1];
    arr[j - 1] = tmp;
}

void heap_sort(char *arr, int size)
{
    for (int i = size / 2; i >= 1; i--)
        sink(arr, i, size);

    while (size > 1) {
        exch(arr, 1, size--);
        sink(arr, 1, size);
    }
}

int each_one_time(const char *str)
{
    int len = strlen(str);
    char *copy = malloc(len + 1);
    snprintf(copy, len + 1, "%s", str);
    heap_sort(copy, len);

    int ok = 1;
    for (char *p = copy + 1; *p; p++) {
        if (*p == p[-1]) {
            ok = 0;
            break;
        }
    }
    free(copy);
    return ok;
}

int main(int argc, char *argv[])
{
    printf("%d\n", each_one_time("badceofkasfascd"));
    printf("%d\n", each_one_time("cdbagef"));
}
