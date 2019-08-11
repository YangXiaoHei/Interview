#include "ds.h"

treenode *rebuild_by_in_post(long *in, long *post, int *post_idx, ht *h, int start, int end)
{
    if (start > end)
        return NULL;

    long root = post[(*post_idx)--];
    int i = ht_get(h, root);
    treenode *n = treenode_create(root);
    n->right = rebuild_by_in_post(in, post, post_idx, h, i + 1, end);
    n->left = rebuild_by_in_post(in, post, post_idx, h, start, i - 1);
    return n;
}

treenode *rebuild(long *in, long *post, int size)
{
    if (!in || !post || size <= 0)
        return NULL;

    ht *h = ht_create();
    for (int i = 0; i < size; i++)
        ht_insert(h, in[i], i);
    int post_idx = size - 1;
    treenode *root = rebuild_by_in_post(in, post, &post_idx, h, 0, size - 1);
    ht_release(&h);
    return root;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    long *in = to_in_arr(root);
    long *post = to_post_arr(root); 
    treenode *copy = rebuild(in, post, 8);
    tree_draw(copy);
}
