#include "ds.h"

void get_kth_node(treenode *root, treenode **target, int *k)
{
    if (!root)
        return;

    if (*target)
        return;

    get_kth_node(root->left, target, k);

    if ((*k)-- == 0)
        *target = root;

    get_kth_node(root->right, target, k);
}

void gen_two_treenode(treenode *root, int size, treenode **n1, treenode **n2)
{
    int k = randWithRange(0, size);
    int m = randWithRange(0, size);
    get_kth_node(root, n1, &k);
    get_kth_node(root, n2, &m);
}

treenode *lowest_common_parent_in_bst(treenode *root, treenode *n1, treenode *n2)
{
    if (!root || !n1 || !n2)
        return NULL;

    if (n1 == n2)
        return n1;
    
#define V(x) ((long)((treenode *)x)->val)

    if (V(n1) < V(root) && V(n2) < V(root))
        return lowest_common_parent_in_bst(root->left, n1, n2);

    if (V(n1) > V(root) && V(n2) > V(root))
        return lowest_common_parent_in_bst(root->right, n1, n2);

    return root;
}

int main(int argc, char *argv[])
{
    int size = 8;
    treenode *root = bst_create(size);
    tree_draw(root);
    treenode *n1 = NULL, *n2 = NULL;
    gen_two_treenode(root, size, &n1, &n2);
    printf("n1 = %ld, n2 = %ld\n", n1->val, n2->val);
    treenode *parent = lowest_common_parent_in_bst(root, n1, n2);
    if (parent)
        printf("common parent is %-3ld\n", parent->val);
}
