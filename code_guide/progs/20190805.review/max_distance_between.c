#include "ds.h"

int max2(int a, int b) { return a > b ? a : b; }
int max3(int a, int b, int c) { return max2(max2(a, b), c); }

int max_distance_core(treenode *root, int *max_branch)
{
    if (!root) {
        *max_branch = 0;
        return 0;
    }

    int l = max_distance_core(root->left, max_branch);
    int lmax = *max_branch;
    int r = max_distance_core(root->right, max_branch);
    int rmax = *max_branch;

    int include = lmax + rmax + 1;
    *max_branch = max2(lmax, rmax) + 1;
    return max3(l, r, include);
}

int max_distance(treenode *root)
{
    if (!root)
        return 0;

    int max_branch = 0;
    return max_distance_core(root, &max_branch);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    printf("%d\n", max_distance(root)); 
}
