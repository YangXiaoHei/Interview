#include "ds.h"

int is_post_order_core(int *arr, int start, int end)
{
    if (start > end)
        return 1;

    int less = -1, more = end;
    for (int i = start; i < end; i++) {
        if (arr[i] < arr[end])
            less = i;
        else if (more == end)
            more = i;
    }
    if (less == -1 || more == end)
        return is_post_order_core(arr, start, end - 1);

    if (less != more - 1)
        return 0;

    return is_post_order_core(arr, start, less) && is_post_order_core(arr, more, end - 1);
}

int is_post_order(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;

    return is_post_order_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 8;
    treenode *root = bst_create(size);
    tree_draw(root);
    int *arr = to_post_arr_(root);
    printf("%d\n", is_post_order(arr, size));
}
