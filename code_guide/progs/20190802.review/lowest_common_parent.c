#include "ds.h"

treenode *lowest_common_parent(treenode *root, treenode *n1, treenode *n2)
{
    if (!root || root == n1 || root == n2)
        return root;

    treenode *l = lowest_common_parent(root->left, n1, n2);
    treenode *r = lowest_common_parent(root->right, n1, n2);
    if (l && r)
        return root;
    return l ? l : r;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    treenode *n1 = NULL, *n2 = NULL;
    tree_random_twonodes(root, &n1, &n2);
    printf("n1 = %-3ld n2 = %-3ld\n", n1->val, n2->val);
    treenode *com = lowest_common_parent(root, n1, n2);
    printf("com = %-3ld\n", com->val);
}
