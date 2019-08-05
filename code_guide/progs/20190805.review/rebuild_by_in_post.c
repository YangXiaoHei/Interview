#include "ds.h"

long hash(long key) { return key; }

treenode *rebuild_core(int *in, int *post, int *post_idx, int start, int end, ht *h)
{
    if (start > end)
        return NULL;

    int v = post[(*post_idx)--];
    int i = ht_get(h, v);
    treenode* n = treenode_create(v);
    n->right = rebuild_core(in, post, post_idx, i + 1, end, h);
    n->left = rebuild_core(in, post, post_idx, start, i - 1, h);
    return n;
}

treenode *rebuild(int *in, int *post, int size)
{
    if (!in || !post || size <= 0)
        return NULL;

    ht *h = ht_create(hash);
    for (int i = 0; i < size; i++)
        ht_insert(h, in[i], i);

    int post_idx = size - 1;
    treenode *root = rebuild_core(in, post, &post_idx, 0, size - 1, h);
    ht_release(&h);
    return root;
}

int main(int argc, char *argv[])
{
    int size = 8;
    treenode *root = bst_create(size);
    tree_draw(root);
    int *in = to_in_arr_(root);
    int *post = to_post_arr_(root);
    treenode *copy = rebuild(in, post, size);
    tree_draw(copy);
}
