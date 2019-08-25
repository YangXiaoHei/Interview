#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_distance(const char *arr[], int size, const char *str1, const char *str2)
{
    int i = -1, j = -1;
    int m = 2147483647;
    for (int k = 0; k < size; k++) {
        if (strcmp(str1, arr[k]) == 0) {
            m = min(m, j == -1 ? m : k - j);
            i = k;
        }
        if (strcmp(str2, arr[k]) == 0) {
            m = min(m, i == -1 ? m : k - i);
            j = k;
        }
    }
    return m == 2147483647 ? -1 : m;
}

int main(int argc, char *argv[])
{
    const char *str[] = { "1", "3", "2", "3", "3", "3", "1", "4", "4", "2" };
    int size = sizeof(str) / sizeof(str[0]);
    printf("%d\n", min_distance(str, size, "1", "2"));
}
