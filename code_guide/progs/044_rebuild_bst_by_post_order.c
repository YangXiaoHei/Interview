#include "ds.h"

int post_seq[100];
int post_size = 0;

void post_trav(long v)
{
    post_seq[post_size++] = v;
}

int is_post_order(int *arr, int start, int end)
{
    if (!arr)
        return 0;

    if (start > end)
        return 1;

    int more = end;
    int less = -1;
    for (int i = start; i < end; i++)
        if (arr[i] < arr[end])
            less = i;
        else
            more = more == end ? i : more;

    if (less == -1 || more == end)
        return is_post_order(arr, start, end - 1);

    if (less != more - 1)
        return 0;

    return is_post_order(arr, start, less) && is_post_order(arr, more, end - 1);
}

treenode* rebuild_bst_by_post_order(int *arr, int start, int end)
{
    if (start > end)
        return NULL;

    treenode *n = treenode_create(arr[end]);
    int more = end;
    int less = -1;
    for (int i = start; i < end; i++) {
        if (arr[i] < arr[end])
            less = i;
        else
            more = more == end ? i : more;
    }
    n->left = rebuild_bst_by_post_order(arr, start, less);
    n->right = rebuild_bst_by_post_order(arr, more, end - 1);
    return n;
}

treenode *rebuild_bst(int *arr, int size)
{
    if (!arr || size <= 0)
        return NULL;
    
    if (!is_post_order(arr, 0, size - 1))
        return NULL;

    return rebuild_bst_by_post_order(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    tree_draw(root);
    post_traverse_funptr(root, post_trav);
    printArray(post_seq, post_size);
    treenode *copy = rebuild_bst(post_seq, post_size);
    tree_draw(root);

}
