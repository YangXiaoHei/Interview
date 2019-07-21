#include "ds.h"

int pre_seq[100], pre_size = 0;
int post_seq[100], post_size = 0;

void pre_trav(long v)
{
    pre_seq[pre_size++] = v;
}

void post_trav(long v)
{
    post_seq[post_size++] = v;
}

treenode *rebuild_tree_by_pre_post_core(int *pre, int *post, int pre_idx, int post_idx, int size)
{
    if (size == 0)
        return NULL;

    treenode *n = treenode_create(pre[pre_idx]);
    if (size == 1)
        return n;

    int lsize;
    int child = pre[pre_idx + 1];
    for (lsize = 1; lsize < size; lsize++)
        if  (post[post_idx + lsize - 1] == child)
            break;

    n->left = rebuild_tree_by_pre_post_core(pre, post, pre_idx + 1, post_idx, lsize);
    n->right = rebuild_tree_by_pre_post_core(pre, post, pre_idx + lsize + 1, post_idx + lsize, size - lsize - 1);
    return n;
}

treenode *rebuild_tree(int *pre, int *post, int size)
{
    if (!pre || !post || size <= 0)
        return NULL;
    return rebuild_tree_by_pre_post_core(pre, post, 0, 0, size);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    pre_traverse_funptr(root, pre_trav);
    post_traverse_funptr(root, post_trav);
    printArray(pre_seq, pre_size);
    printArray(post_seq, post_size);
    treenode *copy = rebuild_tree(pre_seq, post_seq, post_size);
    tree_draw(copy);
}
