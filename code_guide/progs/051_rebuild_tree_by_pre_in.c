#include "ds.h"

int pre_seq[100], pre_size = 0;
int in_seq[100], in_size = 0;

void pre_trav(long v)
{
    pre_seq[pre_size++] = v;
}
void in_trav(long v)
{
    in_seq[in_size++] = v;
}

treenode *rebuild_tree_by_pre_in_core(int *pre, int *in, int *pre_idx, int start, int end)
{
    if (start > end)
        return NULL;

    int root = pre[(*pre_idx)++]; 
    int in_mid = start;
    for (; in_mid <= end && in[in_mid] != root; in_mid++)
        ;

    if (in_mid > end) {
        printf("invalid sequnce\n");
        exit(1);
    }

    treenode *n = treenode_create(root);
    n->left = rebuild_tree_by_pre_in_core(pre, in, pre_idx, start, in_mid - 1);
    n->right = rebuild_tree_by_pre_in_core(pre, in, pre_idx, in_mid + 1, end);
    return n;
}

treenode *rebuild_tree(int *pre, int *in, int size)
{
    if (!pre || !in || size <= 0)
        return NULL;
    int pre_idx = 0;
    return rebuild_tree_by_pre_in_core(pre, in, &pre_idx, 0, size - 1);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);
    pre_traverse_funptr(root, pre_trav);    
    in_traverse_funptr(root, in_trav);    
    printArray(pre_seq, pre_size);
    printArray(in_seq, in_size);
    treenode *copy = rebuild_tree(pre_seq, in_seq, pre_size);
    tree_draw(copy);
}
