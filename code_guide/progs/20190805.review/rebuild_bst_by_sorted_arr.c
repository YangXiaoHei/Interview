#include "ds.h"

treenode *rebuild_core(int *arr, int lo, int hi)
{
    if (lo > hi)
        return NULL;

    int mid = lo + (hi - lo) / 2;
    treenode *n = treenode_create(arr[mid]);
    n->left = rebuild_core(arr, lo, mid - 1);
    n->right = rebuild_core(arr, mid + 1, hi);
    return n;
}

treenode *rebuild(int *arr, int size)
{
    if (!arr || size <= 0 || !is_sorted(arr, size))
        return NULL;
    return rebuild_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayNoDupWithRange(size, 0, 100);
    sort(arr, size);
    printArray(arr, size);
    tree_draw(rebuild(arr, size));
}
