#include "ds.h"

long hash(long k) { return k; }

treenode *rebuild_by_pre_in(long *pre, long *in, int size, ht *h, int *pre_idx, int start, int end)
{
    if (start > end)
        return NULL;

    long root = pre[(*pre_idx)++];
    int i = ht_get(h, root);
    treenode *n = treenode_create(root);
    n->left = rebuild_by_pre_in(pre, in, size, h, pre_idx, start, i - 1);
    n->right = rebuild_by_pre_in(pre, in, size, h, pre_idx, i + 1, end);
    return n;
}

treenode *rebuild(long *pre, long *in, int size)
{
    ht *h = ht_create();
    for (int i = 0; i < size; i++)
        ht_insert(h, in[i], i);
    int pre_idx = 0;
    treenode *root = rebuild_by_pre_in(pre, in, size, h, &pre_idx, 0, size - 1);
    ht_release(&h);
    return root;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(6);
    tree_draw(root);
    long *pre = to_pre_arr(root);
    long *in = to_in_arr(root);
    treenode *copy = rebuild(pre, in, 6);
    tree_draw(copy);
}
