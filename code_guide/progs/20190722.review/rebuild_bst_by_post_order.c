#include "ds.h"

int post_seq[100], post_size = 0;

void post_trav(long v)
{
    post_seq[post_size++] = v;
}

treenode *rebuild_by_post_order(int *arr, int start, int end)
{
    if (start > end)
        return NULL;

    treenode *n = treenode_create(arr[end]);
    int more = end, less = -1;
    for (int i = start; i < end; i++) {
        if (arr[i] < arr[end])
            less = i;
        else
            more = more == end ? i : more;
    }

    if (less == -1) {
        n->right = rebuild_by_post_order(arr, start, end - 1);
        return n;
    }
    if (more == end) {
        n->left = rebuild_by_post_order(arr, start, end - 1);
        return n;
    }
    if (less != more - 1) {
        printf("sequence invalid!\n");
        exit(1);
    }
    n->left = rebuild_by_post_order(arr, start, less);
    n->right = rebuild_by_post_order(arr, more, end - 1);
    return n;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(6);
    tree_draw(root);
    post_traverse_funptr(root, post_trav);
    printArray(post_seq, post_size);
    treenode *copy = rebuild_by_post_order(post_seq, 0, post_size - 1);
    tree_draw(copy);
}
