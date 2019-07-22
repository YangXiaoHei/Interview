#include "ds.h"

int is_contain(treenode *big, treenode *small)
{
    if (!small)
        return 1;

    if (!big)
        return 0;

    if (big->val != small->val)
        return 0;

    return is_contain(big->left, small->left) && is_contain(big->right, small->right);
}

int big_contain_small(treenode *big, treenode *small)
{
    if (!big || !small)
        return 0;

    int result = 0;
    if (big->val == small->val)
        result = is_contain(big, small);

    if (result)
        return 1;

    return big_contain_small(big->left, small) || big_contain_small(big->right, small);
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    root->left->left = N(4);
    root->left->right = N(5);
    root->right->left = N(6);
    root->right->right = N(7);
    tree_draw(root);

    treenode *small = N(2);
    small->left = N(4);
    small->right = N(5);
    tree_draw(small);

    printf("is contain %d\n", big_contain_small(root, small));

}
