#include "ds.h"

treenode *biggest_bst_in_tree_core(treenode *root, int *record)
{
    if (!root) {
        record[0] = 0;
        record[1] = 2147483647;
        record[2] = -2147483647-1;
        return NULL;
    }

    treenode *left = root->left;
    treenode *right = root->right;
    long value = root->val;
    treenode *lbst = biggest_bst_in_tree_core(root->left, record);
    int lsize = record[0];
    int lmin = record[1];
    int lmax = record[2];
    treenode *rbst = biggest_bst_in_tree_core(root->right, record);
    int rsize = record[0];
    int rmin = record[1];
    int rmax = record[2];

    record[1] = lmin < value ? lmin : value;
    record[2] = rmax > value ? rmax : value;

    if (left == lbst && right == rbst && lmax < value && value < rmin) {
        record[0] = rsize + lsize + 1;
        return root;
    }
    record[0] = rsize > lsize ? rsize : lsize;
    return rsize > lsize ? rbst : lbst;
}

treenode *biggest_bst_in_tree(treenode *root)
{
    int record[3] = { 0 };
    return biggest_bst_in_tree_core(root, record);
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

    treenode *biggest_bst = biggest_bst_in_tree(root);
    tree_draw(biggest_bst);

}
