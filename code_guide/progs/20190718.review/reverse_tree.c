#include "ds.h"

void reverse_tree(treenode *root)
{
    if (!root)
        return;

    treenode *n = root->left;
    root->left = root->right;
    root->right = n;

    reverse_tree(root->left);
    reverse_tree(root->right);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    reverse_tree(root);
    tree_draw(root);
}
