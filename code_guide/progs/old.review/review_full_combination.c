#include "ds.h"

void count_sub_arr_core(int *arr, int size, stack *s, int n, int idx)
{
    if (stack_size(s) == n) {
        stack_print_s(s);
        return;
    }

    for (int i = idx; i < size; i++) {
        stack_push(s, arr[i]);
        count_sub_arr_core(arr, size, s, n, i + 1);
        stack_pop(s);
    }
}

void count_sub_arr(int *arr, int size, int n)
{
    stack *s = stack_create();
    count_sub_arr_core(arr, size, s, n, 0);
    stack_release(&s);
}

int main(int argc, char *argv[])
{
    int arr[] = { 1, 2, 3, 4, 5 };
    for (int i = 1; i < 5; i++)
        count_sub_arr(arr, 5, i);
}
