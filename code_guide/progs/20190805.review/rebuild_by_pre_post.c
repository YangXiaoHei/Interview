#include "ds.h"

long hash(long key) { return key; }

treenode *rebuild_core(int *pre, int *post, int pi, int ps, int si, int ss, ht *h)
{
    if (pi > ps)
        return NULL;

    treenode *n = treenode_create(post[ss--]);
    if (ps == pi)
        return n;

    int i = ht_get(h, pre[++pi]);
    n->left = rebuild_core(pre, post, pi, pi + i - si, si, i, h);
    n->right = rebuild_core(pre, post, pi + i - si + 1, ps, i + 1, ss, h);
    return n;
}

treenode *rebuild(int *pre, int *post, int size)
{
    if (!pre || !post || size <= 0)
        return NULL;

    ht *h = ht_create(hash);
    for (int i = 0; i < size; i++)
        ht_insert(h, post[i], i);
    treenode *root = rebuild_core(pre, post, 0, size - 1, 0, size - 1, h);
    ht_release(&h);
    return root;
}

int main(int argc, char *argv[])
{
    int size = 8;
    treenode *root = bst_create(size);
    tree_draw(root);
    int *pre = to_pre_arr_(root);
    int *post = to_post_arr_(root);
    treenode *copy = rebuild(pre, post, size);
    tree_draw(copy);
}
