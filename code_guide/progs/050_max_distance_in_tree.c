#include "ds.h"

int max2(int a, int b)
{
    return a > b ? a : b;
}

int max3(int a, int b, int c)
{
    return max2(max2(a, b), c);
}

int max_distance_in_tree_core(treenode *root, int *last_max_branch)
{
    if (!root) {
        *last_max_branch = 0;
        return 0;
    }   

    int lmax = max_distance_in_tree_core(root->left, last_max_branch);
    int max_from_left = *last_max_branch;

    int rmax = max_distance_in_tree_core(root->right, last_max_branch);
    int max_from_right = *last_max_branch;

    int cur_max = max_from_left + max_from_right + 1;
    *last_max_branch = max2(max_from_left, max_from_right) + 1;
    return max3(cur_max, lmax, rmax);
}

int max_distance_in_tree(treenode *root)
{
    int n = 0;
    return max_distance_in_tree_core(root, &n);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);
    printf("max distance %d\n", max_distance_in_tree(root));
}
