#include "ds.h"

int equal(treenode *big, treenode *small)
{
    if (!big && !small)
        return 1;

    if (!big ^ !small)
        return 0;

    if (big->val != small->val)
        return 0;

    return equal(big->left, small->left) && equal(big->right, small->right);
}

int subtree_contain(treenode *big, treenode *small)
{
    if (!big || !small)
        return 0;

    int result = 0;
    if (big->val == small->val)
        result = equal(big, small);

    return result || subtree_contain(big->left, small) || subtree_contain(big->right, small);
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *big = N(1);
    big->left = N(2);
    big->left->left = N(4);
    big->left->right = N(5);
    big->right = N(3);
    big->right->left = N(6);
    big->right->right = N(7);
    tree_draw(big);

    {
        treenode *small = N(2);
        small->left = N(4);
        small->right = N(5);
        tree_draw(small);
        printf("is contain : %d\n", subtree_contain(big, small));
    }
    {
        treenode *small = N(2);
        small->right = N(5);
        tree_draw(small);
        printf("is contain : %d\n", subtree_contain(big, small));
    }
    {
        treenode *small = N(2);
        small->left = N(4);
        tree_draw(small);
        printf("is contain : %d\n", subtree_contain(big, small));
    }
}
