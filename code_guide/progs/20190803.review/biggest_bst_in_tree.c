#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

treenode *biggest_bst(treenode *root, int *arr)
{
    if (!root) {
        arr[0] = 2147483647;
        arr[1] = -2147483648;
        arr[2] = 0;
        return NULL;
    }

    treenode *l = biggest_bst(root->left, arr);
    int lmin = arr[0];
    int lmax = arr[1];
    int lsize = arr[2];
    treenode *r = biggest_bst(root->right, arr);
    int rmin = arr[0];
    int rmax = arr[1];
    int rsize = arr[2];
    
    arr[0] = min(rmin, root->val);    
    arr[1] = max(lmax, root->val);    
    if (root->left == l && root->right == r && lmax < root->val && root->val < rmin) {
        arr[2] = lsize + rsize + 1;
        return root;
    }
    arr[2] = max(lsize, rsize);
    return rsize > lsize ? r : l;
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

    int arr[3] = { 0 };
    treenode *b = biggest_bst(root, arr);
    tree_draw(b);    
}
