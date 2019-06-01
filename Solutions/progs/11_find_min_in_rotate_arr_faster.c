#include <stdio.h>

int find_min(int *a, int size)
{
    if (!a || size <= 0)
        return -1;

    if (size == 1)
        return a[0];

    if (a[size - 1] > a[0])
        return a[0];

    for (int i = 1; i < size; i++)
        if (a[i] < a[0])
            return a[i];

    return a[0];
}

int main(int argc, char *argv[])
{
    int a[] = {4, 5, 6, 1, 2, 3, 4};
    int size = sizeof(a) / sizeof(a[0]);
    printf("%d\n", find_min(a, size));
}
