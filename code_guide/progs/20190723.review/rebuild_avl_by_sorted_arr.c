#include "ds.h"

treenode *rebuild_avl(int *arr, int start, int end)
{
    if (start > end)
        return NULL;

    int mid = start + (end - start) / 2;
    treenode *n = treenode_create(arr[mid]);
    n->left = rebuild_avl(arr, start, mid - 1);
    n->right = rebuild_avl(arr, mid + 1, end);
    return n;
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 10);
    int *arr = array(size);
    printArray(arr, size);
    treenode *root = rebuild_avl(arr, 0, size - 1);
    tree_draw(root);
}
