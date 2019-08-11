#include "ds.h"

treenode *rebuild_core(int *pre, int *in, ht* h, int *pre_idx, int is, int ie)
{
    if (is > ie)
        return NULL;

    int v = pre[(*pre_idx)++];
    int mid = ht_get(h, v);
    treenode *n = treenode_create(v);
    n->left = rebuild_core(pre, in, h, pre_idx, is, mid - 1);
    n->right = rebuild_core(pre, in, h, pre_idx, mid + 1, ie);
    return n;
}

treenode *rebuild(int *pre, int *in, int size)
{
    ht *h = ht_create();
    for (int i = 0; i < size; i++)
        ht_insert(h, in[i], i);
    int pre_idx = 0;
    treenode *root = rebuild_core(pre, in, h, &pre_idx, 0, size - 1);
    ht_release(&h);
    return root;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    int *pre = to_pre_arr_(root);
    int *in = to_in_arr_(root);
    treenode *copy = rebuild(pre, in, 8);
    tree_draw(copy);
}
