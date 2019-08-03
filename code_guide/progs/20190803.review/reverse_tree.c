#include "ds.h"

void reverse_tree(treenode *root)
{
    if (!root)
        return;

    treenode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    reverse_tree(root->left);
    reverse_tree(root->right);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    reverse_tree(root);
    tree_draw(root);
}
