#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }
int min_distance(const char *arr[], int size, const char *str1, const char *str2)
{
    if (!arr || !str1 || !str2 || !*str1 || !*str2)
        return 0;

    int last1 = -1, last2 = -2;
    int m = 2147483647;
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], str1) == 0) {
            m = min(m, last2 == -1 ? m : i - last2); 
            last1 = i;
        }
        if (strcmp(arr[i], str2) == 0) {
            m = min(m, last1 == -1 ? m : i - last1);
            last2 = i;
        }
    }
    return m == 2147483647 ? -1 : m;
}

int main(int argc, char *argv[])
{
    const char *arr[] = { "1", "3", "3", "2", "0", "3", "1", "3", "2" };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", min_distance(arr, size, "1", "2"));
}
