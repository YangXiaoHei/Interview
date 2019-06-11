#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tool.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

void sort_core(int *arr, int lo, int hi)
{
    if (lo >= hi)
        return;

    int i = lo, j = hi + 1;
    int pivot = arr[lo];
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + lo, arr + j);

    sort_core(arr, lo, j - 1);
    sort_core(arr, j + 1, hi);
}

void sort(int *arr, int size)
{
    sort_core(arr, 0, size - 1);
}

int partition(int *a, int lo, int hi)
{
    int pivot = a[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && a[++i] < pivot);
        while (j > lo && a[--j] > pivot);
        if (i >= j) break;
        swap(a + i, a + j);
    }
    swap(a + lo, a + j);
    return j;
}

int select_k(int *arr, int size, int k)
{
    if (!arr || size <= 0 || k < 0 || k >= size)
        return -1;
    int j;
    int lo = 0, hi = size - 1;
    while (1) {
        j = partition(arr, lo, hi);
        if (k == j)
            break;

        if (k < j)
            hi = j - 1;
        else
            lo = j + 1;
    }
    return arr[k];
}

void test_select_k(void)
{
    int *arr = arrayWithRange(20, 1, 100);
    printArray(arr, 20);
    int r = randWithRange(0, 20);
    printf("%3dth elem = %-3d\n", r, select_k(arr, 20, r));
}

void shuffle(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        int r = i + randWithRange(0, size - i);
        swap(arr + i, arr + r);
    }
}

void initArrayWithMoreThanHalfElem(int *arr, int size) 
{
    int times = randWithRange(size / 2 + 1, min(size, size / 2 + 3));
    int elem = randWithRange(0, 50);
    for (int i = 0; i < times; i++)
        arr[i] = elem;
    for (int i = times; i < size; i++) {
        arr[i] = randWithRange(0, 50);
    }
    shuffle(arr, size);
}

void test_array_gen(void)
{
    int arr[30];
    int size = sizeof(arr) / sizeof(arr[0]);
    initArrayWithMoreThanHalfElem(arr, size);
    printArray(arr, size); 
}

int find_more_than_half(int *arr, int size)
{
    return select_k(arr, size, size / 2);
}

int find_more_than_half_2(int *arr, int size)
{
    int times = 1;
    int res = arr[0];
    for (int i = 0; i < size; i++) {
        if (times == 0) {
            res = arr[i];
            times = 1;
        } else if (arr[i] == res)
            times++;
        else
            times--;
    }
    return res;
}

void test_method_1(int *arr, int size)
{
    printf("the elem more than half 1 %-3d\n", find_more_than_half(arr, size));
} 

void test_method_2(int *arr, int size)
{
    printf("the elem more than half 2 %-3d\n", find_more_than_half_2(arr, size));
}

int main(int argc, char *argv[])
{
    int arr[30];
    int size = sizeof(arr) / sizeof(arr[0]);
    initArrayWithMoreThanHalfElem(arr, size);
    printArray(arr, size); 
    test_method_1(arr, size);
    test_method_2(arr, size);
    sort(arr, size);
    printArray(arr, size);
}
