#include "ds.h"

void print_m_from_n(int *arr, int size, int m)
{
    int cnt = 0;
    while (cnt < m) {
        int r = rand() % (size - cnt);
        int elem = arr[r];
        printf("%-4d", elem);
        swap(arr + size - 1 - cnt++, arr + r);
    }
    printf("\n");
}

int main()
{
    int size = 8;
    int *arr = arrayNoDupWithRange(size, 0, 10);
    printArray(arr, size);
    print_m_from_n(arr, size, 3);
}
