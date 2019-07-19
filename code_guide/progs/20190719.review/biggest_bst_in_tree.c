#include "ds.h"

treenode *biggest_bst_in_tree(treenode *root, int *arr)
{
    if (!root) {
        arr[0] = 0;
        arr[1] = 2147483647;
        arr[2] = -2147483647-1;
        return NULL;
    }

    treenode *left = root->left;
    treenode *right = root->right;
    int v = root->val;
    treenode *l = biggest_bst_in_tree(root->left, arr);
    int lsize = arr[0];
    int lmin = arr[1];
    int lmax = arr[2];
    treenode *r = biggest_bst_in_tree(root->right, arr);
    int rsize = arr[0];
    int rmin = arr[1];
    int rmax = arr[2];

    arr[1] = v < lmin ? v : lmin;
    arr[2] = v > lmax ? v : lmax;
    if (left == l && right == r && lmax < v && v < rmin) {
        arr[0] = lsize + rsize + 1;
        return root; 
    }
    arr[0] = lsize > rsize ? lsize : rsize;
    return lsize > rsize ? l : r;
}

treenode *biggest_bst(treenode *root)
{
    int arr[3] = { 0 };
    return biggest_bst_in_tree(root, arr);
}

int main(int argc, char *argv[])
{
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

    treenode *biggest = biggest_bst(root);
    tree_draw(biggest);
}
