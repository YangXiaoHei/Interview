#include "ds.h"

int is_symmetry_core(treenode *n1, treenode *n2)
{
    if (!n1 && !n2)
        return 1;

    if (!n1 ^ !n2)
        return 0;

    if (n1->val != n2->val)
        return 0;

    return is_symmetry_core(n1->left, n2->right) && is_symmetry_core(n1->right, n2->left);
}

int is_symmetry(treenode *root)
{
    if (!root)
        return 0;

    return is_symmetry_core(root->left, root->right);
}

int main(int argc, char *argv[])
{
    /* treenode *root = bst_create(7); */
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(3);
    root->right = N(3);
    tree_draw(root);
    printf("%d\n", is_symmetry(root));
}
