#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "tool.h"

int binary_search_leftmost(int *arr, int size, int key)
{
    int lo = 0, hi = size - 1;
    while (lo < hi) {
        int mid = (hi - lo) / 2 + lo;
        if (key > arr[mid])
           lo = mid + 1;
        else
           hi = mid; 
    }
    return arr[lo] == key ? lo : -1; 
}

int binary_search_rightmost(int *arr, int size, int key)
{
    int lo = 0, hi = size - 1;
    while (lo < hi) {
        int mid = ceil((hi - lo) / 2.0) + lo;
        if (key < arr[mid])
            hi = mid - 1;
        else
            lo = mid;
    } 
    return arr[lo] == key ? lo : -1;
}

int check_rightmost(int *arr, int size, int key)
{
    for (int i = size - 1; i >= 0; i--)
        if (arr[i] == key)
            return i;
    return -1;
}

int check_leftmost(int *arr, int size, int key)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == key)
            return i;
    return -1;
}

void test_leftmost(void)
{
    int size = 30;
    int lo = 0, hi = 10;
    int *arr = arrayWithRange(size, lo, hi);
    tool_sort(arr, size);
    int key = randWithRange(lo, hi);
    if (binary_search_leftmost(arr, size, key) != check_leftmost(arr, size, key)) 
        printArray(arr, size);
    free(arr);
}

void test_rightmost(void)
{
    int size = 30;
    int lo = 0, hi = 10;
    int *arr = arrayWithRange(size, lo, hi);
    tool_sort(arr, size);
    int key = randWithRange(lo, hi);
    if (binary_search_rightmost(arr, size, key) != check_rightmost(arr, size, key)) 
        printArray(arr, size);
    free(arr);
}

int main(int argc, char *argv[])
{
    /* test_rightmost(); */
    /* test_leftmost(); */
}
