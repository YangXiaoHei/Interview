#include "ds.h"

int tree_is_symmetric_core(treenode *n1, treenode *n2)
{
    if (!n1 && !n2)
       return 1;

    if (!!n1 ^ !!n2)
       return 0; 

    if (n1->val != n2->val)
        return 0;

    return tree_is_symmetric_core(n1->left, n2->right) && 
           tree_is_symmetric_core(n1->right, n2->left);
}

int tree_is_symmetric(treenode *root)
{
    if (!root)
        return 0;

    if (root->left && root->right)
        return tree_is_symmetric_core(root->left, root->right);

    return 0;
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(2);
    root->left->right = N(3);
    root->left->right->left = N(4);
    root->right->left = N(3);
    root->right->left->right = N(4);

    tree_draw(root);
    printf("is symmetric : %d\n", tree_is_symmetric(root));
}
