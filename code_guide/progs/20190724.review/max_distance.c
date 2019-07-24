#include "ds.h"

int max2(int a, int b) { return a > b ? a : b; }
int max3(int a, int b, int c) { return max2(max2(a, b), c); }

int max_distance(treenode *root, int *max_branch)
{
    if (!root) {
        *max_branch = 0;
        return 0;
    }

    int l = max_distance(root->left, max_branch);
    int lbranch = *max_branch;
    int r = max_distance(root->right, max_branch);
    int rbranch = *max_branch;

    int include_root = lbranch + rbranch + 1;
    *max_branch = max2(lbranch, rbranch) + 1; 

    return max3(include_root, l, r);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);
    int b = 0;
    int max = max_distance(root, &b);
    printf("max = %d\n", max);
}
