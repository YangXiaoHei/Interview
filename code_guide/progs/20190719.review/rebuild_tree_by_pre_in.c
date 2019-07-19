#include "ds.h"

int pre_seq[100], pre_size = 0;
int in_seq[100], in_size = 0;

void in_trav(long v)
{
    in_seq[in_size++] = v;
}

void pre_trav(long v)
{
    pre_seq[pre_size++] = v;
}

treenode *rebuild_tree(int *pre, int *in, int size, int *pre_idx, int in_start, int in_end)
{
    if (!pre || !in || size <= 0 || in_start > in_end)
        return NULL;

    int v = pre[*pre_idx];
    int in_mid = 0;
    for (in_mid = in_start; in_mid <= in_end; in_mid++)
        if (in[in_mid] == v)
            break;

    if (in_mid > in_end) {
        printf("sequence invalid!\n");
        return NULL;
    }

    (*pre_idx)++;
    treenode *n = treenode_create(v);
    n->left = rebuild_tree(pre, in, size, pre_idx, in_start, in_mid - 1);
    n->right = rebuild_tree(pre, in, size, pre_idx, in_mid + 1, in_end);
    return n;
}

treenode *rebuild(int *pre, int *in, int size)
{
    if (!pre || !in || size <= 0)
       return NULL;

    int pidx = 0; 
    return rebuild_tree(pre, in, size, &pidx, 0, size - 1);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);

    in_traverse_funptr(root, in_trav);
    pre_traverse_funptr(root, pre_trav);
    
    treenode *copy = rebuild(pre_seq, in_seq, pre_size);
    tree_draw(copy);
}
