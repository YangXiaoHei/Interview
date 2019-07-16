#include "ds.h"

int is_bstnode(treenode *root, treenode *n, int val)
{
    if (!root)
       return 0;

    if (root == n)
       return 1;

    return is_bstnode(val < root->val ? root->left : root->right, n, val);
}

int max_topo(treenode *root, treenode *n)
{
    if (root && n && is_bstnode(root, n, n->val))
        return max_topo(root, n->left) + max_topo(root, n->right) + 1;
    return 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int biggest_topo_of_bst(treenode *root)
{
    if (!root)
        return 0;

    int m = max_topo(root, root);
    m = max(biggest_topo_of_bst(root->left), m);
    m = max(biggest_topo_of_bst(root->right), m);
    return m;
}

int main(int argc, char *argv[])
{
    /* treenode *root = bst_create(10); */
#define N(x) treenode_create(x)
    treenode *root = N(6);
    root->left = N(1);
    root->left->left = N(0);
    root->left->right = N(3);
    root->right = N(12);
    root->right->left = N(10);
    root->right->left->left = N(4);
    root->right->left->left->left = N(2);
    root->right->left->left->right = N(5);
    root->right->left->right = N(14);
    root->right->left->right->left = N(11);
    root->right->left->right->right = N(15);
    root->right->right = N(13);
    root->right->right->left = N(20);
    root->right->right->right = N(16);
    tree_draw(root);
    printf("biggest topo of bst size is : %d\n", biggest_topo_of_bst(root));
}
