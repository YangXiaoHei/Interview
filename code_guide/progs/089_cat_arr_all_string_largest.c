#include "ds.h"

void xswap(const char **a, const char **b)
{
    const char *c = *a;
    *a = *b;
    *b = c;
}

int xcmp(const char *a, const char *b)
{
    int lena = strlen(a), lenb = strlen(b);
    char *ab = malloc(lena + lenb + 1);
    snprintf(ab, lena + lenb + 1, "%s%s", a, b);

    char *ba = malloc(lena + lenb + 1);
    snprintf(ba, lena + lenb + 1, "%s%s", b, a);
    int res = strcmp(ab, ba);
    free(ab);
    free(ba);
    return res;
}

void quick_core(const char *arr[], int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
        return;
    if (size == 2) {
        if (xcmp(arr[lo], arr[hi]) > 0)
            xswap(arr + lo, arr + hi);
        return;
    }

    int mid = lo + (hi - lo) / 2;

    if (xcmp(arr[mid], arr[lo]) < 0) xswap(arr + mid, arr + lo);
    if (xcmp(arr[hi], arr[lo]) < 0)  xswap(arr + hi, arr + lo);
    if (xcmp(arr[hi], arr[mid]) < 0) xswap(arr + mid, arr + hi);

    if (size == 3) 
        return;

    xswap(arr + hi - 1, arr + mid);
    const char *pivot = arr[hi - 1];
    int i = lo - 1, j = hi - 1;
    while (1) {
        while (xcmp(arr[++i], pivot) < 0);
        while (xcmp(arr[--j], pivot) > 0);
        if (i >= j) break;
        xswap(arr + i, arr + j);
    }
    xswap(arr + i, arr + hi - 1);
    quick_core(arr, lo, i - 1);
    quick_core(arr, i + 1, hi);
}

void quick(const char *arr[], int size)
{
    if (!arr || size <= 0)
        return;
    quick_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    const char *arr[] = { "c", "d", "a", "f", "b", "e" };    
    int size = sizeof(arr) / sizeof(arr[0]);
    quick(arr, size);

    int total_len = 0;
    for (int i = 0; i < size; i++)
        total_len += strlen(arr[i]);

    int l = 0;
    char *buf = malloc(total_len + 1);
    for (int i = 0; i < size; i++)
        l += snprintf(buf + i, total_len + 1 - i, "%s", arr[i]);
    printf("res = %s\n", buf);
}
