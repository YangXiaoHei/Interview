#include "ds.h"

int post_seq[100], post_size = 0;

void post_trav(long v)
{
    post_seq[post_size++] = v;
}

int is_post_order(int *arr, int start, int end)
{
    if (start > end)
        return 1;

    int root = arr[end];
    int more = end;
    int less = -1;
    for (int i = start; i < end; i++) {
        if (arr[i] < root)
            less = i;
        else
            more = more == end ? i : more;
    }

    if (less == -1 || more == end)
        return is_post_order(arr, start, end - 1);

    if (less != more - 1)
        return 0;

    return is_post_order(arr, start, less) && is_post_order(arr, more, end - 1);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    post_traverse_funptr(root, post_trav);
    printArray(post_seq, post_size);
    swap(post_seq + 1, post_seq + 3);
    printArray(post_seq, post_size);
    printf("is post order %d\n", is_post_order(post_seq, 0, post_size - 1));
}
