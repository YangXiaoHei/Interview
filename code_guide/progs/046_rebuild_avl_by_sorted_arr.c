#include "ds.h"

treenode *rebuild_avl_core(int *arr, int start, int end)
{
    if (start > end)
        return NULL;

    int mid = start + (end - start) / 2;
    treenode *n = treenode_create(arr[mid]);
    n->left = rebuild_avl_core(arr, start, mid - 1);
    n->right = rebuild_avl_core(arr, mid + 1, end);
    return n;
}

treenode *rebuild_avl(int *arr, int size)
{
    if (!arr || size <= 0)
        return NULL;

    return rebuild_avl_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 8;
    int *arr = arrayNoDupWithRange(size, -10, 10);
    sort(arr, size);
    printArray(arr, size);
    treenode *root = rebuild_avl(arr, size);
    tree_draw(root);
}
